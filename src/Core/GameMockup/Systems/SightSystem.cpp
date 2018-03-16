#include "SightSystem.h"

#include "Math/Utils.h"

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
    cEntityGrid* entityMap = cGameApplication::App()->EntityMap();

    // BBOx of fov
    //sf::RectangleShape bbox( sf::Vector2f( mFOVBBox.width, mFOVBBox.height ) );
    //bbox.setPosition( sf::Vector2f( mFOVBBox.left, mFOVBBox.top ) );
    //iRenderTarget->draw( bbox );

    for( int i = 0; i < mTriangles.size(); ++i )
    {
        mTriangles[ i ].setPrimitiveType( sf::Triangles );
        for( int j = 0; j < mTriangles[ i ].getVertexCount(); ++j )
        {
            mTriangles[ i ][ j ].color = sf::Color( i*20, i*10, 0, 100 );
        }

        iRenderTarget->draw( mTriangles[ i ] );
    }

    //for( int i = 0; i < mDEBUGClips.size(); ++i )
    //{
    //    mDEBUGClips[ i ].setPrimitiveType( sf::TriangleFan );
    //    for( int j = 0; j < mDEBUGClips[ i ].getVertexCount(); ++j )
    //    {
    //        mDEBUGClips[ i ][ j ].color = sf::Color( 255, 150, 0, 255 );
    //    }

    //    iRenderTarget->draw( mDEBUGClips[ i ] );
    //}

    //for( int i = 0; i < mDEBUGRays.size(); ++i )
    //{
    //    sf::VertexArray line( sf::Lines, 2 );
    //    line[ 0 ].position = mDEBUGRays[ i ].mPoint;
    //    line[ 0 ].color = sf::Color( i*50, 0, 0 );
    //    line[ 1 ].position = mDEBUGRays[ i ].mPoint + mDEBUGRays[ i ].mDirection;
    //    line[ 1 ].color = sf::Color( i*50, 0, 0 );
    //    iRenderTarget->draw( line );
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
    iRenderTarget->draw( mInterestingHitPoints );
}


