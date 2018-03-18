#include "GameMockup/GameApplication.h"


#include "ECS/Core/Entity.h"
#include "ECS/Core/World.h"
#include "ECS/Utilities/ComponentRegistry.h"
#include "ECS/Utilities/EntityParser.h"

#include "GameMockup/GameScreen.h"
#include "GameMockup/InfiltratorScreen.h"
#include "GameMockup/OpenGLRenderSceneScreen.h"
#include "GameMockup/Systems/AnimationRenderer.h"
#include "GameMockup/Systems/InputConverter.h"
#include "GameMockup/Systems/SimplePhysics.h"
#include "GameMockup/Systems/SimplerRenderer.h"
#include "GameMockup/Systems/SquareController.h"
#include "GameMockup/Systems/SightSystem.h"

#include "MainMenu/MainMenu.h"
#include "MainMenu/MenuItem/MenuItem.Callback.h"
#include "MainMenu/MenuItem/MenuItem.PageSwaper.h"
#include "MainMenu/MenuPage/MenuPage.h"

#include "Mapping/PhysicEntityGrid.h"

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


cEntityGrid*
cGameApplication::EntityMap()
{
    return  mEntityMap;
}


// -------------------------------------------------------------------------------------
// ----------------------------------------------------------------------- Init/Finalize
// -------------------------------------------------------------------------------------


void
cGameApplication::Initialize()
{
    tSuperClass::Initialize();
    //SetAppDefaultResolution( 1024, 768 ); //TODO: menu is shitty as fuck when not in 800*600 ........

    mEntityMap = new cEntityGrid();
    // =======ECS WORLD=======
    mWorld = new cWorld();
    mWorld->AddSystem( new cSimplerRenderer() );

    cInputConverter* ic = new cInputConverter();
    mWorld->AddSystem( ic );
    mWorld->ConnectSystemToEvents( ic );

    mWorld->AddSystem( new cAnimationRenderer() );
    mWorld->AddSystem( new cSightSystem() );
    mWorld->AddSystem( new cSimplePhysics() );
    mWorld->AddSystem( new cSquareController() );

    // Following call may need world
    cComponentRegistry::Instance()->Initialize();
    cEntityParser::Instance()->Initialize();

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

    cItemCallback*   infiltratorScreenSwap = new cItemCallback( menu, "Infiltrator", rect, [](){
        cGameApplication::App()->PushScreen( new cInfiltratorScreen() );
    } );

    cItemCallback*   openGLRenderSceneScreenSwap = new cItemCallback( menu, "OpenGL", rect, [](){
        cGameApplication::App()->PushScreen( new cOpenGLRenderSceneScreen() );
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

    cScreenMainMenu* mainMenuScreen = new cScreenMainMenu( menu );
    PushScreen( mainMenuScreen );

    // =======Shortcuts=======
    mShortcutEngine = new cShortcuts();
    mShortcutEngine->Initialize();
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

