#include "MainMenu/MainMenu.h"

#include "MainMenu/MenuPage/MenuPage.h"


cMainMenu::cMainMenu()
{ 
}


void
cMainMenu::AddPage( cMenuPage* iPage )
{
    mPages.push_back( iPage );
}


void 
cMainMenu::CurrentPage( int iPage )
{
    mCurrentPage = iPage;
}


void 
cMainMenu::MouseClick( float iX, float iY )
{
    mPages[ mCurrentPage ]->MouseClick( iX, iY );
}


void
cMainMenu::Draw()
{ 
    mPages[ mCurrentPage ]->Draw(); 
}


