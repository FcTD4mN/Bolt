#include "Application/EditorApplication.h"


#include "ECS/Core/Entity.h"
#include "ECS/Core/World.h"
#include "ECS/Utilities/ComponentRegistry.h"
#include "ECS/Utilities/EntityParser.h"

#include "MainMenu/MainMenu.h"
#include "MainMenu/MenuItem/MenuItem.Callback.h"
#include "MainMenu/MenuItem/MenuItem.PageSwaper.h"
#include "MainMenu/MenuPage/MenuPage.h"


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------ Construction/Destruction
// -------------------------------------------------------------------------------------


cEditorApplication::cEditorApplication()
{
}


// -------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------- Instance
// -------------------------------------------------------------------------------------


//static
cEditorApplication*
cEditorApplication::App()
{
    static cEditorApplication* gApplication = 0;
    if( !gApplication )
        gApplication = new cEditorApplication();

    return  gApplication;
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------ Access
// -------------------------------------------------------------------------------------


cWorld*
cEditorApplication::World()
{
    return mWorld;
}


// -------------------------------------------------------------------------------------
// ----------------------------------------------------------------------- Init/Finalize
// -------------------------------------------------------------------------------------


void
cEditorApplication::Initialize()
{
    // NO TSUPERCLASS
    // As it would create a mMainWindow, which we don't want here
    // The behaviour is different when embeded into editor

    // =======ECS WORLD=======
    mWorld = new cWorld();

    // Following call may need world
    cComponentRegistry::Instance()->Initialize();
    cEntityParser::Instance()->Initialize();


    // ========= MAIN MENU =========
    sf::Vector2u winSize( 360, 360 );

    mMMenu = new cMainMenu();
    cMenuPage* pageOne = new cMenuPage( mMMenu );
    pageOne->Size( float(winSize.x), float(winSize.y) );

    cMenuPage* pageTwo = new cMenuPage( mMMenu );
    pageTwo->Size( float(winSize.x), float(winSize.y) );

    sf::RectangleShape rect( sf::Vector2f( 200, 50 ) );

    cItemPageSwaper* itemOne  = new cItemPageSwaper( mMMenu, "FirstPage0", rect, 1 );
    cItemPageSwaper* itemOne2 = new cItemPageSwaper( mMMenu, "FirstPage1", rect, 1 );

    cItemPageSwaper* itemTwo  = new cItemPageSwaper( mMMenu, "SecondPage0", rect, 0 );
    cItemCallback*   itemTwo2 = new cItemCallback( mMMenu, "SecondPage1", rect, []()
    {
        cEditorApplication::App()->Window()->setTitle( "CLICK" );
    } );

    pageOne->AddItem( itemOne );
    pageOne->AddItem( itemOne2 );
    pageTwo->AddItem( itemTwo );
    pageTwo->AddItem( itemTwo2 );

    mMMenu->AddPage( pageOne );
    mMMenu->AddPage( pageTwo );
    mMMenu->CurrentPage( 0 );
}


void
cEditorApplication::Finalize()
{
    cComponentRegistry::Instance()->Finalize();

    delete mWorld;
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------- Update/Draw
// -------------------------------------------------------------------------------------


void
cEditorApplication::Update( unsigned int iDeltaTime )
{
    mWorld->Update( iDeltaTime );
}


void
cEditorApplication::Draw( sf::RenderTarget* iRenderTarget )
{
    mWorld->Draw( iRenderTarget );
    mMMenu->Draw( iRenderTarget );
}