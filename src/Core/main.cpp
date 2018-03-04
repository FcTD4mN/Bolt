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

extern "C" {
static int numargs=0;

/* Return the number of arguments of the application command line */
static PyObject*
emb_numargs(PyObject *self, PyObject *args)
{
    if(!PyArg_ParseTuple(args, ":numargs"))
        return NULL;
    return PyLong_FromLong(numargs);
}

static PyMethodDef EmbMethods[] = {
    {"numargs", emb_numargs, METH_VARARGS,
     "Return the number of arguments received by the process."},
    {NULL, NULL, 0, NULL}
};

static PyModuleDef EmbModule = {
    PyModuleDef_HEAD_INIT, "emb", NULL, -1, EmbMethods,
    NULL, NULL, NULL, NULL
};

static PyObject*
PyInit_emb(void)
{
    return PyModule_Create(&EmbModule);
}

}
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

    numargs = argc;
    PyImport_AppendInittab("emb", &PyInit_emb);

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
