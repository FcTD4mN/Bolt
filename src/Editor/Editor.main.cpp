#include "Editor.BoltQtMainWindows.BoltEditor.h"


#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>

#ifdef WINDOWS
#include <Windows.h>
#endif // WINDOWS

int
MainFunction( int argc, char *argv[] )
{
    QApplication App( argc, argv );


    // Creates the main window
    ::nQt::cBoltEditor* MainWindow = new ::nQt::cBoltEditor();
    MainWindow->setWindowTitle( "Qt SFML" );
    MainWindow->resize( 800, 600 );
    MainWindow->Setup();
    MainWindow->show();

    return App.exec();
}

#ifdef WINDOWS
// This is the main for console application ( we use console for debugging purposes mainly )
#ifdef _DEBUG
int
main( int argc, char *argv[] )
{
    return  MainFunction( argc, argv );
}
#endif


// This is the main for non console applications
#ifndef _DEBUG
int WINAPI
WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR  lpCmdLine,  int  nCmdShow )
{
    int argc = 0;
    LPWSTR *argList = CommandLineToArgvW( GetCommandLine(), &argc );

    return  MainFunction( argc, (char**)argList );
}
#endif
#else

int
main( int argc, char *argv[] )
{
    return  MainFunction( argc, argv );
}

#endif // WINDOWS