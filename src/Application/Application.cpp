#include "Application/Application.h"
 

cApplication::cApplication() : 
    mMainWindow( 0 )
{
}



//static 
cApplication* 
cApplication::App()
{
    static cApplication* gApplication = 0;
    if( !gApplication )
        gApplication = new cApplication();

    return  gApplication;
}


sf::RenderWindow*
cApplication::Window()
{
    return  mMainWindow;
}


void
cApplication::Initialize()
{ 
    mMainWindow = new  sf::RenderWindow( sf::VideoMode( 800, 600 ), "Game Title" );
}


void
cApplication::Finalize()
{
    delete  mMainWindow;
}



