#include "Core.Screen.ScreenNoProject.h"


namespace nScreen {


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------ Construction
// -------------------------------------------------------------------------------------


cScreenNoProject::~cScreenNoProject()
{
}


cScreenNoProject::cScreenNoProject()
{
}


// -------------------------------------------------------------------------------------
// ----------------------------------------------------------------------- Init/Finalize
// -------------------------------------------------------------------------------------


void
cScreenNoProject::Initialize()
{
    tSuperClass::Initialize();

    mLoaded = true;
}


void
cScreenNoProject::Finalize()
{
    tSuperClass::Finalize();
}


// -------------------------------------------------------------------------------------
// -------------------------------------------------------------- Main Running functions
// -------------------------------------------------------------------------------------


void
cScreenNoProject::Draw( sf::RenderTarget* iRenderTarget )
{
}


void
cScreenNoProject::Update( unsigned int iDeltaTime )
{
    // Does nothing
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------ Events
// -------------------------------------------------------------------------------------


void
cScreenNoProject::Resized( const sf::Event& iEvent )
{
    // Does nothing
}


void
cScreenNoProject::KeyPressed( const sf::Event& iEvent )
{
    // Does nothing
}


void
cScreenNoProject::KeyReleased( const sf::Event& iEvent )
{
    // Does nothing
}


void
cScreenNoProject::MouseWheelMoved( const sf::Event& iEvent )
{
    // Does nothing
}


void
cScreenNoProject::MouseWheelScrolled( const sf::Event& iEvent )
{
    // Does nothing
}


void
cScreenNoProject::MouseButtonPressed( const sf::Event& iEvent )
{
    // Does nothing
}


void
cScreenNoProject::MouseButtonReleased( const sf::Event& iEvent )
{
    // Does nothing
}


void
cScreenNoProject::MouseMoved( const sf::Event& iEvent )
{
    // Does nothing
}


void
cScreenNoProject::MouseEntered( const sf::Event& iEvent )
{
    // Does nothing
}


void
cScreenNoProject::MouseLeft( const sf::Event& iEvent )
{
    // Does nothing
}


void
cScreenNoProject::JoystickButtonPressed( const sf::Event& iEvent )
{
    // Does nothing
}


void
cScreenNoProject::JoystickButtonReleased( const sf::Event& iEvent )
{
    // Does nothing
}


void
cScreenNoProject::JoystickMoved( const sf::Event& iEvent )
{
    // Does nothing
}


void
cScreenNoProject::JoystickConnected( const sf::Event& iEvent )
{
    // Does nothing
}


void
cScreenNoProject::JoystickDisconnected( const sf::Event& iEvent )
{
    // Does nothing
}


void
cScreenNoProject::TouchBegan( const sf::Event& iEvent )
{
    // Does nothing
}


void
cScreenNoProject::TouchMoved( const sf::Event& iEvent )
{
    // Does nothing
}


void
cScreenNoProject::TouchEnded( const sf::Event& iEvent )
{
    // Does nothing
}


void
cScreenNoProject::SensorChanged( const sf::Event& iEvent )
{
    // Does nothing
}


} // namespace nScreen

