#include <SFML/Graphics.hpp>
#include "GameMockup/GameApplication.h"


#include "MainMenu/MainMenu.h"
#include "MainMenu/MenuPage/MenuPage.h"
#include "MainMenu/MenuItem/MenuItem.PageSwaper.h"
#include "MainMenu/MenuItem/MenuItem.Callback.h"
#include "Math/Rectangle.h"

#include <iostream>

int main()
{
    cGameApplication* app = cGameApplication::App();
    app->Initialize();
    sf::Clock clock;

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
        rect.setPosition( sf::Vector2f( sf::Mouse::getPosition( *window ) ) );
        rect.setFillColor( sf::Color( 10, 10, 255, 255 ) );
        rect.setSize( sf::Vector2f( 50, 50 ) );
        window->draw( rect );
        // PERF TESTS============================================================


        app->Window()->display();

        sf::Time frameTime = clock.restart();
        float fps = 1 / frameTime.asSeconds();
        std::cout << std::to_string( fps ) << std::endl;
    }

    return 0;
}
