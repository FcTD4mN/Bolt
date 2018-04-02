#include "QtMainWindows/BoltEditor.h"

#include "QtWidgets/TestCanvas.h"
#include "QtMainWindows/BoltEditor.h"

#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>

#include <Windows.h>


int
MainFunction( int argc, char *argv[] )
{
    QApplication App( argc, argv );

    // Creates the main window
    cBoltEditor* MainWindow = new cBoltEditor();
    MainWindow->setWindowTitle( "Qt SFML" );
    MainWindow->resize( 800, 600 );
    MainWindow->show();

    // Create a SFML view inside the main frame
    MyCanvas* SFMLView = new MyCanvas( MainWindow, QPoint( 20, 20 ), QSize( 360, 360 ) );
    SFMLView->show();

    return App.exec();
}

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
