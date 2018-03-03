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
cMainMenu::MouseClick( int iX, int iY )
{
    mPages[ mCurrentPage ]->MouseClick( iX, iY );
}


void
cMainMenu::Draw( sf::RenderTarget* iRenderTarget )
{
    mPages[ mCurrentPage ]->Draw( iRenderTarget );
}


