#include "Editor.BoltQtWidgets.QSFMLCanvas.h"


QSFMLCanvas::~QSFMLCanvas()
{
}


QSFMLCanvas::QSFMLCanvas( QWidget* Parent, const QPoint& Position, const QSize& Size, unsigned int FrameTime ) :
    QWidget( Parent ),
    mRenderWindow( 0 ),
    mInitialized( false )
{
    // Setup some states to allow direct rendering into the widget
    setAttribute( Qt::WA_PaintOnScreen );
    setAttribute( Qt::WA_OpaquePaintEvent );
    setAttribute( Qt::WA_NoSystemBackground );

    // Set strong focus to enable keyboard events to be received
    setFocusPolicy( Qt::StrongFocus );

    // Setup the widget geometry
    move( Position );
    resize( Size );

    // Setup the timer
    mTimer.setInterval( FrameTime );
}


QSFMLCanvas::QSFMLCanvas( QWidget * Parent ) :
    QWidget( Parent ),
    mRenderWindow( 0 ),
    mInitialized( false )
{
    // Setup some states to allow direct rendering into the widget
    setAttribute( Qt::WA_PaintOnScreen );
    setAttribute( Qt::WA_OpaquePaintEvent );
    setAttribute( Qt::WA_NoSystemBackground );

    // Set strong focus to enable keyboard events to be received
    setFocusPolicy( Qt::StrongFocus );

    // Setup the timer
    mTimer.setInterval( 0 );
}


void
QSFMLCanvas::showEvent( QShowEvent* )
{
    if( !mInitialized )
    {
        // Under X11, we need to flush the commands sent to the server to ensure that
        // SFML will get an updated view of the windows
#ifdef Q_WS_X11
        XFlush( QX11Info::display() );
#endif

        // Create the SFML window with the widget handle
        mRenderWindow = new sf::RenderWindow( ( sf::WindowHandle )winId() );

        // Let the derived class do its specific stuff
        OnInit();

        // Setup the timer to trigger a refresh at specified framerate
        connect( &mTimer, SIGNAL( timeout() ), this, SLOT( repaint() ) );
        mTimer.start();

        mInitialized = true;
    }
}


sf::RenderWindow*
QSFMLCanvas::Window()
{
    return  mRenderWindow;
}


void
QSFMLCanvas::OnInit()
{
    // TODO;
}


void
QSFMLCanvas::OnUpdate()
{
    // TODO;
}


QPaintEngine* QSFMLCanvas::paintEngine() const
{
    return 0;
}


void
QSFMLCanvas::paintEvent( QPaintEvent* )
{
    mRenderWindow->clear( sf::Color( 200, 200, 200 ) );
    // Let the derived class do its specific stuff
    OnUpdate();
    mRenderWindow->display();
}
