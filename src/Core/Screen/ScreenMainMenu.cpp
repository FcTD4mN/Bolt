#include "ScreenMainMenu.h"

#include "MainMenu/MainMenu.h"

// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------ Construction
// -------------------------------------------------------------------------------------


cScreenMainMenu::~cScreenMainMenu()
{
}


cScreenMainMenu::cScreenMainMenu( cMainMenu* iMainMenu ) :
    mMainMenu( iMainMenu )
{
}


// -------------------------------------------------------------------------------------
// ----------------------------------------------------------------------- Init/Finalize
// -------------------------------------------------------------------------------------


void
cScreenMainMenu::Initialize()
{

}


void
cScreenMainMenu::Finalize()
{

}


// -------------------------------------------------------------------------------------
// -------------------------------------------------------------- Main Running functions
// -------------------------------------------------------------------------------------


void
cScreenMainMenu::Draw( sf::RenderTarget* iRenderTarget )
{
    mMainMenu->Draw( iRenderTarget );
}


void
cScreenMainMenu::Update( unsigned int iDeltaTime )
{
    // Does nothing
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------ Events
// -------------------------------------------------------------------------------------


void
cScreenMainMenu::Resized( const sf::Event& iEvent )
{
    // Does nothing
}


void
cScreenMainMenu::KeyPressed( const sf::Event& iEvent )
{
    // Does nothing
}


void
cScreenMainMenu::KeyReleased( const sf::Event& iEvent )
{
    // Does nothing
}


void
cScreenMainMenu::MouseWheelMoved( const sf::Event& iEvent )
{
    // Does nothing
}


void
cScreenMainMenu::MouseWheelScrolled( const sf::Event& iEvent )
{
    // Does nothing
}


void
cScreenMainMenu::MouseButtonPressed( const sf::Event& iEvent )
{
    // Does nothing
}


void
cScreenMainMenu::MouseButtonReleased( const sf::Event& iEvent )
{
    mMainMenu->MouseClick( iEvent.mouseButton.x, iEvent.mouseButton.y );
}


void
cScreenMainMenu::MouseMoved( const sf::Event& iEvent )
{
    // Does nothing
}


void
cScreenMainMenu::MouseEntered( const sf::Event& iEvent )
{
    // Does nothing
}


void
cScreenMainMenu::MouseLeft( const sf::Event& iEvent )
{
    // Does nothing
}


void
cScreenMainMenu::JoystickButtonPressed( const sf::Event& iEvent )
{
    // Does nothing
}


void
cScreenMainMenu::JoystickButtonReleased( const sf::Event& iEvent )
{
    // Does nothing
}


void
cScreenMainMenu::JoystickMoved( const sf::Event& iEvent )
{
    // Does nothing
}


void
cScreenMainMenu::JoystickConnected( const sf::Event& iEvent )
{
    // Does nothing
}


void
cScreenMainMenu::JoystickDisconnected( const sf::Event& iEvent )
{
    // Does nothing
}


void
cScreenMainMenu::TouchBegan( const sf::Event& iEvent )
{
    // Does nothing
}


void
cScreenMainMenu::TouchMoved( const sf::Event& iEvent )
{
    // Does nothing
}


void
cScreenMainMenu::TouchEnded( const sf::Event& iEvent )
{
    // Does nothing
}


void
cScreenMainMenu::SensorChanged( const sf::Event& iEvent )
{
    // Does nothing
}