void
cSightSystem::Update( unsigned int iDeltaTime )
{
    cEntityGrid* entityMap = cGameApplication::App()->EntityMap();

    mTransformationAngleSort = mTransformationAngleSort.Identity;
    mTriangles.clear();
    mDEBUGClips.clear();
    mDEBUGEntities.clear();
    mDEBUGRays.clear();
    mDEBUGHitPoints.clear();

    sf::Vector2f fovOrigin;
    sf::Vector2f fovB;

    for( int i = 0; i < mEntityGroup.size(); ++i )
    {
        cEntity* entity = mEntityGroup[ i ];

        auto position = dynamic_cast< cPosition* >( entity->GetComponentByName( "position" ) );
        auto size = dynamic_cast< cSize* >( entity->GetComponentByName( "size" ) );
        auto direction = dynamic_cast< cDirection* >( entity->GetComponentByName( "direction" ) );
        auto fieldofview = dynamic_cast< cFieldOfView* >( entity->GetComponentByName( "fieldofview" ) );

        // This is the transformation that allows to go in the watcher's referential
        mTransformationAngleSort.rotate( float( RadToDeg( GetAngleBetweenVectors( gXAxisVector, direction->mDirection ) ) ) );
        mTransformationAngleSort.translate( -position->mPosition );
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

        //for( auto v : entitiesInFOVBBox )
        for( auto v : mPointsOfInterest )
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
            mDEBUGEntities.push_back( analysisVisibleBox );

            // For each triangle in the set, we split it according to object in the fov
            for( int i = 0; i < mTriangles.size(); ++i )
            {
                sf::VertexArray clipedPol = ClipPolygonPolygon( analysisVisibleBox, mTriangles[ i ] );
                mDEBUGClips.push_back( clipedPol );
                std::vector< cEdgeF > rayList;
                mInterestingHitPoints.clear();

                // Now we have the clipped polygon, we want to cast rays towards every vertexes to see
                // which part of the FOV is obstructed

                // =============================================================
                // =============================================================

                // The first ray we add is the left part of the sub fov
                cEdgeF firstTamere = cEdgeF::MakePointPoint( mTriangles[ i ][ 0 ].position, mTriangles[ i ][ 2 ].position );
                rayList.push_back( firstTamere );
                mDEBUGRays.push_back( firstTamere );

                // Then, one ray per vertex of the polygon
                for( int j = 0; j < clipedPol.getVertexCount(); ++j )
                {
                    // First we get for each vertex, the ray from fov's origin
                    // Then we store it, so we end up with the list of rays
                    // We'll then be able to remove rays that are identical, to simplify things
                    sf::Vector2f vectorDirectionToPolygonEdge = Normale( clipedPol[ j ].position - fovOrigin );
                    vectorDirectionToPolygonEdge *= float( fieldofview->mDistance );

                    // There it is
                    cEdgeF ray = cEdgeF::MakePointDirection( fovOrigin, vectorDirectionToPolygonEdge );

                    if( AddElementToVectorUnique( ray, &rayList ) )
                        mDEBUGRays.push_back( ray );
                }

                // Then finally the last ray is the right part of the sub fov
                cEdgeF lastTamere = cEdgeF::MakePointPoint( mTriangles[ i ][ 0 ].position, mTriangles[ i ][ 1 ].position );
                if( AddElementToVectorUnique( lastTamere, &rayList ) )
                    mDEBUGRays.push_back( lastTamere );


                // Then we intersect every rays against polygon
                // ============================================
                // ============================================
                for( auto ray : rayList )
                {
                    // Now, for each edge of the clipped polygon, we intersect with that ray
                    // and harvest all intersections
                    std::vector< cEdgeF > clipPolEdges;

                    // Collision between ray and clipped Polygon will be stored in this vertexArray
                    sf::VertexArray hitPoints;

                    ExtractEdgesFromPolygon( &clipPolEdges, clipedPol );
                    for( auto edge : clipPolEdges )
                    {
                        float paramA;
                        float paramB;

                        if( cEdgeF::Intersect( &paramA, &paramB, edge, ray ) )
                        {
                            if( ( paramA > kEpsilonF && paramA < 1.0F - kEpsilonF ) // If actual intersection that is NOT on an exact vertex
                                && ( paramB > kEpsilonF && paramB < 1.0F - kEpsilonF ) )
                            {
                                mDEBUGHitPoints.append( ray.mPoint + paramB * ray.mDirection );
                                mDEBUGHitPoints[ mDEBUGHitPoints.getVertexCount() - 1 ].color = sf::Color::Red;
                                hitPoints.append( ray.mPoint + paramB * ray.mDirection );
                            }
                            else if( abs(paramA) < kEpsilonF || abs(paramA - 1.0F) < kEpsilonF ) // If it is on an exact vertex
                            {
                                mDEBUGHitPoints.append( ray.mPoint + paramB * ray.mDirection );
                                mDEBUGHitPoints[ mDEBUGHitPoints.getVertexCount() - 1 ].color = sf::Color::Green;

                                sf::Vector2f vertex = ray.mPoint + paramB * ray.mDirection;
                                AddElementToVertexArrayUnique( vertex, &hitPoints );
                            }
                        }
                    }

                    // If only one local or no intersections with polygon, it means the ray will cast up to the fov's limit
                    // So the interesting hitpoint of that ray is fov's limit
                    if( hitPoints.getVertexCount() <= 1 )
                    {
                        // We get fov's limit, which is the edge 1-2 (0 is always the origin point of fov)
                        // Then we intersect with the ray to get the exact point
                        cEdgeF fovLimit = cEdgeF::MakePointPoint( mTriangles[ i ][1].position, mTriangles[ i ][2].position );
                        float paramA;
                        float paramB;
                        cEdgeF::Intersect( &paramA, &paramB, fovLimit, ray );

                        mInterestingHitPoints.append( ray.mPoint + paramB * ray.mDirection );

                        // We also push the single intersection, to be able to build subTriangles
                        if( hitPoints.getVertexCount() == 1 )
                            mInterestingHitPoints.append( hitPoints[ 0 ].position );
                    }
                    else if( hitPoints.getVertexCount() > 1 )
                    {
                        // If there were more than one intersection, we keep the closest one
                        // So we transform points into watcher's referential
                        // That has its fov pointing upwards => the smallest the X, the closest it is
                        TransformPolygonUsingTransformation( &hitPoints, mTransformationAngleSort );
                        hitPoints = SortVertexesByX( hitPoints );
                        TransformPolygonUsingTransformation( &hitPoints, mTransformationAngleSort.getInverse() );
                        mInterestingHitPoints.append( hitPoints[ 0 ].position );
                    }
                }

                TransformPolygonUsingTransformation( &mInterestingHitPoints, mTransformationAngleSort );
                sf::VertexArray iHitPointXSorted = SortVertexesByAngle( mInterestingHitPoints );
                TransformPolygonUsingTransformation( &iHitPointXSorted, mTransformationAngleSort.getInverse() );
                TransformPolygonUsingTransformation( &mInterestingHitPoints, mTransformationAngleSort.getInverse() );
                // Need to retransform mInteresing points ?

                //sf::VertexArray subTriangle( sf::Triangles, 3 );
                //subTriangle[ 0 ] = fovOrigin;

                //for( auto hp : mInterestingHitPoints )
                //{
                //    mResultingSubTriangles.push_back( subTriangle );
                //}
            }
        }
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
        AcceptEntity( iEntity );
}

