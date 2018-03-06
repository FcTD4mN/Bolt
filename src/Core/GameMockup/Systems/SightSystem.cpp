#include "SightSystem.h"

#include "ECS/Core/Entity.h"
#include "ECS/Utilities/EntityParser.h"
#include "ECS/Core/World.h"

#include "GameMockup/GameApplication.h"
#include "GameMockup/Components/FieldOfView.h"
#include "GameMockup/Components/Position.h"
#include "GameMockup/Components/Size.h"
#include "GameMockup/Components/Direction.h"

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
}


void
cSightSystem::Update( unsigned int iDeltaTime )
{
    for( int i = 0; i < mEntityGroup.size(); ++i )
    {
        cEntity* entity = mEntityGroup[ i ];

        auto position = dynamic_cast< cPosition* >( entity->GetComponentByName( "position" ) );
        auto size = dynamic_cast< cSize* >( entity->GetComponentByName( "size" ) );
        auto direction = dynamic_cast< cDirection* >( entity->GetComponentByName( "direction" ) );
        auto fieldofview = dynamic_cast< cFieldOfView* >( entity->GetComponentByName( "fieldofview" ) );


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

