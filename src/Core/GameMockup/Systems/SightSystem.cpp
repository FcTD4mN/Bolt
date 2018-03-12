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

    sf::VertexArray lines( sf::LinesStrip, 2 );
    lines[ 0 ].position = mDEBUGSightPA;
    lines[ 0 ].color = sf::Color( 20, 20, 255, 100 );
    lines[ 1 ].position = mDEBUGSightPA + mDEBUGSightLine;
    lines[ 1 ].color = sf::Color( 20, 20, 255, 100 );

    sf::ConvexShape sight;
    sight.setPointCount( 3 );
    sight.setPoint( 0, mFOVTriangle.mA );
    sight.setPoint( 1, mFOVTriangle.mB );
    sight.setPoint( 2, mFOVTriangle.mC );
    sight.setFillColor( sf::Color( 0, 0, 255, 100 ) );

    iRenderTarget->draw( lines );
    iRenderTarget->draw( sight );
}


void
cSightSystem::Update( unsigned int iDeltaTime )
{
    cEntityGrid* entityMap = cGameApplication::App()->EntityMap();

    mTransformation = mTransformation.Identity;

    sf::Vector2f fovA;
    sf::Vector2f fovB;
    sf::Vector2f fovC;

    // These names sux ass, but i didn't have any better
    sf::Vector2f analysis;

    for( int i = 0; i < mEntityGroup.size(); ++i )
    {
        cEntity* entity = mEntityGroup[ i ];

        auto position = dynamic_cast< cPosition* >( entity->GetComponentByName( "position" ) );
        auto size = dynamic_cast< cSize* >( entity->GetComponentByName( "size" ) );
        auto direction = dynamic_cast< cDirection* >( entity->GetComponentByName( "direction" ) );
        auto fieldofview = dynamic_cast< cFieldOfView* >( entity->GetComponentByName( "fieldofview" ) );

        mTransformation.rotate( RadToDeg( -GetAngleBetweenVectors( gXAxisVector, direction->mDirection ) ) + 180.0F );
        mTransformation.translate( -position->mPosition );

        // Get FOV triangle
        fovA = position->mPosition;
        float semiAngle = float(fieldofview->mAngle / 2.0F);
        sf::Transform rotation;
        rotation.rotate( semiAngle );

        sf::Vector2f baseVector = direction->mDirection * float(fieldofview->mDistance);
        fovB = rotation.transformPoint( baseVector );

        rotation.rotate( float(-fieldofview->mAngle) );
        fovC = rotation.transformPoint( baseVector );

        // Translation
        fovB += fovA;
        fovC += fovA;

        mFOVTriangle.mA = fovA;
        mFOVTriangle.mB = fovB;
        mFOVTriangle.mC = fovC;

        sf::VertexArray fov;
        fov.append( fovA );
        fov.append( fovB );
        fov.append( fovC );

        std::vector< cEntity* > entitiesInFOVBBox;
        entityMap->GetEntitiesInBoundingBox( &entitiesInFOVBBox, fov.getBounds() );

        for( auto v : entitiesInFOVBBox )
        {
            auto positionENT = dynamic_cast< cPosition* >( v->GetComponentByName( "position" ) );
            auto sizeENT = dynamic_cast< cSize* >( v->GetComponentByName( "size" ) );


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

