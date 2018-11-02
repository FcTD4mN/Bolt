#include "GameMockup.Screen.ConsoleScreen.h"


#include "GameMockup.Application.GameApplication.h"


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
    ::nCore::nApplication::cApplication::App()->SetAppTitle( "CONSOLE" );

    mConsoleWidget = new  ::nCore::nGUI::cConsoleWidget();
    sf::Vector2f  availableGeometry = sf::Vector2f( float( ::nCore::nApplication::cApplication::App()->Window()->getSize().x ),
                                                    float( ::nCore::nApplication::cApplication::App()->Window()->getSize().y ) );
    mConsoleWidget->SetSize( availableGeometry );
    mConsoleWidget->SetPosition( sf::Vector2f() );

    ::nCore::nApplication::cApplication::App()->Window()->setKeyRepeatEnabled( true );
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


} // namespace nScreen

