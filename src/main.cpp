#include <SFML/Graphics.hpp>
#include "GameMockup/GameApplication.h"
#include "GameMockup/GameScreen.h"
#include "GameMockup/ConsoleScreen.h"


#include "MainMenu/MainMenu.h"
#include "MainMenu/MenuPage/MenuPage.h"
#include "MainMenu/MenuItem/MenuItem.PageSwaper.h"
#include "MainMenu/MenuItem/MenuItem.Callback.h"
#include "Math/Rectangle.h"

#include "Benchmark/Benchmark.h"

int main()
{
	/*
	nBenchmark::RunVectorVsHMapvsMapBenchmark();

	*/
    nBenchmark::EntityStressTest();

    return  0;

    srand( unsigned int(time( NULL )) );

    cGameApplication* app = cGameApplication::App();
    app->Initialize();

#ifdef  CONSOLEDEBUG
    cGameApplication::App()->PushScreen(new cConsoleScreen() );
#endif //  CONSOLEDEBUG

    sf::RenderWindow* window = cGameApplication::App()->Window();
    window->setFramerateLimit( 144 );
    sf::Vector2u size = window->getSize();

    sf::Clock clock;
    sf::Time frameTime;
    sf::Event event;

    while( app->Window()->isOpen() )
    {
        frameTime = clock.restart();

        while( app->Window()->pollEvent( event ) )
        {
            app->HandleEvents( event );
        }

        app->Update( frameTime.asMilliseconds() );
        app->Window()->clear( sf::Color( 200, 200, 200 ) );
        app->Draw( app->Window() );

        // PERF TESTS============================================================
        if( 0 )
        {
            sf::RectangleShape rect( sf::Vector2f( 10.0F, 10.0F ) );
            rect.setPosition( sf::Vector2f( sf::Mouse::getPosition( *window ) ) );
            rect.setFillColor( sf::Color( 10, 10, 255, 255 ) );
            rect.setSize( sf::Vector2f( 50, 50 ) );
            window->draw( rect );
        }
        // PERF TESTS============================================================

        app->Window()->display();
    }

    return 0;
}
