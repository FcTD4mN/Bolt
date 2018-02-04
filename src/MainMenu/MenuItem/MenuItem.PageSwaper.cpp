#include "MainMenu/MenuItem/MenuItem.PageSwaper.h"

#include "Application/Application.h"

#include <SFML/Graphics.hpp>


cItemPageSwaper::cItemPageSwaper( const std::string& iText, const cRectangle& iBox, int iPage ) :
   tSuperClass( iText, iBox ),
    mPageToSwapTo( iPage )
{
}

void 
cItemPageSwaper::ClickAction()
{
}


void 
cItemPageSwaper::Draw() const
{
    cApplication::App()->Window()->draw( Text() );
}


