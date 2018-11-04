#include "Core.ECS.System.InputConverter.h"


#include "Core.ECS.Component.UserInput.h"
#include "Core.ECS.Core.Entity.h"
#include "Core.Shortcuts.Shortcuts.h"


#include <iostream>


namespace nCore {
namespace nECS {
namespace nSystem {


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------ Construction/Destruction
// -------------------------------------------------------------------------------------


cInputConverter::~cInputConverter()
{
}


cInputConverter::cInputConverter() :
    tSuperClass( "InputConverter" )
{
    ConnectToEvents();
}


cInputConverter::cInputConverter( const cInputConverter & iSys ) :
    tSuperClass( iSys )
{
}


::nCore::nECS::nCore::cSystem*
cInputConverter::Clone() const
{
    return  new cInputConverter( *this );
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------- Update/Draw
// -------------------------------------------------------------------------------------


void
cInputConverter::Update( unsigned int iDeltaTime )
{
    for( int i = 0; i < mEntityGroup.size(); ++i )
    {
        ::nCore::nECS::nCore::cEntity* entity = mEntityGroup[ i ];

        auto userinput = entity->GetComponentByIDAs< ::nCore::nECS::nComponent::cUserInput* >( "userinput" );
    }
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------ Entity
// -------------------------------------------------------------------------------------


void
cInputConverter::IncomingEntity( ::nCore::nECS::nCore::cEntity * iEntity )
{
    auto userinput = iEntity->GetComponentByID( "userinput" );

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
        ::nCore::nECS::nCore::cEntity* entity = mEntityGroup[ i ];

        auto userinput = entity->GetComponentByIDAs< ::nCore::nECS::nComponent::cUserInput* >( "userinput" );
        userinput->mActions.push_back( ::nCore::nShortcuts::cShortcuts::Instance()->GetActionForKey( iEvent.key.code ) );
    }
}


void
cInputConverter::KeyReleased( const sf::Event & iEvent )
{
    for( int i = 0; i < mEntityGroup.size(); ++i )
    {
        ::nCore::nECS::nCore::cEntity* entity = mEntityGroup[ i ];

        auto userinput = entity->GetComponentByIDAs< ::nCore::nECS::nComponent::cUserInput* >( "userinput" );

        for( int i = 0; i < userinput->mActions.size(); ++i )
        {
            if( userinput->mActions[ i ] == ::nCore::nShortcuts::cShortcuts::Instance()->GetActionForKey( iEvent.key.code ) )
                userinput->mActions.erase( userinput->mActions.begin() + i );
        }
    }
}


} // namespace nSystem
} // namespace nECS
} // namespace nCore

