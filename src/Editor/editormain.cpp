#include "QtMainWindows/BoltEditor.h"

#include "QtWidgets/TestCanvas.h"

#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>

#include <Windows.h>


// This is the main for console application ( we use console for debugging purposes mainly )
#ifdef _DEBUG
int
main(int argc, char *argv[])
{
    QApplication App(argc, argv);

    // Create the main frame
    QFrame* MainFrame = new QFrame;
    MainFrame->setWindowTitle("Qt SFML");
    MainFrame->resize(400, 400);
    MainFrame->show();

    // Create a SFML view inside the main frame
    MyCanvas* SFMLView = new MyCanvas(MainFrame, QPoint(20, 20), QSize(360, 360));
    SFMLView->show();

    return App.exec();
}
#endif


// This is the main for non console applications
#ifndef _DEBUG
int WINAPI
WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR  lpCmdLine,  int  nCmdShow )
{
    int argc = 0;

    LPWSTR *argList = CommandLineToArgvW( GetCommandLine(), &argc );
    char** argv = (char**)argList;

    QApplication App( argc, argv );

    // Create the main frame
    QFrame* MainFrame = new QFrame;
    MainFrame->setWindowTitle( "Qt SFML" );
    MainFrame->resize( 400, 400 );
    MainFrame->show();

    // Create a SFML view inside the main frame
    MyCanvas* SFMLView = new MyCanvas( MainFrame, QPoint( 20, 20 ), QSize( 360, 360 ) );
    SFMLView->show();

    return App.exec();
}
#endif
