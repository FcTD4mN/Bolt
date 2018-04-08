#include "GameMockup.Screen.ConsoleScreen.h"

//#include "ECS/Entity.h"
//#include "ECS/EntityParser.h"
//#include "ECS/World.h"

#include "GameMockup.Application.GameApplication.h"
/*
#include "GameMockup/Components/Color.h"
#include "GameMockup/Components/Position.h"
#include "GameMockup/Components/Size.h"
#include "GameMockup/Components/SpriteAnimated.h"
#include "GameMockup/Components/UserInput.h"
*/

namespace nScreen {

// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------ Construction
// -------------------------------------------------------------------------------------


cConsoleScreen::~cConsoleScreen()
{
}


cConsoleScreen::cConsoleScreen() :
    mConsoleWidget( 0 )
{
}


// -------------------------------------------------------------------------------------
// ----------------------------------------------------------------------- Init/Finalize
// -------------------------------------------------------------------------------------


void
cConsoleScreen::Initialize()
{
    ::nApplication::cGameApplication::App()->SetAppTitle( "CONSOLE" );

    mConsoleWidget = new  ::nGUI::cConsoleWidget();
    sf::Vector2f  availableGeometry = sf::Vector2f( float( ::nApplication::cGameApplication::App()->Window()->getSize().x ),
                                                    float( ::nApplication::cGameApplication::App()->Window()->getSize().y ) );
    mConsoleWidget->SetSize( availableGeometry );
    mConsoleWidget->SetPosition( sf::Vector2f() );

    ::nApplication::cGameApplication::App()->Window()->setKeyRepeatEnabled( true );
}


void
cConsoleScreen::Finalize()
{
    if( mConsoleWidget )
    {
        delete  mConsoleWidget;
        mConsoleWidget = 0;
    }
}


// -------------------------------------------------------------------------------------
// -------------------------------------------------------------- Main Running functions
// -------------------------------------------------------------------------------------


void
cConsoleScreen::Draw( sf::RenderTarget* iRenderTarget )
{
    mConsoleWidget->Draw( iRenderTarget );
}


void
cConsoleScreen::Update( unsigned int iDeltaTime )
{
    mConsoleWidget->Update( iDeltaTime );
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------ Events
// -------------------------------------------------------------------------------------


void
cConsoleScreen::Resized( const sf::Event& iEvent )
{
    // Does nothing
}


void
cConsoleScreen::TextEntered( const sf::Event& iEvent )
{
    mConsoleWidget->TextEntered( iEvent );
}


void
cConsoleScreen::KeyPressed( const sf::Event& iEvent )
{
    mConsoleWidget->KeyPressed( iEvent );
}


void
cConsoleScreen::KeyReleased( const sf::Event& iEvent )
{
    mConsoleWidget->KeyReleased( iEvent );
}


void
cConsoleScreen::MouseWheelMoved( const sf::Event& iEvent )
{
    // Does nothing
}


void
cConsoleScreen::MouseWheelScrolled( const sf::Event& iEvent )
{
    // Does nothing
}


void
cConsoleScreen::MouseButtonPressed( const sf::Event& iEvent )
{
    // Does nothing
}


void
cConsoleScreen::MouseButtonReleased( const sf::Event& iEvent )
{
}


void
cConsoleScreen::MouseMoved( const sf::Event& iEvent )
{
    // Does nothing
}


void
cConsoleScreen::MouseEntered( const sf::Event& iEvent )
{
    // Does nothing
}


void
cConsoleScreen::MouseLeft( const sf::Event& iEvent )
{
    // Does nothing
}


void
cConsoleScreen::JoystickButtonPressed( const sf::Event& iEvent )
{
    // Does nothing
}


void
cConsoleScreen::JoystickButtonReleased( const sf::Event& iEvent )
{
    // Does nothing
}


void
cConsoleScreen::JoystickMoved( const sf::Event& iEvent )
{
    // Does nothing
}


void
cConsoleScreen::JoystickConnected( const sf::Event& iEvent )
{
    // Does nothing
}


void
cConsoleScreen::JoystickDisconnected( const sf::Event& iEvent )
{
    // Does nothing
}


void
cConsoleScreen::TouchBegan( const sf::Event& iEvent )
{
    // Does nothing
}


void
cConsoleScreen::TouchMoved( const sf::Event& iEvent )
{
    // Does nothing
}


void
cConsoleScreen::TouchEnded( const sf::Event& iEvent )
{
    // Does nothing
}


void
cConsoleScreen::SensorChanged( const sf::Event& iEvent )
{
    // Does nothing
}

} //nScreen
