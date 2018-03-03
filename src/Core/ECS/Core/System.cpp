#include "ECS/Core/System.h"

#include "ECS/Core/Entity.h"

// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------ Construction
// -------------------------------------------------------------------------------------


cSystem::~cSystem()
{
}


cSystem::cSystem()
{
}


// -------------------------------------------------------------------------------------
// -------------------------------------------------------------- Main Running functions
// -------------------------------------------------------------------------------------


void
cSystem::Draw( sf::RenderTarget* iRenderTarget )
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





