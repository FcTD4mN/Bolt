#include <SFML/Graphics.hpp>
#include <cpython/Python.h>

#include "BoltScript/BoltScriptEnvironment.h"

#include "GameMockup/GameApplication.h"
#include "GameMockup/GameScreen.h"
#include "GameMockup/ConsoleScreen.h"


#include "MainMenu/MainMenu.h"
#include "MainMenu/MenuPage/MenuPage.h"
#include "MainMenu/MenuItem/MenuItem.PageSwaper.h"
#include "MainMenu/MenuItem/MenuItem.Callback.h"

#include "Benchmark/Benchmark.h"

int
main(int argc, char *argv[])
{

    //nBenchmark::RunVectorVsHMapvsMapBenchmark();
    //nBenchmark::EntityStressTest();

    srand( unsigned int(time( NULL )) );

    cGameApplication* app = cGameApplication::App();
    app->Initialize();

    ::nBoltScript::Env()->RegisterFunction( "exit", [=]( void ) { app->Window()->close(); } );
#ifdef  CONSOLEDEBUG

    cGameApplication::App()->PushScreen(new cConsoleScreen() );

#endif //  CONSOLEDEBUG

    // PYTHON TEST
    wchar_t *program = Py_DecodeLocale(argv[0], NULL);
    if (program == NULL) {
        fprintf(stderr, "Fatal error: cannot decode argv[0]\n");
        exit(1);
    }
    Py_SetProgramName(program);
    Py_Initialize();
    PyRun_SimpleString("import ctypes\n");

    ////////////////////////////////////////////////////////////

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
            //sf::RectangleShape rect( sf::Vector2f( 10.0F, 10.0F ) );
            //rect.setPosition( sf::Vector2f( sf::Mouse::getPosition( *window ) ) );
            //rect.setFillColor( sf::Color( 10, 10, 255, 255 ) );
            //rect.setSize( sf::Vector2f( 50, 50 ) );
            //window->draw( rect );

            float fps = 1 / frameTime.asSeconds();
            std::cout << std::to_string( fps ) << "\n";
            std::cout << "==============" << std::to_string( cGameApplication::App()->World()->EntityCount() ) << "\n";

        }
        // PERF TESTS============================================================

        app->Window()->display();
    }

    if (Py_FinalizeEx() < 0) {
        exit(120);
    }
    PyMem_RawFree(program);

    return 0;
}
