#include "Application/Application.h"

#include "Screen/Screen.h"


// Game.Application, not here, this is just for testing purposes
#include "MainMenu/MainMenu.h"
#include "MainMenu/MenuItem/MenuItem.Callback.h"
#include "MainMenu/MenuItem/MenuItem.PageSwaper.h"
#include "MainMenu/MenuPage/MenuPage.h"
#include "Screen/ScreenMainMenu.h"
// ----------------------------------------

// -------------------------------------------------------------------------------------
// ------------------------------------------------------------ Construction/Destruction
// -------------------------------------------------------------------------------------


cApplication::cApplication() :
    mMainWindow( 0 )
{
}


// -------------------------------------------------------------------------------------
// ----------------------------------------------------------------------- Getter/Setter
// -------------------------------------------------------------------------------------


sf::RenderWindow*
cApplication::Window()
{
    return  mMainWindow;
}


void
cApplication::SetAppTitle( const std::string & iTitle )
{
    mMainWindow->setTitle( iTitle );
}


void
cApplication::SetAppDefaultResolution( int iW, int iH )
{
    mMainWindow->setSize( sf::Vector2u( iW, iH ) );
}


// -------------------------------------------------------------------------------------
// ----------------------------------------------------------------------- Init/Finalize
// -------------------------------------------------------------------------------------


void
cApplication::Initialize()
{
    mMainWindow = new  sf::RenderWindow( sf::VideoMode( 800, 600 ), "Game Title" );
}


