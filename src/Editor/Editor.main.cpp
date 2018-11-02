#include <QApplication>
#include <QFile>



#ifdef WINDOWS
#include <Windows.h>
#endif //WINDOWS

#include "Editor.MainWindows.BoltEditor.h"
#include "Editor.MainWindows.MainWindow.h"


int
MainFunction( int argc, char *argv[] )
{
    QApplication App( argc, argv );

    {
        // Reading and applying style sheet.
        QFile  file( "resources/Editor/css-themes/style.qss" );
        file.open( QFile::ReadOnly );
        QString  qss = QLatin1String( file.readAll() );
        App.setStyle( "plastique" );
        App.setStyleSheet( qss );
        file.close();
    }

    // Create the main window
    ::nEditor::nMainWindows::cBoltEditor* MainWindow = new ::nEditor::nMainWindows::cBoltEditor();
    MainWindow->setObjectName( "MainWindow" );
    MainWindow->setWindowTitle( "Bolt Editor" );
    MainWindow->resize( 800, 600 );
    MainWindow->Setup();
    MainWindow->show();

    // Just for now, as it takes a lot of time to load both windows
    //auto w = new ::nEditor::nWidgets::cMainWindow();
    //w->resize( 800, 600 );
    //w->show();

    return App.exec();
}


#ifdef WINDOWS
// Debug, application with console.
#ifdef _DEBUG

int
main( int argc, char *argv[] )
{
    return  MainFunction( argc, argv );
}

// Release, non-console application.
#else


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


