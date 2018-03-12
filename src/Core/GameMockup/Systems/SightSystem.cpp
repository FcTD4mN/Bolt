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

    for( int i = 0; i < mTriangles.size(); ++i )
    {
        mTriangles[ i ].setPrimitiveType( sf::Triangles );
        for( int j = 0; j < mTriangles[ i ].getVertexCount(); ++j )
        {
            mTriangles[ i ][ j ].color = sf::Color( i*20, i*10, 0, 100 );
        }

        iRenderTarget->draw( mTriangles[ i ] );
    }

    for( int i = 0; i < mDEBUGClips.size(); ++i )
    {
        mDEBUGClips[ i ].setPrimitiveType( sf::TriangleFan );
        for( int j = 0; j < mDEBUGClips[ i ].getVertexCount(); ++j )
        {
            mDEBUGClips[ i ][ j ].color = sf::Color( 255, 150, 0, 255 );
        }

        iRenderTarget->draw( mDEBUGClips[ i ] );
    }
}


void
cSightSystem::Update( unsigned int iDeltaTime )
{
    cEntityGrid* entityMap = cGameApplication::App()->EntityMap();

    mTransformation = mTransformation.Identity;
    mTriangles.clear();
    mDEBUGClips.clear();
    mDEBUGEntities.clear();

    sf::Vector2f fovA;
    sf::Vector2f fovB;

    for( int i = 0; i < mEntityGroup.size(); ++i )
    {
        cEntity* entity = mEntityGroup[ i ];

        auto position = dynamic_cast< cPosition* >( entity->GetComponentByName( "position" ) );
        auto size = dynamic_cast< cSize* >( entity->GetComponentByName( "size" ) );
        auto direction = dynamic_cast< cDirection* >( entity->GetComponentByName( "direction" ) );
        auto fieldofview = dynamic_cast< cFieldOfView* >( entity->GetComponentByName( "fieldofview" ) );

        mTransformation.rotate( RadToDeg( -GetAngleBetweenVectors( gXAxisVector, direction->mDirection ) ) + 180.0F );
        mTransformation.translate( -position->mPosition );
        sf::VertexArray subFov;
        sf::VertexArray completeFov;

        // Get FOV triangles
        fovA = position->mPosition; // Base point of the triangle
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

        // We need the complete FOV to check the bounding box and ask entitymap for all entities
        completeFov.append( fovA );
        completeFov.append( fovB + fovA );

        for( int i = 0; i < FOVSplitThreshold; ++i )
        {
            // We start a new triangle, that has ptA and ptB from the previous
            subFov.clear();
            subFov.append( fovA );
            subFov.append( fovA + fovB );
            // And for each split, we apply the rotation to the top left point, creating the top right point
            // for the Nth triangle
            fovB = rotation.transformPoint( fovB );
            subFov.append( fovB + fovA );
            mTriangles.push_back( subFov );
        }

        completeFov.append( fovB + fovA );

        std::vector< cEntity* > entitiesInFOVBBox;
        entityMap->GetEntitiesInBoundingBox( &entitiesInFOVBBox, completeFov.getBounds() );

        //for( auto v : mPointsOfInterest )
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

            for( int i = 0; i < mTriangles.size(); ++i )
            {
                sf::VertexArray clipedPol = ClipPolygonPolygon( analysisVisibleBox, mTriangles[ i ] );
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

