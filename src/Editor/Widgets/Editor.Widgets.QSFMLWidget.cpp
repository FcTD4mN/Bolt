#include "Editor.Widgets.QSFMLWidget.h"


/*
#ifdef USE_RIVET
#include <RivetCustomMainWindow>
#endif // USE_RIVET
*/

#ifdef WINDOWS
#include <QtWinExtras>
#endif // WINDOWS


//--------------------------------------------------------------------------------------
//----------------------------------------------------------- Construction / Destruction


QSFMLWidget::~QSFMLWidget()
{
}


QSFMLWidget::QSFMLWidget( QWidget* iParent ) :
    QWidget( iParent ),
    mInitialized( false )
{
    // Mise en place de quelques options pour autoriser le rendu direct dans le widget
    setAttribute(Qt::WA_PaintOnScreen);
    setAttribute(Qt::WA_OpaquePaintEvent);
    setAttribute(Qt::WA_NoSystemBackground);

    // Changement de la police de focus, pour autoriser notre widget � capter les �v�nements clavier
    setFocusPolicy(Qt::StrongFocus);

    // Pr�paration du timer
    float fps = 60.f;
    int mstime = int( 1000.f / 60.f );
    mTimer.setInterval( mstime );
}


//--------------------------------------------------------------------------------------
//-------------------------------------------------------------------------- Private API


void
QSFMLWidget::OnInit()
{
    // Nothing ATM
}


void
QSFMLWidget::OnUpdate()
{
    // Nothing ATM
}


void
QSFMLWidget::OnDraw()
{
    sf::RenderWindow::clear( sf::Color( 220, 220, 220 ) );
    sf::RenderWindow::display();
}


//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------- Events overrides


void
QSFMLWidget::showEvent(QShowEvent*)
{
    if (!mInitialized)
    {
        // Sous X11, il faut valider les commandes qui ont ete envoyees au serveur
        // afin de s'assurer que SFML aura une vision a jour de la fenetre
        #ifdef Q_WS_X11
            XFlush(QX11Info::display());
        #endif

        // On cree la fenetre SFML avec l'identificateur du widget
        //sf::RenderWindow::create( static_cast< sf::WindowHandle >( winId() ) );
        sf::RenderWindow::create( (sf::WindowHandle)( winId() ) );

        // On laisse la classe derivee s'initialiser si besoin
        OnInit();

        // On parametre le timer de sorte qu'il genere un rafraichissement a la frequence souhaitee
        connect( &mTimer, SIGNAL( timeout() ), this, SLOT( repaint() ) );
        mTimer.start();

        mInitialized = true;
    }
}


void
QSFMLWidget::paintEvent(QPaintEvent*)
{
#ifdef USE_RIVET
    auto tw = dynamic_cast< ::Rivet::CustomMainWindow* >( topLevelWidget() );
    if( tw && tw->CheckCustomWindowResizingState() ) return;
#endif // USE_RIVET

    OnUpdate();
    sf::RenderWindow::setActive( true );
    OnDraw();
    sf::RenderWindow::setActive( false );
}

#ifdef WINDOWS

bool
QSFMLWidget::nativeEvent( const  QByteArray&  eventType, void* message, long* result )
{
    // Cast to WINAPI standards
    MSG*    wmsg    = reinterpret_cast< MSG* >( message );
    LPARAM  lparam  = wmsg->lParam;
    WPARAM  wparam  = wmsg->wParam;
    HWND    hwnd    = wmsg->hwnd;
    UINT    msg     = wmsg->message;

    switch( msg )
    {
        case WM_NCHITTEST:
        {
            *result = HTTRANSPARENT;
            return  true;
        }

        default:
        {
            // The case is not handled ? Treat it the normal way & return.
            return  QWidget::nativeEvent( eventType, message, result );
        }
    }
}

#endif // WINDOWS

//--------------------------------------------------------------------------------------
//------------------------------------------------------------------- Behaviour override


QPaintEngine*
QSFMLWidget::paintEngine() const
{
    return  0;
}

