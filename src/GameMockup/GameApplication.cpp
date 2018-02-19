#include "GameMockup/GameApplication.h"

#include "Screen/Screen.h"


#include "MainMenu/MainMenu.h"
#include "MainMenu/MenuItem/MenuItem.Callback.h"
#include "MainMenu/MenuItem/MenuItem.PageSwaper.h"
#include "MainMenu/MenuPage/MenuPage.h"
#include "Screen/ScreenMainMenu.h"


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
// ----------------------------------------------------------------------- Init/Finalize
// -------------------------------------------------------------------------------------


void
cGameApplication::Initialize()
{
    tSuperClass::Initialize();

    // Game.Application, not here, this is just for testing purposes
    cMainMenu* menu = new cMainMenu();
    cMenuPage* pageOne = new cMenuPage( menu );
    cMenuPage* pageTwo = new cMenuPage( menu );

    sf::RectangleShape rect( sf::Vector2f( 200, 50 ) );

    cItemPageSwaper* itemOne  = new cItemPageSwaper( menu, "FirstPage0", rect, 1 );
    cItemPageSwaper* itemOne2 = new cItemPageSwaper( menu, "FirstPage1", rect, 1 );

    cItemPageSwaper* itemTwo  = new cItemPageSwaper( menu, "SecondPage0", rect, 0 );
    cItemCallback*   itemTwo2 = new cItemCallback( menu, "SecondPage1", rect, []()
    {
        cGameApplication::App()->Window()->setTitle( "CLICK" );
    } );


    pageOne->AddItem( itemOne );
    pageOne->AddItem( itemOne2 );
    pageTwo->AddItem( itemTwo );
    pageTwo->AddItem( itemTwo2 );


    menu->AddPage( pageOne );
    menu->AddPage( pageTwo );
    menu->CurrentPage( 0 );

    cScreenMainMenu* mainMenuScreen = new cScreenMainMenu( menu );
    PushScreen( mainMenuScreen );
    //-----------------------------------
}


void
cGameApplication::Finalize()
{
    tSuperClass::Finalize();
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------- Update/Draw
// -------------------------------------------------------------------------------------


void
cGameApplication::Update()
{
    tSuperClass::Update();
}


void
cGameApplication::Draw()
{
    tSuperClass::Draw();
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------ Events
// -------------------------------------------------------------------------------------


void
cGameApplication::KeyPressed( const sf::Event& iEvent )
{
    tSuperClass::KeyPressed( iEvent );
}


void
cGameApplication::KeyReleased( const sf::Event& iEvent )
{
    tSuperClass::KeyReleased( iEvent );
}

