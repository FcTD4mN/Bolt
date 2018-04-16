#include "Editor.BoltQtWidgets.TestCanvas.h"

#include "Editor.Application.EditorApplication.h"

#include "Core.ECS.Utilities.EntityParser.h"
#include "Core.ECS.Core.Entity.h"
#include "Core.ECS.Core.World.h"

#include "Core.ECS.Component.Position.h"

#include <QtGui/QInputEvent>
#include <QtGui/QPainter>


MyCanvas::MyCanvas( QWidget* Parent, const QPoint& Position, const QSize& Size ) :
    QSFMLCanvas( Parent, Position, Size ),
    mState( kIdle )
{
}


MyCanvas::MyCanvas( QWidget* Parent ) :
    QSFMLCanvas( Parent ),
    mState( kIdle )
{
}


void
MyCanvas::SetEditorApp( ::nApplication::cEditorApplication * iEditorApp )
{
    mEditorApp = iEditorApp;
}


void
MyCanvas::OnInit()
{
}

void
MyCanvas::OnUpdate()
{
    // We don't want the world to update actually in the editor
    //mEditorApp->Update( 0 );
}


void
MyCanvas::resizeEvent( QResizeEvent * iEvent )
{
    if( mRenderWindow )
    {
        auto defView = mRenderWindow->getView();
        defView.setSize( iEvent->size().width(), iEvent->size().height() );
        mRenderWindow->setView( defView );

        mRenderWindow->setSize( sf::Vector2u( iEvent->size().width(), iEvent->size().height() ) );
    }
}


void
MyCanvas::paintEvent( QPaintEvent* )
{
    mRenderWindow->clear( sf::Color( 200, 200, 200 ) );
    mEditorApp->Draw( mRenderWindow );

    mRenderWindow->display();
}


//===========================================================================================================
//=========================================================================================== Event Overrides
//===========================================================================================================


void
MyCanvas::mousePressEvent( QMouseEvent * iEvent )
{
    if( iEvent->modifiers() & Qt::AltModifier )
        mState = kPanningCanvas;
    else
        mState = kSelecting;

    mOriginPosition = sf::Vector2i( iEvent->x(), iEvent->y() );
    tSuperClass::mousePressEvent( iEvent );
}


void
MyCanvas::mouseMoveEvent( QMouseEvent * iEvent )
{
    sf::Vector2i currentPos = sf::Vector2i( iEvent->x(), iEvent->y() );
    sf::Vector2i offset = mOriginPosition - currentPos;

    if( mState == kPanningCanvas )
    {
        auto defView = mRenderWindow->getView();
        defView.move( sf::Vector2f( float(offset.x), float(offset.y) ) );
        mRenderWindow->setView( defView );
        mOriginPosition = currentPos;
    }

    tSuperClass::mouseMoveEvent( iEvent );
}


void
MyCanvas::mouseReleaseEvent( QMouseEvent* iEvent )
{
    int minX = mOriginPosition.x;
    int minY = mOriginPosition.y;

    int maxX = iEvent->x();
    int maxY = iEvent->y();

    if( minX > maxX )
    {
        minX = maxX;
        maxX = mOriginPosition.x;
    }

    if( minY > maxY )
    {
        minY = maxY;
        maxY = mOriginPosition.y;
    }

    mSelectionBox = QRect( minX, minY, maxX, maxY );

    mState = kIdle;

    tSuperClass::mouseReleaseEvent( iEvent );
}


void
MyCanvas::mouseDoubleClickEvent( QMouseEvent * iEvent )
{
    ::nECS::cEntityParser* ep = ::nECS::cEntityParser::Instance();
    ::nECS::cWorld* world = mEditorApp->World();

    std::string name = mCurrentPrototypeEntitySelected.data( Qt::DisplayRole ).toString().toStdString();
    ::nECS::cEntity* theEnti = ep->CreateEntityFromPrototypeMap( name.c_str() );


    sf::Vector2f convert = mRenderWindow->mapPixelToCoords( sf::Vector2i( iEvent->localPos().x() , iEvent->localPos().y() ) );

    auto position = dynamic_cast< ::nECS::cPosition* >( theEnti->GetComponentByName( "position" ) );
    if( position )
    {
        position->X( convert.x );
        position->Y( convert.y );
    }
    world->AddEntity( theEnti );

    printf( "Added : %s\n", name.c_str() );

    tSuperClass::mouseDoubleClickEvent( iEvent );
}


void
MyCanvas::CurrentPrototypeChanged( const QModelIndex& iIndex )
{
    mCurrentPrototypeEntitySelected = iIndex;
}

