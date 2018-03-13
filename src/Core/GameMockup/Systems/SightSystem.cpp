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


#define FOVSplitThreshold 5

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

    for( int i = 0; i < mDEBUGRays.size(); ++i )
    {
        sf::VertexArray line( sf::Lines, 2 );
        line[ 0 ].position = mDEBUGRays[ i ].mPoint;
        line[ 0 ].color = sf::Color( 255, 0, 0 );
        line[ 1 ].position = mDEBUGRays[ i ].mPoint + mDEBUGRays[ i ].mDirection;
        line[ 1 ].color = sf::Color( 255, 0, 0 );
        iRenderTarget->draw( line );
    }

    for( int i = 0; i < mDEBUGHitPoints.getVertexCount(); ++i )
    {
        mDEBUGHitPoints[ i ].color = sf::Color( 255, 0, 0 );
    }
    iRenderTarget->draw( mDEBUGHitPoints );

}


void
cSightSystem::Update( unsigned int iDeltaTime )
{
    cEntityGrid* entityMap = cGameApplication::App()->EntityMap();

    mTransformation = mTransformation.Identity;
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

        mTransformation.rotate( float(RadToDeg( -GetAngleBetweenVectors( gXAxisVector, direction->mDirection ) )) + 180.0F );
        mTransformation.translate( -position->mPosition );
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

            for( int i = 0; i < mTriangles.size(); ++i )
            {
                sf::VertexArray clipedPol = ClipPolygonPolygon( analysisVisibleBox, mTriangles[ i ] );
                std::vector< cEdgeF > rayList;

                // Now we have the clipped polygon, we want to cast rays towards every vertexes to see
                // which part of the FOV is obstructed
                for( int j = 0; j < clipedPol.getVertexCount(); ++j )
                {
                    // First we get for each vertex, the ray from fov's origin
                    // Then we store it, so we end up with the list of rays
                    // We'll then be able to remove rays that are identical, to simplify things
                    sf::Vector2f vectorDirectionToPolygonEdge = Normale( clipedPol[ j ].position - fovOrigin );
                    vectorDirectionToPolygonEdge *= float( fieldofview->mDistance + 5.0F ); // +5 to ensure intersection

                    // There it is
                    cEdgeF ray = cEdgeF::MakePointDirection( fovOrigin, vectorDirectionToPolygonEdge );

                    // This looks ugly as hell, but no better idea atm
                    bool addNewRay = true;
                    for( auto rayFromList : rayList )
                    {
                        if( Collinear( ray.mDirection, rayFromList.mDirection ) )
                        {
                            addNewRay = false;
                            break;
                        }
                    }
                    if( addNewRay )
                    {
                        mDEBUGRays.push_back( ray );
                        rayList.push_back( ray );
                    }
                }

                for( auto ray : rayList )
                {
                    // Now, for each edge of the clipped polygon, we intersect with that ray
                    // and harvest all intersections
                    std::vector< cEdgeF > clipPolEdges;

                    // Collision between ray and clipped Polygon will be stored in this vector
                    std::vector< sf::Vector2f > hitPoints;

                    ExtractEdgesFromPolygon( &clipPolEdges, clipedPol );
                    for( auto edge : clipPolEdges )
                    {
                        float paramA;
                        float paramB;

                        cEdgeF::Intersect( &paramA, &paramB, edge, ray );
                        if( ( paramA > 0.0F && paramA < 1.0F ) // If actual intersection that is NOT on an exact vertex
                            && ( paramB > 0.0F && paramB < 1.0F ) )
                        {
                            mDEBUGHitPoints.append( ray.mPoint + paramB * ray.mDirection );
                            hitPoints.push_back( ray.mPoint + paramB * ray.mDirection );
                        }
                        else if( abs(paramA) < kEpsilonF || abs(paramA - 1.0F) < kEpsilonF ) // If it is on an exact vertex
                        {
                            mDEBUGHitPoints.append( ray.mPoint + ray.mDirection );
                            hitPoints.push_back( ray.mPoint + paramB * ray.mDirection );
                        }

                        // In all cases, we should have 2 intersections with clippedPolygon
                        int a = 2;
                    }
                }

                if( clipedPol.getVertexCount() > 0 )
                    mDEBUGClips.push_back( clipedPol );
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

