#include "GameMockup/GameApplication.h"


#include "ECS/Entity.h"
#include "ECS/World.h"
#include "ECS/ComponentRegistry.h"

#include "GameMockup/GameScreen.h"
#include "GameMockup/Systems/AnimationRenderer.h"
#include "GameMockup/Systems/InputConverter.h"
#include "GameMockup/Systems/SimplerRenderer.h"
#include "GameMockup/Systems/SquareController.h"

#include "MainMenu/MainMenu.h"
#include "MainMenu/MenuItem/MenuItem.Callback.h"
#include "MainMenu/MenuItem/MenuItem.PageSwaper.h"
#include "MainMenu/MenuPage/MenuPage.h"

#include "Screen/Screen.h"
#include "Screen/ScreenMainMenu.h"

#include "Shortcuts/Shortcuts.h"


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


cWorld*
cGameApplication::World()
{
    return mWorld;
}


cShortcuts*
cGameApplication::ShortcutEngine()
{
    return  mShortcutEngine;
}


// -------------------------------------------------------------------------------------
// ----------------------------------------------------------------------- Init/Finalize
// -------------------------------------------------------------------------------------


void
cGameApplication::Initialize()
{
    tSuperClass::Initialize();

    cComponentRegistry::Instance()->Initialize();

    // =========== GENERAL CONFIG ===========
    mMainWindow->setKeyRepeatEnabled( false );

    sf::Vector2u winSize = mMainWindow->getSize();

    // ========= MAIN MENU =========
    cMainMenu* menu = new cMainMenu();
    cMenuPage* pageOne = new cMenuPage( menu );
    pageOne->Size( float(winSize.x), float(winSize.y) );

    cMenuPage* pageTwo = new cMenuPage( menu );
    pageTwo->Size( float(winSize.x), float(winSize.y) );

    sf::RectangleShape rect( sf::Vector2f( 200, 50 ) );

    cItemPageSwaper* itemOne  = new cItemPageSwaper( menu, "FirstPage0", rect, 1 );
    cItemPageSwaper* itemOne2 = new cItemPageSwaper( menu, "FirstPage1", rect, 1 );

    cItemPageSwaper* itemTwo  = new cItemPageSwaper( menu, "SecondPage0", rect, 0 );
    cItemCallback*   itemTwo2 = new cItemCallback( menu, "SecondPage1", rect, []()
    {
        cGameApplication::App()->Window()->setTitle( "CLICK" );
    } );

    cItemCallback*   gameScreenSwap = new cItemCallback( menu, "Game", rect, []()
    {
        cGameApplication::App()->PushScreen( new cGameScreen() );
    } );

    pageOne->AddItem( itemOne );
    pageOne->AddItem( itemOne2 );
    pageOne->AddItem( gameScreenSwap );
    pageTwo->AddItem( itemTwo );
    pageTwo->AddItem( itemTwo2 );

    menu->AddPage( pageOne );
    menu->AddPage( pageTwo );
    menu->CurrentPage( 0 );

    cScreenMainMenu* mainMenuScreen = new cScreenMainMenu( menu );
    PushScreen( mainMenuScreen );

    // =======ECS WORLD=======
    mWorld = new cWorld();
    mWorld->AddSystem( new cSimplerRenderer() );

    cInputConverter* ic = new cInputConverter();
    mWorld->AddSystem( ic );
    mWorld->ConnectSystemToEvents( ic );

    mWorld->AddSystem( new cSquareController() );
    mWorld->AddSystem( new cAnimationRenderer() );

    // =======Shortcuts=======
    mShortcutEngine = new cShortcuts();
    mShortcutEngine->Initialize();

    //-----------------------------------
}


void
cGameApplication::Finalize()
{
    tSuperClass::Finalize();

    cComponentRegistry::Instance()->Finalize();

    delete mWorld;
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------- Update/Draw
// -------------------------------------------------------------------------------------


void
cGameApplication::Update( unsigned int iDeltaTime )
{
    tSuperClass::Update( iDeltaTime );
    mWorld->Update( iDeltaTime );
}


void
cGameApplication::Draw( sf::RenderTarget* iRenderTarget )
{
    mWorld->Draw( iRenderTarget );
    tSuperClass::Draw( iRenderTarget );
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------ Events
// -------------------------------------------------------------------------------------


void
cGameApplication::KeyPressed( const sf::Event& iEvent )
{
    tSuperClass::KeyPressed( iEvent );
    mWorld->KeyPressed( iEvent );
}


void
cGameApplication::KeyReleased( const sf::Event& iEvent )
{
    tSuperClass::KeyReleased( iEvent );
    mWorld->KeyReleased( iEvent );
}

