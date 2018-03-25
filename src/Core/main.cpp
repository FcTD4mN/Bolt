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

#include "Volumetric/Static/Data.h"


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

    // Small Volumetric benchmark
    ::nBoltScript::Env()->Print( ">>> Size of Volumetric Atomic Data: " + std::to_string( sizeof( ::nVolumetric::cData ) ) + "Bytes\n" );

    // PYTHON TEST
    wchar_t *program = Py_DecodeLocale(argv[0], NULL);
    if (program == NULL) {
        fprintf(stderr, "Fatal error: cannot decode argv[0]\n");
        exit(1);
    }

    PyImport_AppendInittab("PyBolt", &::nBoltScript::PyInit_PyBolt);

    Py_SetProgramName(program);
    Py_Initialize();
    PyRun_SimpleString("import PyBolt\n");
    PyRun_SimpleString("PyBolt.PyBoltPrint(\"\")\n");
    PyRun_SimpleString("class Monitor:\n"
                       "    def __init__(self):\n"
                       "      self\n"
                       "\n"
                       "    def write(self, s):\n"
                       "      if s.rstrip() != \"\":\n"
                       "        PyBolt.PyBoltPrint(s)\n"
                       "\n" );
    PyRun_SimpleString("monitorQ = Monitor()\n");
    PyRun_SimpleString("print(\"Redirecting output...\")\n"
                       "import sys\n"
                       "sys.stdout = monitorQ\n"
                       "sys.stderr = monitorQ\n" );

    PyRun_SimpleString("print(\"Python says i love Bolt\")\n" );
    PyRun_SimpleString("print(\"Python says i can't wait to see your little voxels\")\n" );


    ////////////////////////////////////////////////////////////

    sf::RenderWindow* window = cGameApplication::App()->Window();
    window->setFramerateLimit( 144 );
    sf::Vector2u size = window->getSize();

    sf::Clock clock;
    sf::Time frameTime;
    sf::Event event;




    // Drawing entityMap
        //sf::Vector2f position;
        //sf::RectangleShape square;
        //square.setSize( sf::Vector2f( 32, 32 ) );
        //square.setFillColor( sf::Color( 0, 0, 0, 0 ) );
        //square.setOutlineColor( sf::Color( 255, 0, 0, 120 ) );
        //square.setOutlineThickness( 1.0F );
    // /Drawing entityMap

    while( window->isOpen() )
    {
        frameTime = clock.restart();

        while( window->pollEvent( event ) )
        {
            app->HandleEvents( event );
        }

        app->Update( frameTime.asMilliseconds() );
        window->clear( sf::Color( 200, 200, 200 ) );
        app->Draw( window );

        // PERF TESTS============================================================

        // Draw entityMapGrid
            //for( int x = 0; x < 32; ++x )
            //{
            //    for( int y = 0; y < 32; ++y )
            //    {
            //        position.x = x * 32;
            //        position.y = y * 32;
            //        square.setPosition( position );

            //        window->draw( square );
            //    }
            //}
        // /Drawing entityMap

        if( 1 )
        {
            //sf::RectangleShape rect( sf::Vector2f( 10.0F, 10.0F ) );
            //rect.setPosition( sf::Vector2f( sf::Mouse::getPosition( *window ) ) );
            //rect.setFillColor( sf::Color( 10, 10, 255, 255 ) );
            //rect.setSize( sf::Vector2f( 50, 50 ) );
            //window->draw( rect );

            //nBenchmark::DrawStressTest( app->Window() );

            /*
            float fps = 1 / frameTime.asSeconds();
            std::cout << std::to_string( fps ) << "\n";
            std::cout << "==============" << std::to_string( cGameApplication::App()->World()->EntityCount() ) << "\n";
            */

        }
        // PERF TESTS============================================================

        window->display();
    }

    if (Py_FinalizeEx() < 0) {
        exit(120);
    }
    PyMem_RawFree(program);

    return 0;
}
