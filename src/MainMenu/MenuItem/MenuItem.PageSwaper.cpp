#include "MainMenu/MenuItem/MenuItem.PageSwaper.h"


#include "Application/Application.h"
#include "MainMenu/MainMenu.h"

#include <SFML/Graphics.hpp>


cItemPageSwaper::cItemPageSwaper( cMainMenu* iMasterMenu, const std::string& iText, const sf::RectangleShape& iBox, int iPage ) :
   tSuperClass( iMasterMenu, iText, iBox ),
    mPageToSwapTo( iPage )
{
}

void
cItemPageSwaper::ClickAction()
{
    mMasterMenu->CurrentPage( mPageToSwapTo );
}