void
cApplication::Finalize()
{
    delete  mMainWindow;
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------- Update/Draw
// -------------------------------------------------------------------------------------


void
cApplication::Update()
{
    cScreen* currentScreen = mScreenStack.back();
    if( currentScreen )
        currentScreen->Update();
}


void
cApplication::Draw( sf::RenderTarget* iRenderTarget )
{
    cScreen* currentScreen = mScreenStack.back();
    if( currentScreen )
        currentScreen->Draw( iRenderTarget );
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------ Screen
// -------------------------------------------------------------------------------------


void
cApplication::PushScreen( cScreen * iScreen )
{
    mScreenStack.push_back( iScreen );
}


void
cApplication::PopScreen()
{
    mScreenStack.pop_back();
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------ Events
// -------------------------------------------------------------------------------------


void
cApplication::HandleEvents( sf::Event & iEvent )
{
    switch( iEvent.type )
    {
        case sf::Event::Closed:
            mMainWindow->close();
            break;
        case sf::Event::Resized:
            Resized( iEvent );
            break;
        case sf::Event::LostFocus:
            LostFocus( iEvent );
            break;
        case sf::Event::GainedFocus:
            GainedFocus( iEvent );
            break;
        case sf::Event::TextEntered:
            TextEntered( iEvent );
            break;
        case sf::Event::KeyPressed:
            KeyPressed( iEvent );
            break;
        case sf::Event::KeyReleased:
            KeyReleased( iEvent );
            break;
        case sf::Event::MouseWheelMoved:
            MouseWheelMoved( iEvent );
            break;
        case sf::Event::MouseWheelScrolled:
            MouseWheelScrolled( iEvent );
            break;
        case sf::Event::MouseButtonPressed:
            MouseButtonPressed( iEvent );
            break;
        case sf::Event::MouseButtonReleased:
            MouseButtonReleased( iEvent );
            break;
        case sf::Event::MouseMoved:
            MouseMoved( iEvent );
            break;
        case sf::Event::MouseEntered:
            MouseEntered( iEvent );
            break;
        case sf::Event::MouseLeft:
            MouseLeft( iEvent );
            break;
        case sf::Event::JoystickButtonPressed:
            JoystickButtonPressed( iEvent );
            break;
        case sf::Event::JoystickButtonReleased:
            JoystickButtonReleased( iEvent );
            break;
        case sf::Event::JoystickMoved:
            JoystickMoved( iEvent );
            break;
        case sf::Event::JoystickConnected:
            JoystickConnected( iEvent );
            break;
        case sf::Event::JoystickDisconnected:
            JoystickDisconnected( iEvent );
            break;
        case sf::Event::TouchBegan:
            TouchBegan( iEvent );
            break;
        case sf::Event::TouchMoved:
            TouchMoved( iEvent );
            break;
        case sf::Event::TouchEnded:
            TouchEnded( iEvent );
            break;
        case sf::Event::SensorChanged:
            SensorChanged( iEvent );
            break;
        default:
            break;
    }
}

void
cApplication::Closed( const sf::Event& iEvent )
{
}


void
cApplication::Resized( const sf::Event& iEvent )
{
}


void
cApplication::LostFocus( const sf::Event& iEvent )
{
}


void
cApplication::GainedFocus( const sf::Event& iEvent )
{
}


void
cApplication::TextEntered( const sf::Event& iEvent )
{
}


void
cApplication::KeyPressed( const sf::Event& iEvent )
{
    cScreen* currentScreen = mScreenStack.back();
    if( currentScreen )
        currentScreen->KeyPressed( iEvent );
}


void
cApplication::KeyReleased( const sf::Event& iEvent )
{
    cScreen* currentScreen = mScreenStack.back();
    if( currentScreen )
        currentScreen->KeyReleased( iEvent );
}


void
cApplication::MouseWheelMoved( const sf::Event& iEvent )
{
    cScreen* currentScreen = mScreenStack.back();
    if( currentScreen )
        currentScreen->MouseWheelMoved( iEvent );
}


void
cApplication::MouseWheelScrolled( const sf::Event& iEvent )
{
    cScreen* currentScreen = mScreenStack.back();
    if( currentScreen )
        currentScreen->MouseWheelScrolled( iEvent );
}


void
cApplication::MouseButtonPressed( const sf::Event& iEvent )
{
    cScreen* currentScreen = mScreenStack.back();
    if( currentScreen )
        currentScreen->MouseButtonPressed( iEvent );
}


void
cApplication::MouseButtonReleased( const sf::Event& iEvent )
{
    cScreen* currentScreen = mScreenStack.back();
    if( currentScreen )
        currentScreen->MouseButtonReleased( iEvent );
}


void
cApplication::MouseMoved( const sf::Event& iEvent )
{
    cScreen* currentScreen = mScreenStack.back();
    if( currentScreen )
        currentScreen->MouseMoved( iEvent );
}


void
cApplication::MouseEntered( const sf::Event& iEvent )
{
    cScreen* currentScreen = mScreenStack.back();
    if( currentScreen )
        currentScreen->MouseEntered( iEvent );
}


void
cApplication::MouseLeft( const sf::Event& iEvent )
{
    cScreen* currentScreen = mScreenStack.back();
    if( currentScreen )
        currentScreen->MouseLeft( iEvent );
}


void
cApplication::JoystickButtonPressed( const sf::Event& iEvent )
{
    cScreen* currentScreen = mScreenStack.back();
    if( currentScreen )
        currentScreen->JoystickButtonPressed( iEvent );
}


void
cApplication::JoystickButtonReleased( const sf::Event& iEvent )
{
    cScreen* currentScreen = mScreenStack.back();
    if( currentScreen )
        currentScreen->JoystickButtonReleased( iEvent );
}


void
cApplication::JoystickMoved( const sf::Event& iEvent )
{
    cScreen* currentScreen = mScreenStack.back();
    if( currentScreen )
        currentScreen->JoystickMoved( iEvent );
}


void
cApplication::JoystickConnected( const sf::Event& iEvent )
{
    cScreen* currentScreen = mScreenStack.back();
    if( currentScreen )
        currentScreen->JoystickConnected( iEvent );
}


void
cApplication::JoystickDisconnected( const sf::Event& iEvent )
{
    cScreen* currentScreen = mScreenStack.back();
    if( currentScreen )
        currentScreen->JoystickDisconnected( iEvent );
}


void
cApplication::TouchBegan( const sf::Event& iEvent )
{
    cScreen* currentScreen = mScreenStack.back();
    if( currentScreen )
        currentScreen->TouchBegan( iEvent );
}


void
cApplication::TouchMoved( const sf::Event& iEvent )
{
    cScreen* currentScreen = mScreenStack.back();
    if( currentScreen )
        currentScreen->TouchMoved( iEvent );
}


void
cApplication::TouchEnded( const sf::Event& iEvent )
{
    cScreen* currentScreen = mScreenStack.back();
    if( currentScreen )
        currentScreen->TouchEnded( iEvent );
}


void
cApplication::SensorChanged( const sf::Event& iEvent )
{
    cScreen* currentScreen = mScreenStack.back();
    if( currentScreen )
        currentScreen->SensorChanged( iEvent );
}
