#include <SFML/Graphics.hpp>
#include "Application/Application.h"


#include "MainMenu/MainMenu.h"
#include "MainMenu/MenuPage/MenuPage.h"
#include "MainMenu/MenuItem/MenuItem.PageSwaper.h"
#include "MainMenu/MenuItem/MenuItem.Callback.h"
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

    sf::RectangleShape rect( sf::Vector2f( 200, 50 ) );

    cItemPageSwaper itemOne( &menu, "FirstPage0", rect, 1 );
    cItemPageSwaper itemOne2( &menu, "FirstPage1", rect, 1 );

    cItemPageSwaper itemTwo( &menu, "SecondPage0", rect, 0 );
    cItemCallback itemTwo2( &menu, "SecondPage1", rect, []() {
        cApplication::App()->Window()->setTitle( "CLICK" );
    } );


    pageOne.AddItem( &itemOne );
    pageOne.AddItem( &itemOne2 );
    pageTwo.AddItem( &itemTwo );
    pageTwo.AddItem( &itemTwo2 );


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
            else if( event.type == sf::Event::MouseButtonReleased )
                menu.MouseClick( event.mouseButton.x, event.mouseButton.y );
        }

        window->clear();
        menu.Draw();
        window->display();
    }

    return 0;
}
