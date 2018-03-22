#include "SightSystem.h"

#include "Math/Utils.h"
#include "Math/Ray.h"

#include "ECS/Core/Entity.h"
#include "ECS/Utilities/EntityParser.h"
#include "ECS/Core/World.h"

#include "GameMockup/GameApplication.h"
#include "GameMockup/Components/FieldOfView.h"
#include "GameMockup/Components/Position.h"
#include "GameMockup/Components/Size.h"
#include "GameMockup/Components/Direction.h"

#include "Mapping/PhysicEntityGrid.h"

#include "SFML/Graphics.hpp"

#include <iostream>


#define FOVSplitThreshold 1

// -------------------------------------------------------------------------------------
// ------------------------------------------------------------ Construction/Destruction
// -------------------------------------------------------------------------------------


cSightSystem::~cSightSystem()
{
}


cSightSystem::cSightSystem() :
    tSuperClass()
{
}


// -------------------------------------------------------------------------------------
// ----------------------------------------------------------------------- Init/Finalize
// -------------------------------------------------------------------------------------


void
cSightSystem::Initialize()
{
    mInterestingHitPoints.setPrimitiveType( sf::Points );
}


void
cSightSystem::Finalize()
{
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------- Update/Draw
// -------------------------------------------------------------------------------------


void
cSightSystem::Draw( sf::RenderTarget* iRenderTarget )
{
    //cEntityGrid* entityMap = cGameApplication::App()->EntityMap();

    // BBOx of fov
    //sf::RectangleShape bbox( sf::Vector2f( mFOVBBox.width, mFOVBBox.height ) );
    //bbox.setPosition( sf::Vector2f( mFOVBBox.left, mFOVBBox.top ) );
    //iRenderTarget->draw( bbox );

    //for( int i = 0; i < mTriangles.size(); ++i )
    //{
    //    mTriangles[ i ].setPrimitiveType( sf::Triangles );
    //    for( int j = 0; j < mTriangles[ i ].getVertexCount(); ++j )
    //    {
    //        mTriangles[ i ][ j ].color = sf::Color( i*20, i*10, 0, 100 );
    //    }

    //    iRenderTarget->draw( mTriangles[ i ] );
    //}

    //for( int i = 0; i < mDEBUGClips.size(); ++i )
    //{
    //    mDEBUGClips[ i ].setPrimitiveType( sf::TriangleFan );
    //    for( int j = 0; j < mDEBUGClips[ i ].getVertexCount(); ++j )
    //    {
    //        mDEBUGClips[ i ][ j ].color = sf::Color( 255, 150, 0, 255 );
    //    }

    //    iRenderTarget->draw( mDEBUGClips[ i ] );
    //}

    //if( mTriangles.size() > 0 )
    //{
    //    sf::VertexArray fovTrans = mTriangles[ 0 ];
    //    TransformPolygonUsingTransformation( &fovTrans, mTransformationAngleSort );
    //    iRenderTarget->draw( fovTrans );

    //    for( auto ent : mDEBUGEntities )
    //    {
    //        sf::VertexArray trans = ent;
    //        TransformPolygonUsingTransformation( &trans, mTransformationAngleSort );
    //        trans.setPrimitiveType( sf::Quads );
    //        iRenderTarget->draw( trans );
    //    }
    //}
    //iRenderTarget->draw( mDEBUGHitPoints );

    //for( int i = 0; i < mResultingSubTriangles.size(); ++i )
    //{
    //    for( int j = 0; j < mResultingSubTriangles[ i ].getVertexCount(); ++j )
    //    {
    //        mResultingSubTriangles[ i ].setPrimitiveType( sf::Triangles );
    //        mResultingSubTriangles[ i ][ j ].color = sf::Color( (50*i)%255, ( 100 * i ) % 255, ( 10 * i ) % 255, 50 );
    //    }
    //    iRenderTarget->draw( mResultingSubTriangles[ i ] );
    //}
    //iRenderTarget->draw( mInterestingHitPoints );

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

    //sf::CircleShape hitPoint( 6, 4 );
    //hitPoint.setFillColor( sf::Color::Red );
    //for( int i = 0; i < mDEBUGMinMax.getVertexCount(); ++i )
    //{
    //    hitPoint.setPosition( mDEBUGMinMax[ i ].position );
    //    hitPoint.setOrigin( sf::Vector2f( 3.0F,3.0F ) );
    //    iRenderTarget->draw( hitPoint );
    //}
    //
    //sf::CircleShape fovHP( 6, 4 );
    //fovHP.setFillColor( sf::Color::Blue );
    //for( int i = 0; i < mDEBUGFovHP.getVertexCount(); ++i )
    //{
    //    fovHP.setPosition( mDEBUGFovHP[ i ].position );
    //    fovHP.setOrigin( sf::Vector2f( 3.0F, 3.0F ) );
    //    iRenderTarget->draw( fovHP );
    //}
}


void
cSightSystem::Update( unsigned int iDeltaTime )
{
    cEntityGrid* entityMap = cGameApplication::App()->EntityMap();

    //mDEBUGClips.clear();
    //mDEBUGEntities.clear();
    //mDEBUGMinMax.clear();
    //mDEBUGFovHP.clear();
    mFOVDrawer.clear();

    sf::Vector2f fovOrigin;
    sf::Vector2f fovB;

    for( int i = 0; i < mWatchers.size(); ++i )
    {
        cEntity* entity = mWatchers[ i ];

        //mTransformationAngleSort = mTransformationAngleSort.Identity;
        mTriangles.clear();
        mResultingSubTriangles.clear();

        auto position = dynamic_cast< cPosition* >( entity->GetComponentByName( "position" ) );
        auto size = dynamic_cast< cSize* >( entity->GetComponentByName( "size" ) );
        auto direction = dynamic_cast< cDirection* >( entity->GetComponentByName( "direction" ) );
        auto fieldofview = dynamic_cast< cFieldOfView* >( entity->GetComponentByName( "fieldofview" ) );

        // This is the transformation that allows to go in the watcher's referential
        //mTransformationAngleSort.rotate( float( RadToDeg( GetAngleBetweenVectors( gXAxisVector, direction->mDirection ) ) ) );
        //mTransformationAngleSort.translate( -position->mPosition );
        sf::VertexArray subFov;

        // Get FOV triangles
        fovOrigin = position->mPosition; // Base point of the triangle
        float semiAngle = float(fieldofview->mAngle / 2.0F);
        sf::Transform rotation;
        rotation.rotate( semiAngle );

        // This vector is the vector of the bisectrice of the FOV
        sf::Vector2f baseVector = direction->mDirection * float(fieldofview->mDistance);
        fovB = rotation.transformPoint( baseVector ); // This will be the most top left point of the first triangle
        // Reset the rotation
        rotation = rotation.Identity;
        // Set it to FOV angle / number of split, negative so it goes right and not left
        rotation.rotate( float( -fieldofview->mAngle ) / FOVSplitThreshold );

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
        }

        mFOVBBox = GetTriangleSetBBox( mTriangles );

        std::vector< cEntity* > entitiesInFOVBBox;
        entityMap->GetEntitiesInBoundingBox( &entitiesInFOVBBox, mFOVBBox );

        for( auto v : entitiesInFOVBBox )
        {
            // We don't analyse the watcher itself
            if( v == entity )
                continue;

            auto positionENT = dynamic_cast< cPosition* >( v->GetComponentByName( "position" ) );
            auto sizeENT = dynamic_cast< cSize* >( v->GetComponentByName( "size" ) );

            sf::VertexArray analysisVisibleBox( sf::Points, 4 );
            analysisVisibleBox[ 0 ] = positionENT->mPosition;
            analysisVisibleBox[ 1 ] = positionENT->mPosition + sf::Vector2f( 0.0F, sizeENT->mSize.y );
            analysisVisibleBox[ 2 ] = positionENT->mPosition + sizeENT->mSize;
            analysisVisibleBox[ 3 ] = positionENT->mPosition + sf::Vector2f( sizeENT->mSize.x, 0.0F );

            std::vector< sf::VertexArray > subTriangles;
            for( int i = int( mTriangles.size() - 1 ); i >= 0; --i )
            {
                TriangleSubDivisionUsingPolygon( &subTriangles, mTriangles[ i ], analysisVisibleBox );

                if( subTriangles.size() > 0 )
                {
                    for( auto triangle : subTriangles )
                        mTriangles.push_back( triangle );

                    mTriangles.erase( mTriangles.begin() + i );
                }

                subTriangles.clear();
            }

        }// for all entities

        mFOVDrawer.push_back( mTriangles );
    }
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------ Entity
// -------------------------------------------------------------------------------------


void
cSightSystem::IncomingEntity( cEntity* iEntity )
{
    auto position       = iEntity->GetComponentByName( "position" );
    auto size           = iEntity->GetComponentByName( "size" );
    auto direction      = iEntity->GetComponentByName( "direction" );
    auto fieldofview    = iEntity->GetComponentByName( "fieldofview" );

    if( iEntity->HasTag( "hero" ) )
        mPointsOfInterest.push_back( iEntity );
    else if( position && size && direction && fieldofview )
        mWatchers.push_back( iEntity );

    AcceptEntity( iEntity );
}


void
cSightSystem::EntityLost( cEntity * iEntity )
{
    auto position = iEntity->GetComponentByName( "position" );
    auto size = iEntity->GetComponentByName( "size" );
    auto direction = iEntity->GetComponentByName( "direction" );
    auto fieldofview = iEntity->GetComponentByName( "fieldofview" );

    if( iEntity->HasTag( "hero" ) )
    {
        for( int i = 0; i < mPointsOfInterest.size(); ++i )
        {
            if( iEntity == mPointsOfInterest[ i ] )
                mPointsOfInterest.erase( mPointsOfInterest.begin() + i );
        }
    }
    else if( position && size && direction && fieldofview )
    {
        for( int i = 0; i < mWatchers.size(); ++i )
        {
            if( iEntity == mWatchers[ i ] )
                mWatchers.erase( mWatchers.begin() + i );
        }
    }

    tSuperClass::EntityLost( iEntity );
}



