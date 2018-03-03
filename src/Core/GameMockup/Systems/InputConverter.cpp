#include "InputConverter.h"

#include "ECS/Core/Entity.h"

#include "GameMockup/GameApplication.h"
#include "GameMockup/Components/UserInput.h"

#include "Shortcuts/Shortcuts.h"

#include <iostream>

// -------------------------------------------------------------------------------------
// ------------------------------------------------------------ Construction/Destruction
// -------------------------------------------------------------------------------------


cInputConverter::~cInputConverter()
{
}


cInputConverter::cInputConverter() :
    tSuperClass()
{
}


// -------------------------------------------------------------------------------------
// ----------------------------------------------------------------------- Init/Finalize
// -------------------------------------------------------------------------------------


void
cInputConverter::Initialize()
{
}


void
cInputConverter::Finalize()
{
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------- Update/Draw
// -------------------------------------------------------------------------------------


void
cInputConverter::Draw( sf::RenderTarget* iRenderTarget )
{
}


void
cInputConverter::Update( unsigned int iDeltaTime )
{
    for( int i = 0; i < mEntityGroup.size(); ++i )
    {
        cEntity* entity = mEntityGroup[ i ];

        auto userinput = dynamic_cast< cUserInput* >( entity->GetComponentByName( "userinput" ) );
    }
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------ Entity
// -------------------------------------------------------------------------------------


void
cInputConverter::IncomingEntity( cEntity * iEntity )
{
    auto userinput = iEntity->GetComponentByName( "userinput" );

    if( userinput )
        AcceptEntity( iEntity );
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------ Events
// -------------------------------------------------------------------------------------


void
cInputConverter::KeyPressed( const sf::Event & iEvent )
{
    for( int i = 0; i < mEntityGroup.size(); ++i )
    {
        cEntity* entity = mEntityGroup[ i ];

        auto userinput = dynamic_cast< cUserInput* >( entity->GetComponentByName( "userinput" ) );
        userinput->mActions.push_back( cGameApplication::App()->ShortcutEngine()->GetActionForKey( iEvent.key.code ) );
    }
}


void
cInputConverter::KeyReleased( const sf::Event & iEvent )
{
    for( int i = 0; i < mEntityGroup.size(); ++i )
    {
        cEntity* entity = mEntityGroup[ i ];

        auto userinput = dynamic_cast< cUserInput* >( entity->GetComponentByName( "userinput" ) );

        for( int i = 0; i < userinput->mActions.size(); ++i )
        {
            if( userinput->mActions[ i ] == cGameApplication::App()->ShortcutEngine()->GetActionForKey( iEvent.key.code ) )
                userinput->mActions.erase( userinput->mActions.begin() + i );
        }
    }
}


