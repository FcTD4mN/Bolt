#include "GameMockup.Application.GameApplication.h"


#include "Core.ECS.Core.Entity.h"
#include "Core.ECS.Core.World.h"
#include "Core.ECS.Utilities.ComponentRegistry.h"
#include "Core.ECS.Utilities.EntityParser.h"

#include "Core.ECS.Component.Color.h"
#include "Core.ECS.Component.Position.h"
#include "Core.ECS.Component.SimplePhysic.h"
#include "Core.ECS.Component.Size.h"
#include "Core.ECS.Component.SpriteAnimated.h"
#include "Core.ECS.Component.UserInput.h"
#include "Core.ECS.Component.Direction.h"
#include "Core.ECS.Component.FieldOfView.h"

#include "Core.ECS.System.AnimationRenderer.h"
#include "Core.ECS.System.InputConverter.h"
#include "Core.ECS.System.SimplerRenderer.h"
#include "Core.ECS.System.SimplePhysics.h"
#include "Core.ECS.System.SightSystem.h"

#include "Core.ECS.Core.ScreenEntityMap.h"

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


namespace nApplication
{

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
    return mWorld;
}


// -------------------------------------------------------------------------------------
// ----------------------------------------------------------------------- Init/Finalize
// -------------------------------------------------------------------------------------


void
cGameApplication::Initialize()
{
    tSuperClass::Initialize();
    //SetAppDefaultResolution( 1024, 768 ); //TODO: menu is shitty as fuck when not in 800*600 ........

    ::nECS::cScreenEntityMap::Instance()->Initialize( 100, 100, 32 );

    // =======ECS WORLD=======
    mWorld = new ::nECS::cWorld();
    mWorld->AddSystem( new ::nECS::cSimplerRenderer() );

    ::nECS::cInputConverter* ic = new ::nECS::cInputConverter();
    mWorld->AddSystem( ic );
    mWorld->ConnectSystemToEvents( ic );

    mWorld->AddSystem( new ::nECS::cAnimationRenderer() );
    mWorld->AddSystem( new ::nECS::cSightSystem() );
    mWorld->AddSystem( new ::nECS::cSimplePhysics() );
    mWorld->AddSystem( new ::nECS::cSquareController() );

    // Following call may need world
    ::nECS::cComponentRegistry::Instance()->Initialize();
    ::nECS::cComponentRegistry::Instance()->RegisterComponent( new ::nECS::cColor() );
    ::nECS::cComponentRegistry::Instance()->RegisterComponent( new ::nECS::cDirection() );
    ::nECS::cComponentRegistry::Instance()->RegisterComponent( new ::nECS::cFieldOfView() );
    ::nECS::cComponentRegistry::Instance()->RegisterComponent( new ::nECS::cPosition() );
    ::nECS::cComponentRegistry::Instance()->RegisterComponent( new ::nECS::cSize() );
    ::nECS::cComponentRegistry::Instance()->RegisterComponent( new ::nECS::cSpriteAnimated() );
    ::nECS::cComponentRegistry::Instance()->RegisterComponent( new ::nECS::cUserInput() );
    ::nECS::cComponentRegistry::Instance()->RegisterComponent( new ::nECS::cSimplePhysic() );

    ::nECS::cEntityParser::Instance()->Initialize( mWorld );

    // =========== GENERAL CONFIG ===========
    mMainWindow->setKeyRepeatEnabled( false );

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

    // =======Shortcuts=======
    ::nShortcuts::cShortcuts::Instance()->Initialize();
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

} // nApplication