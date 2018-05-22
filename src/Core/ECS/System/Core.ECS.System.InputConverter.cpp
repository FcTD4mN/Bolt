#include "Core.ECS.System.InputConverter.h"


#include "Core.ECS.Component.UserInput.h"
#include "Core.ECS.Core.Entity.h"
#include "Core.Shortcuts.Shortcuts.h"


#include <iostream>


namespace nECS {


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
        userinput->mActions.push_back( ::nShortcuts:: cShortcuts::Instance()->GetActionForKey( iEvent.key.code ) );
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
            if( userinput->mActions[ i ] == ::nShortcuts::cShortcuts::Instance()->GetActionForKey( iEvent.key.code ) )
                userinput->mActions.erase( userinput->mActions.begin() + i );
        }
    }
}


} // namespace nECS

