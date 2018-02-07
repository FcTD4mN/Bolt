#include "MainMenu/MenuItem/MenuItem.PageSwaper.h"


#include "Application/Application.h"
#include "MainMenu/MainMenu.h"

#include <SFML/Graphics.hpp>


cItemPageSwaper::cItemPageSwaper( cMainMenu* iMasterMenu, const std::string& iText, const cRectangle& iBox, int iPage ) :
   tSuperClass( iMasterMenu, iText, iBox ),
    mPageToSwapTo( iPage )
{
}

void 
cItemPageSwaper::ClickAction()
{
    mMasterMenu->CurrentPage( mPageToSwapTo );
}


void 
cItemPageSwaper::Draw()
{
    sf::Font font;
    if( !font.loadFromFile( "resources/Fonts/arial.ttf" ) )
        int a = 2;

    mText.setString( "TEST" );
    mText.setFont( font );
    mText.setCharacterSize( 24 );
    mText.setFillColor( sf::Color::Red );

    sf::RenderWindow* window = cApplication::App()->Window();
    window->draw( mText ); 
}


