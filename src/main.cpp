#include <SFML/Graphics.hpp>
#include "GameMockup/GameApplication.h"


#include "MainMenu/MainMenu.h"
#include "MainMenu/MenuPage/MenuPage.h"
#include "MainMenu/MenuItem/MenuItem.PageSwaper.h"
#include "MainMenu/MenuItem/MenuItem.Callback.h"
#include "Math/Rectangle.h"

int main()
{
    cGameApplication* app = cGameApplication::App();
    app->Initialize();


    srand( time( NULL ) );

    sf::RenderWindow* window = cGameApplication::App()->Window();
    sf::Vector2u size = window->getSize();


    while( app->Window()->isOpen() )
    {
        sf::Event event;
        while( app->Window()->pollEvent( event ) )
        {
            app->HandleEvents( event );
        }

        app->Update();
        app->Window()->clear();
        app->Draw( app->Window() );



        // PERF TESTS============================================================
        sf::RectangleShape rect( sf::Vector2f( 10.0F, 10.0F ) );
        //rect.setFillColor( sf::Color( 255, 10, 10, 100 ) );

        //for( int i = 0; i < 25000; ++i )
        //{
        //    int posX = rand() % ( size.x - 10 );
        //    int posY = rand() % ( size.y - 10 );

        //    rect.setPosition( sf::Vector2f( float(posX), float(posY )) );
        //    window->draw( rect );
        //}
        rect.setPosition( sf::Vector2f( sf::Mouse::getPosition( *window ) ) );
        rect.setFillColor( sf::Color( 10, 10, 255, 255 ) );
        rect.setSize( sf::Vector2f( 50, 50 ) );
        window->draw( rect );
        // PERF TESTS============================================================


        app->Window()->display();
    }

    return 0;
}
