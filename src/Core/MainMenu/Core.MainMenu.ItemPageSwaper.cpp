#include "Core.MainMenu.ItemPageSwaper.h"


#include "Core.Application.Application.h"
#include "Core.MainMenu.MainMenu.h"


#include <SFML/Graphics.hpp>


namespace nMainMenu {


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


} //nMainMenu

