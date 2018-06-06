#include "GameMockup.Application.GameApplication.h"


#include "Core.ECS.Core.Entity.h"
#include "Core.ECS.Core.World.h"
#include "Core.ECS.Utilities.ComponentRegistry.h"
#include "Core.ECS.Utilities.SystemRegistry.h"
#include "Core.ECS.Utilities.EntityParser.h"

#include "Core.MainMenu.MainMenu.h"
#include "Core.MainMenu.ItemCallback.h"
#include "Core.MainMenu.ItemPageSwaper.h"
#include "Core.MainMenu.MenuPage.h"

#include "Core.Screen.Screen.h"
#include "Core.Screen.ScreenMainMenu.h"

#include "Core.Shortcuts.Shortcuts.h"

#include "GameMockup.ECS.System.SquareController.h"

#include "GameMockup.Screen.GameScreen.h"
#include "GameMockup.Screen.InfiltratorScreen.h"
#include "GameMockup.Screen.OpenGLRenderSceneScreen.h"


namespace nApplication {


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------ Construction/Destruction
// -------------------------------------------------------------------------------------


cGameApplication::cGameApplication()
{
}


// -------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------- Instance
// -------------------------------------------------------------------------------------


//static
cGameApplication*
cGameApplication::App()
{
    static cGameApplication* gApplication = 0;
    if( !gApplication )
        gApplication = new cGameApplication();

    return  gApplication;
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------ Access
// -------------------------------------------------------------------------------------


::nECS::cWorld*
cGameApplication::World()
{
    return  0;
}


// -------------------------------------------------------------------------------------
// ----------------------------------------------------------------------- Init/Finalize
// -------------------------------------------------------------------------------------


void
cGameApplication::Initialize()
{
    // =========== GAME SPECIFIC SYSTEMS ===========
    ::nECS::cSystemRegistry::Instance()->RegisterSystem( new  ::nECS::cSquareController() );

    // =========== APPLICATION/PROJET INIT ===========
    tSuperClass::Initialize();

    // =========== GENERAL CONFIG ===========
    mMainWindow->setKeyRepeatEnabled( false );

    // ============= SHORTCUTS =============
    ::nShortcuts::cShortcuts::Instance()->Initialize();

    return;

    sf::Vector2u winSize = mMainWindow->getSize();

    // ========= MAIN MENU =========
    ::nMainMenu::cMainMenu* menu = new ::nMainMenu::cMainMenu();
    ::nMainMenu::cMenuPage* pageOne = new ::nMainMenu::cMenuPage( menu );
    pageOne->Size( float(winSize.x), float(winSize.y) );

    ::nMainMenu::cMenuPage* pageTwo = new ::nMainMenu::cMenuPage( menu );
    pageTwo->Size( float(winSize.x), float(winSize.y) );

    sf::RectangleShape rect( sf::Vector2f( 200, 50 ) );

    ::nMainMenu::cItemPageSwaper* itemOne  = new ::nMainMenu::cItemPageSwaper( menu, "FirstPage0", rect, 1 );
    ::nMainMenu::cItemPageSwaper* itemOne2 = new ::nMainMenu::cItemPageSwaper( menu, "FirstPage1", rect, 1 );

    ::nMainMenu::cItemPageSwaper* itemTwo  = new ::nMainMenu::cItemPageSwaper( menu, "SecondPage0", rect, 0 );
    ::nMainMenu::cItemCallback*   itemTwo2 = new ::nMainMenu::cItemCallback( menu, "SecondPage1", rect, []()
    {
        cGameApplication::App()->Window()->setTitle( "CLICK" );
    } );

    ::nMainMenu::cItemCallback*   gameScreenSwap = new ::nMainMenu::cItemCallback( menu, "Game", rect, []()
    {
        cGameApplication::App()->PushScreen( new ::nScreen::cGameScreen() );
    } );

    ::nMainMenu::cItemCallback*   infiltratorScreenSwap = new ::nMainMenu::cItemCallback( menu, "Infiltrator", rect, [](){
        cGameApplication::App()->PushScreen( new ::nScreen::cInfiltratorScreen() );
    } );

    ::nMainMenu::cItemCallback*   openGLRenderSceneScreenSwap = new ::nMainMenu::cItemCallback( menu, "OpenGL", rect, [](){
        cGameApplication::App()->PushScreen( new ::nScreen::cOpenGLRenderSceneScreen() );
    } );

    pageOne->AddItem( itemOne );
    pageOne->AddItem( itemOne2 );
    pageOne->AddItem( gameScreenSwap );
    pageOne->AddItem( infiltratorScreenSwap );
    pageOne->AddItem( openGLRenderSceneScreenSwap );
    pageTwo->AddItem( itemTwo );
    pageTwo->AddItem( itemTwo2 );

    menu->AddPage( pageOne );
    menu->AddPage( pageTwo );
    menu->CurrentPage( 0 );

    ::nScreen::cScreenMainMenu* mainMenuScreen = new ::nScreen::cScreenMainMenu( menu );
    PushScreen( mainMenuScreen );
}


void
cGameApplication::Finalize()
{
    tSuperClass::Finalize();

    ::nECS::cComponentRegistry::Instance()->Finalize();

    delete mWorld;
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------- Update/Draw
// -------------------------------------------------------------------------------------


void
cGameApplication::Update( unsigned int iDeltaTime )
{
    tSuperClass::Update( iDeltaTime );
    //mWorld->Update( iDeltaTime );
}


void
cGameApplication::Draw( sf::RenderTarget* iRenderTarget )
{
    //mWorld->Draw( iRenderTarget );
    tSuperClass::Draw( iRenderTarget );
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------ Events
// -------------------------------------------------------------------------------------


void
cGameApplication::KeyPressed( const sf::Event& iEvent )
{
    tSuperClass::KeyPressed( iEvent );
    //mWorld->KeyPressed( iEvent );
}


void
cGameApplication::KeyReleased( const sf::Event& iEvent )
{
    tSuperClass::KeyReleased( iEvent );
    //mWorld->KeyReleased( iEvent );
}




} // namespace nApplication

