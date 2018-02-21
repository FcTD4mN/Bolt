#include "MainMenu/MenuItem/MenuItem.Callback.h"


#include "Application/Application.h"
#include "MainMenu/MainMenu.h"

#include <SFML/Graphics.hpp>


cItemCallback::cItemCallback( cMainMenu* iMasterMenu, const std::string& iText, const sf::RectangleShape& iBox, std::function< void() > iFunction ) :
   tSuperClass( iMasterMenu, iText, iBox ),
    mFunction( iFunction )
{
}


void
cItemCallback::ClickAction()
{
    mFunction();
}


