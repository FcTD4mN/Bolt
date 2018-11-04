#include "Core.ECS.System.SightSystem.h"


#include "Core.Base.Thread.ThreadProcessor.h"
#include "Core.Base.Thread.Thread.h"
#include "Core.ECS.Core.Entity.h"
#include "Core.ECS.Core.World.h"
#include "Core.ECS.Component.Transformation.h"
#include "Core.ECS.Component.FieldOfView.h"
#include "Core.ECS.Component.Direction.h"
#include "Core.ECS.Mapping.ScreenEntityMap.h"
#include "Core.Mapping.PhysicEntityGrid.h"
#include "Core.Render.Layer.h"
#include "Core.Math.Utils.h"
#include "Core.Math.Ray.h"


#include <SFML/Graphics.hpp>
#include <iostream>


namespace nCore {
namespace nECS {
namespace nSystem {


#define FOVSplitThreshold 20


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------ Construction/Destruction
// -------------------------------------------------------------------------------------


cSightSystem::~cSightSystem()
{
}


cSightSystem::cSightSystem() :
    tSuperClass( "SightSystem" )
{
}


cSightSystem::cSightSystem( const cSightSystem & iSys ) :
    tSuperClass( iSys )
{
}


// -------------------------------------------------------------------------------------
// ----------------------------------------------------------------------- Init/Finalize
// -------------------------------------------------------------------------------------


::nCore::nECS::nCore::cSystem*
cSightSystem::Clone() const
{
    return  new cSightSystem( *this );
}


void
cSightSystem::Initialize()
{
    mOutputTriangles    = new std::vector< sf::VertexArray >();
    mTriangleQueue      = new std::queue< eAssociatedTriangle >();

    mThreadHandles.reserve( 256 );
}


void
cSightSystem::Finalize()
{
    delete  mOutputTriangles;
    delete  mTriangleQueue;
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------- Update/Draw
// -------------------------------------------------------------------------------------


void
cSightSystem::Draw( sf::RenderTarget* iRenderTarget )
{
    for( auto fov : mFOVDrawer )
    {
        for( int i = 0; i < fov.size(); ++i )
        {
            for( int j = 0; j < fov[ i ].getVertexCount(); ++j )
            {
                fov[ i ].setPrimitiveType( sf::Triangles );
                fov[ i ][ j ].color = sf::Color( 200,20,20,50 );
            }

            iRenderTarget->draw( fov[ i ] );
        }
    }
}


void
cSightSystem::Update( unsigned int iDeltaTime )
{
    //// ========================================
    //// ============== MULTI THREAD ============
    //// ========================================

    ::nCore::nMapping::cEntityGrid* entityMap = 0;

    // Draw container
    mFOVDrawer.clear();

    for( int i = 0; i < mWatchers.size(); ++i )
    {
        ::nCore::nECS::nCore::cEntity* entity = mWatchers[ i ];

        auto layer = entity->Layer();
        if( layer )
            entityMap = layer->EntityGrid();
        else
            entityMap = mWorld->EntityMap();

        // MutliThread sync variables
        mWorkingThreadCount.store( 0 );
        mFinished.store( false );
        mAllPolygonsInFOV.clear();
        mOutputTriangles->clear();

        auto transformation = entity->GetComponentByIDAs< ::nCore::nECS::nComponent::cTransformation* >( "transformation" );
        auto direction      = entity->GetComponentByIDAs< ::nCore::nECS::nComponent::cDirection* >( "direction" );
        auto fieldofview    = entity->GetComponentByIDAs< ::nCore::nECS::nComponent::cFieldOfView* >( "fieldofview" );

        std::vector< sf::VertexArray > trianglesToComputeVector;    // Needed to extract bbox
        sf::VertexArray subFov;

        // Important points of main FOV
        sf::Vector2f fovOrigin( float( transformation->X()), float( transformation->Y()) ); // Base point of the triangle
        sf::Vector2f fovB;

        // Get FOV triangles
        float semiAngle = float(fieldofview->Angle() / 2.0F);
        sf::Transform rotation;
        rotation.rotate( semiAngle );

        // This vector is the vector of the bisectrice of the FOV
        sf::Vector2f baseVector = direction->AsVector2F() * float(fieldofview->Distance() );
        fovB = rotation.transformPoint( baseVector ); // This will be the most top left point of the first triangle
        // Reset the rotation
        rotation = rotation.Identity;
        // Set it to FOV angle / number of split, negative so it goes right and not left
        rotation.rotate( float( -fieldofview->Angle() ) / FOVSplitThreshold );

        mTriangles.clear();
        for( int i = 0; i < FOVSplitThreshold; ++i )
        {
            // We start a new triangle, that has ptA and ptB from the previous
            subFov.clear();
            subFov.append( fovOrigin );
            subFov.append( fovOrigin + fovB );
            // And for each split, we apply the rotation to the top left point, creating the top right point
            // for the Nth triangle
            fovB = rotation.transformPoint( fovB );
            subFov.append( fovB + fovOrigin );
            mTriangles.push_back( subFov );

            eAssociatedTriangle assocTriangle;
            assocTriangle.mTriangle = subFov;
            mTriangleQueue->push( assocTriangle );
        }

        mFOVBBox = ::nCore::nMath::GetTriangleSetBBox( mTriangles );

        std::set< ::nCore::nECS::nCore::cEntity* > entitiesInFOVBBox;
        entityMap->GetEntitiesInBoundingBox( &entitiesInFOVBBox, mFOVBBox );

        mAllPolygonsInFOV.clear();
        for( auto &v : entitiesInFOVBBox )
        {
            // We don't analyse the watcher itself
            if( v == entity )
                continue;

            auto transformationENT = v->GetComponentByIDAs< ::nCore::nECS::nComponent::cTransformation* >( "transformation" );
            sf::Vector2f entPosVec( float( transformationENT->X()), float( transformationENT->Y()) );

            sf::VertexArray analysisVisibleBox( sf::Points, 4 );
            analysisVisibleBox[ 0 ] = entPosVec;
            analysisVisibleBox[ 1 ] = entPosVec + sf::Vector2f( 0.0F, float( transformationENT->H()) );
            analysisVisibleBox[ 2 ] = entPosVec + transformationENT->SizeAsVector2F();
            analysisVisibleBox[ 3 ] = entPosVec + sf::Vector2f( float( transformationENT->W()), 0.0F );

            mAllPolygonsInFOV.push_back( analysisVisibleBox );
        }

        mThreadHandles.clear();

        auto threadMethod = [ this ]( int iIndex ){

            std::vector < sf::VertexArray > output;
            output.reserve( 256 );

            while( mFinished.load() == false )
            {
                eAssociatedTriangle triangleToCompute;

                std::unique_lock< std::mutex > lck( mMutex );
                if( !mTriangleQueue->empty() )
                {
                    triangleToCompute = mTriangleQueue->front();
                    mTriangleQueue->pop();
                    ++mWorkingThreadCount;

                    lck.unlock();
                }
                else if( mFinished.load() == false ) // because it could have changed since the while ! :) :) :)
                {
                    mSynchronizeCV.wait( lck );
                    continue;
                }
                else
                {
                    continue;
                }

                int collisisonPolyIndex = -1;

                for( int j = 0; j < mAllPolygonsInFOV.size(); ++j )
                {
                    if( ::nCore::nMath::VectorContainsElement( triangleToCompute.mVisitedPolygonIndexes, j ) )
                        continue;

                    bool generatedSubTriangles = ::nCore::nMath::TriangleSubDivisionUsingPolygon( &output, triangleToCompute.mTriangle, mAllPolygonsInFOV[ j ] );

                    // This will push associated index every time we got sub triangles
                    // So polyIndex count == number of times we generated sub triangles
                    if( generatedSubTriangles )
                    {
                        collisisonPolyIndex = j;
                        break;
                    }
                }

                // Writing results in one lock
                std::unique_lock< std::mutex > lck2( mMutex );

                if( collisisonPolyIndex == -1 )
                {
                    mOutputTriangles->push_back( triangleToCompute.mTriangle );
                }
                else
                {
                    for( auto triangle : output )
                    {
                        eAssociatedTriangle subTriangle = triangleToCompute;
                        subTriangle.mTriangle = triangle;
                        subTriangle.mVisitedPolygonIndexes.push_back( collisisonPolyIndex );
                        mTriangleQueue->push( subTriangle );
                    }
                }

                --mWorkingThreadCount;
                if( mWorkingThreadCount == 0 && mTriangleQueue->empty() )
                    mFinished.store( true );

                lck2.unlock();
                mSynchronizeCV.notify_all();
            }
        };

        unsigned int availableThreadsCount = ::nCore::nBase::nThread::cThreadProcessor::Instance()->GetAvailableThreadCount();

        if( availableThreadsCount == 0 )
            availableThreadsCount = 1;

        for( unsigned int i = 0; i < availableThreadsCount; ++i )
        {
            mThreadHandles.push_back( ::nCore::nBase::nThread::cThreadProcessor::Instance()->AffectFunctionToThreadAndStart( threadMethod, true ) );
        }

        for( int i = 0; i < mThreadHandles.size(); ++i )
        {
            ::nCore::nBase::nThread::cThreadHandle& handle = mThreadHandles[ i ];
            ::nCore::nBase::nThread::cThread* t = handle.GetThread();
            if( t )
                t->WaitEndOfTask();
        }

        mFOVDrawer.push_back( *mOutputTriangles );
    }

    // ========================================
    // ============= SINGLE THREAD ============
    // ========================================

    //::nCore::nMapping::cEntityGrid* entityMap = ::nECS::cScreenEntityMap::Instance()->mEntityGrid;

    //mFOVDrawer.clear();

    //for( int i = 0; i < mWatchers.size(); ++i )
    //{
    //    cEntity* entity = mWatchers[ i ];

    //    //mTransformationAngleSort = mTransformationAngleSort.Identity;
    //    mTriangles.clear();

    //    auto position = dynamic_cast< cPosition* >( entity->GetComponentByID( "position" ) );
    //    auto size = dynamic_cast< cSize* >( entity->GetComponentByID( "size" ) );
    //    auto direction = dynamic_cast< cDirection* >( entity->GetComponentByID( "direction" ) );
    //    auto fieldofview = dynamic_cast< cFieldOfView* >( entity->GetComponentByID( "fieldofview" ) );

    //    // This is the transformation that allows to go in the watcher's referential
    //    //mTransformationAngleSort.rotate( float( RadToDeg( GetAngleBetweenVectors( gXAxisVector, direction->mDirection ) ) ) );
    //    //mTransformationAngleSort.translate( -position->mPosition );
    //    sf::VertexArray subFov;

    //    // Important points of main FOV
    //    sf::Vector2f fovOrigin;
    //    sf::Vector2f fovB;

    //    // Get FOV triangles
    //    fovOrigin = position->AsVector2F(); // Base point of the triangle
    //    float semiAngle = float( fieldofview->Angle() / 2.0F );
    //    sf::Transform rotation;
    //    rotation.rotate( semiAngle );

    //    // This vector is the vector of the bisectrice of the FOV
    //    sf::Vector2f baseVector = direction->AsVector2F() * float( fieldofview->Distance() );
    //    fovB = rotation.transformPoint( baseVector ); // This will be the most top left point of the first triangle
    //                                                  // Reset the rotation
    //    rotation = rotation.Identity;
    //    // Set it to FOV angle / number of split, negative so it goes right and not left
    //    rotation.rotate( float( -fieldofview->Angle() ) / FOVSplitThreshold );

    //    for( int i = 0; i < FOVSplitThreshold; ++i )
    //    {
    //        // We start a new triangle, that has ptA and ptB from the previous
    //        subFov.clear();
    //        subFov.append( fovOrigin );
    //        subFov.append( fovOrigin + fovB );
    //        // And for each split, we apply the rotation to the top left point, creating the top right point
    //        // for the Nth triangle
    //        fovB = rotation.transformPoint( fovB );
    //        subFov.append( fovB + fovOrigin );
    //        mTriangles.push_back( subFov );
    //    }

    //    //mFOVBBox = GetTriangleSetBBox( mTriangles ); // Function was removed, too lazy to seek in through git
    //    mFOVBBox = sf::FloatRect( 0.0, 0.0, 800, 600 );

    //    std::vector< cEntity* > entitiesInFOVBBox;
    //    entityMap->GetEntitiesInBoundingBox( &entitiesInFOVBBox, mFOVBBox );

    //    for( auto v : entitiesInFOVBBox )
    //    {
    //        // We don't analyse the watcher itself
    //        if( v == entity )
    //            continue;

    //        auto positionENT = dynamic_cast< cPosition* >( v->GetComponentByID( "position" ) );
    //        auto sizeENT = dynamic_cast< cSize* >( v->GetComponentByID( "size" ) );

    //        sf::VertexArray analysisVisibleBox( sf::Points, 4 );
    //        sf::Vector2f posEntVector = positionENT->AsVector2F();
    //        sf::Vector2f sizeEntVector = sizeENT->AsVector2F();
    //        analysisVisibleBox[ 0 ] = posEntVector;
    //        analysisVisibleBox[ 1 ] = posEntVector + sf::Vector2f( 0.0F, sizeEntVector.y );
    //        analysisVisibleBox[ 2 ] = posEntVector + sizeEntVector;
    //        analysisVisibleBox[ 3 ] = posEntVector + sf::Vector2f( sizeEntVector.x, 0.0F );

    //        // No threading
    //        std::vector< sf::VertexArray >  subTriangles;
    //        for( int i = int( mTriangles.size() - 1 ); i >= 0; --i )
    //        {
    //            ::nCore::nMath::TriangleSubDivisionUsingPolygon( &subTriangles, mTriangles[ i ], analysisVisibleBox );

    //            if( subTriangles.size() > 0 )
    //            {
    //                mTriangles.erase( mTriangles.begin() + i );
    //                for( auto sub : subTriangles )
    //                {
    //                    mTriangles.push_back( sub );
    //                }
    //            }
    //        }// /No threading

    //    }// for all entities

    //    mFOVDrawer.push_back( mTriangles );
    //}
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------ Entity
// -------------------------------------------------------------------------------------


void
cSightSystem::IncomingEntity( ::nCore::nECS::nCore::cEntity* iEntity )
{
    auto transformation = iEntity->GetComponentByID( "transformation" );
    auto direction      = iEntity->GetComponentByID( "direction" );
    auto fieldofview    = iEntity->GetComponentByID( "fieldofview" );

    if( iEntity->HasTag( "hero" ) )
        mPointsOfInterest.push_back( iEntity );
    else if( transformation && direction && fieldofview )
        mWatchers.push_back( iEntity );

    AcceptEntity( iEntity );
}


void
cSightSystem::EntityLost( ::nCore::nECS::nCore::cEntity * iEntity )
{
    auto transformation = iEntity->GetComponentByID( "transformation " );
    auto direction = iEntity->GetComponentByID( "direction" );
    auto fieldofview = iEntity->GetComponentByID( "fieldofview" );

    if( iEntity->HasTag( "hero" ) )
    {
        for( int i = 0; i < mPointsOfInterest.size(); ++i )
        {
            if( iEntity == mPointsOfInterest[ i ] )
                mPointsOfInterest.erase( mPointsOfInterest.begin() + i );
        }
    }
    else if( transformation && direction && fieldofview )
    {
        for( int i = 0; i < mWatchers.size(); ++i )
        {
            if( iEntity == mWatchers[ i ] )
                mWatchers.erase( mWatchers.begin() + i );
        }
    }

    tSuperClass::EntityLost( iEntity );
}


} // namespace nSystem
} // namespace nECS
} // namespace nCore

