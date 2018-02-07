#include <SFML/Graphics.hpp>
#include "Application/Application.h"


#include "MainMenu/MainMenu.h"
#include "MainMenu/MenuPage/MenuPage.h"
#include "MainMenu/MenuItem/MenuItem.PageSwaper.h"
#include "Math/Rectangle.h"

int main()
{
    cApplication::App()->Initialize();
    sf::RenderWindow* window = cApplication::App()->Window();

    sf::Text test;
    sf::Font font;
    if( !font.loadFromFile( "resources/Fonts/arial.ttf" ) )
        int a = 2;

    test.setString( "TEST" );
    test.setFont( font );
    test.setCharacterSize( 24 );
    test.setFillColor( sf::Color::Red );

    cMainMenu menu;
    cMenuPage pageOne( &menu );
    cMenuPage pageTwo( &menu );

    cItemPageSwaper itemOne( &menu, "FirstPage0", cRectangle( 50, 50, 50, 50 ), 1 );
    cItemPageSwaper itemTwo( &menu, "FirstPage1", cRectangle( 50, 50, 50, 50 ), 0 );
    pageOne.AddItem( &itemOne );
    pageTwo.AddItem( &itemTwo );

    menu.AddPage( &pageOne );
    menu.AddPage( &pageTwo );
    menu.CurrentPage( 0 );

    while( window->isOpen() )
    {
        sf::Event event;
        while( window->pollEvent( event ) )
        {
            if( event.type == sf::Event::Closed )
                window->close();
        }
         
        menu.Draw();
        //window->draw( test );
        window->display();
        //window->clear();
    }

    return 0;
}
