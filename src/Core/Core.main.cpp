#include "Core.BoltScript.BoltScriptEnvironment.h"
#include "Core.Application.Application.h"
#include "Core.Screen.Screen.h"
#include "Core.ECS.Core.World.h"


#include <SFML/Graphics.hpp>

//#ifdef WINDOWS
//#include <cpython/Python.h>
//#else
//#include <Python.h>
//#endif //WINDOWS


#include <chrono>
#include <iostream>


// extern  ::nCore::nApplication::cApplication* CreateApplication();

// When game mockup is out of core, we need to remove this preproc (project properties)
// Or, we can add 2 more targets: GameMockupDebug and GameMockupRelease, but then we handle 4 target total, what is the most confortable ?
#ifndef  OVERRIDE_APPLICATION

::nCore::nApplication::cApplication*
CreateApplication()
{
    if( ::nCore::nApplication::cApplication::App() )
        return  ::nCore::nApplication::cApplication::App();
    return  new  ::nCore::nApplication::cApplication();
}

#endif // OVERRIDE_APPLICATION


int
BoltMain( int argc, char *argv[] )
{

    // ================================================================================================================== PYTHON TESTS

    //::nBoltScript::Env()->RegisterFunction( "exit", [ = ]( void ){ app->Window()->close(); } );
#ifdef  CONSOLEDEBUG

    ::nApplication::cGameApplication::App()->PushScreen( new ::nScreen::cConsoleScreen() );

#endif //  CONSOLEDEBUG

    // PYTHON TEST
    //wchar_t *program = Py_DecodeLocale( argv[ 0 ], NULL );
    //if( program == NULL )
    //{
    //    fprintf( stderr, "Fatal error: cannot decode argv[0]\n" );
    //    exit( 1 );
    //}

    //PyImport_AppendInittab( "PyBolt", &::nCore::nBoltScript::PyInit_PyBolt );

    //Py_SetProgramName( program );
    //Py_Initialize();
    /*
    PyRun_SimpleString( "import PyBolt\n" );
    PyRun_SimpleString( "PyBolt.PyBoltPrint(\"\")\n" );
    PyRun_SimpleString( "class Monitor:\n"
                        "    def __init__(self):\n"
                        "      self\n"
                        "\n"
                        "    def write(self, s):\n"
                        "      if s.rstrip() != \"\":\n"
                        "        PyBolt.PyBoltPrint(s)\n"
                        "\n" );
    PyRun_SimpleString( "monitorQ = Monitor()\n" );
    PyRun_SimpleString( "print(\"Redirecting output...\")\n"
                        "import sys\n"
                        "sys.stdout = monitorQ\n"
                        "sys.stderr = monitorQ\n" );

    PyRun_SimpleString( "print(\"Python says i love Bolt\")\n" );
    PyRun_SimpleString( "print(\"Python says i can't wait to see your little voxels\")\n" );


    printf( "\n" );
    */
    //PyRun_SimpleString( "print( 'yo' )" );

    // ================================================================================================================== PYTHON TESTS

    //nBenchmark::RunVectorVsHMapvsMapBenchmark();
    //nBenchmark::EntityStressTest();

    srand( (unsigned int)( time( NULL ) ) );

    ::nCore::nApplication::cApplication* app = CreateApplication();
    app->Initialize();
    if( !app->LoadProject( "resources/ProjectTest/ProjectTest.proj" ) )
        app->SetDefaultNoProjectScreen();

    app->BuildProject();

    static auto gClock = std::chrono::high_resolution_clock::now();

    ////////////////////////////////////////////////////////////

    sf::RenderWindow* window = app->Window();
    sf::Vector2u size = window->getSize();

    sf::Clock clock;
    sf::Time frameTime;
    sf::Event event;

    double          FPSAverage = 0.0;
    unsigned int    fpscounter = 0;

    // Drawing entityMap
    //sf::Vector2f position;
    //sf::RectangleShape square;
    //square.setSize( sf::Vector2f( 32, 32 ) );
    //square.setFillColor( sf::Color( 0, 0, 0, 0 ) );
    //square.setOutlineColor( sf::Color( 255, 0, 0, 120 ) );
    //square.setOutlineThickness( 1.0F );
    // /Drawing entityMap
    if( !app->Project() )
        return  0;

    while( window->isOpen() )
    {
        frameTime = clock.restart();

        while( window->pollEvent( event ) )
            app->HandleEvents( event );

        app->Update( (unsigned int)( frameTime.asMicroseconds() ) );
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

            float fps = 1 / frameTime.asSeconds();
            FPSAverage += fps;

            if( fpscounter >= 1000 )
            {
                FPSAverage /= fpscounter;
                std::cout << std::to_string( FPSAverage ) << "\n";
                std::cout << "==============" << std::to_string( app->CurrentScreen()->World()->EntityCount() ) << "\n";
                fpscounter = 0;
                FPSAverage = 0.0;
            }
            else
            {
                ++fpscounter;
            }
        }
        // PERF TESTS============================================================

        window->display();
    }

    app->Finalize();

    //if( Py_FinalizeEx() < 0 )
    //{
    //    exit( 120 );
    //}
    //PyMem_RawFree( program );

    return  0;
}

int
main( int argc, char *argv[] )
{
    return  BoltMain( argc, argv );
}
