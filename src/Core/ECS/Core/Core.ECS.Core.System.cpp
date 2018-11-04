#include "Core.ECS.Core.System.h"


#include "Core.ECS.Core.Entity.h"
#include "Core.ECS.Core.World.h"


namespace nCore {
namespace nECS {
namespace nCore {


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------ Construction
// -------------------------------------------------------------------------------------


cSystem::~cSystem()
{
}


cSystem::cSystem( const std::string& iName ) :
    mName( iName ),
    mWorld( 0 ),
    mEventConnected( false )
{
}


cSystem::cSystem( const cSystem & iSystem ) :
    mName( iSystem.mName ),
    mWorld( 0 ), // don't copy this, just set it back as needed
    mEventConnected( iSystem.mEventConnected )
{
    // This is a basic clone, more like a new done from an already existing system
    if( iSystem.mEventConnected )
        ConnectToEvents();
}


// -------------------------------------------------------------------------------------
// ----------------------------------------------------------------------- Init/Finalize
// -------------------------------------------------------------------------------------


void
cSystem::Initialize()
{
    // Do nothing here
}


void
cSystem::Finalize()
{
    mEntityGroup.clear();
}


// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------- Access/Get
// -------------------------------------------------------------------------------------


const std::string &
cSystem::Name() const
{
    return  mName;
}


void
cSystem::ConnectToEvents()
{
    mEventConnected = true;
    if( mWorld )
        mWorld->ConnectSystemToEvents( this );
}


void
cSystem::DisconnectFromEvents()
{
    mEventConnected = false;
    if( mWorld )
        mWorld->DisconnectSystemToEvents( this );
}


bool
cSystem::IsEventConnected() const
{
    return  mEventConnected;
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------- Update/Draw
// -------------------------------------------------------------------------------------


void
cSystem::Draw( sf::RenderTarget* iRenderTarget )
{
    // Does nothing
}


void
cSystem::DrawEntity( sf::RenderTarget * iRenderTarget, cEntity * iEntity )
{
    // Does nothing
}


void
cSystem::Update( unsigned int iDeltaTime )
{
    // Does nothing
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------ Entity
// -------------------------------------------------------------------------------------


void
cSystem::IncomingEntity( cEntity * iEntity )
{
    // Empty system won't do anything
}


void
cSystem::EntityLost( cEntity* iEntity )
{
    for( int i = 0; i < mEntityGroup.size(); ++i )
    {
        if( mEntityGroup[ i ] == iEntity )
            mEntityGroup.erase( mEntityGroup.begin() + i );
    }
}


void
cSystem::AcceptEntity( cEntity * iEntity )
{
    mEntityGroup.push_back( iEntity );
    iEntity->AddSystemObserver( this );
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------ Events
// -------------------------------------------------------------------------------------


void
cSystem::Resized( const sf::Event& iEvent )
{
    // Does nothing
}


void
cSystem::KeyPressed( const sf::Event& iEvent )
{
    // Does nothing
}


void
cSystem::KeyReleased( const sf::Event& iEvent )
{
    // Does nothing
}


void
cSystem::MouseWheelMoved( const sf::Event& iEvent )
{
    // Does nothing
}


void
cSystem::MouseWheelScrolled( const sf::Event& iEvent )
{
    // Does nothing
}


void
cSystem::MouseButtonPressed( const sf::Event& iEvent )
{
    // Does nothing
}


void
cSystem::MouseButtonReleased( const sf::Event& iEvent )
{
    // Does nothing
}


void
cSystem::MouseMoved( const sf::Event& iEvent )
{
    // Does nothing
}


void
cSystem::MouseEntered( const sf::Event& iEvent )
{
    // Does nothing
}


void
cSystem::MouseLeft( const sf::Event& iEvent )
{
    // Does nothing
}


void
cSystem::JoystickButtonPressed( const sf::Event& iEvent )
{
    // Does nothing
}


void
cSystem::JoystickButtonReleased( const sf::Event& iEvent )
{
    // Does nothing
}


void
cSystem::JoystickMoved( const sf::Event& iEvent )
{
    // Does nothing
}


void
cSystem::JoystickConnected( const sf::Event& iEvent )
{
    // Does nothing
}


void
cSystem::JoystickDisconnected( const sf::Event& iEvent )
{
    // Does nothing
}


void
cSystem::TouchBegan( const sf::Event& iEvent )
{
    // Does nothing
}


void
cSystem::TouchMoved( const sf::Event& iEvent )
{
    // Does nothing
}


void
cSystem::TouchEnded( const sf::Event& iEvent )
{
    // Does nothing
}


void
cSystem::SensorChanged( const sf::Event& iEvent )
{
    // Does nothing
}


} // namespace nCore
} // namespace nECS
} // namespace nCore

