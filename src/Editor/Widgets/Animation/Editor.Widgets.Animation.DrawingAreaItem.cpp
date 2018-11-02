#include "Editor.Widgets.Animation.DrawingAreaItem.h"

#include <QGraphicsSceneMouseEvent>
#include <QMenu>
#include <QPainter>




cDrawingAreaItem::~cDrawingAreaItem()
{
    delete  mPixmap;
}


cDrawingAreaItem::cDrawingAreaItem( QGraphicsItem *parent ) :
    tSuperClass( parent ),
    mPixmap( 0 )
{
    setAcceptHoverEvents( true );
}


//--------------------------------------------------------------------------------------
//-------------------------------------------------------- QGraphicsPixmapItem overrides
//--------------------------------------------------------------------------------------


QRectF
cDrawingAreaItem::boundingRect() const
{
    if( mPixmap )
        return  QRectF( QPoint( 0, 0 ), mPixmap->size() );
    else
        return  QRectF( 0, 0, 0, 0 );
}


void
cDrawingAreaItem::paint( QPainter* iPainter, const QStyleOptionGraphicsItem* iOption, QWidget* iWidget )
{
    if( !mPixmap )
        return;

    // We draw our own pixmap, so we can handle it without copying it everytime
    iPainter->setRenderHint( QPainter::SmoothPixmapTransform, ( transformationMode() == Qt::SmoothTransformation ) );
    iPainter->drawPixmap( offset(), *mPixmap );

    QPen pen( Qt::black );
    pen.setWidth( 1 );
    iPainter->setPen( pen );

    QRectF bounds = boundingRect();
    int contractValue = 1;
    bounds.setLeft( bounds.left() + contractValue );
    bounds.setTop( bounds.top() + contractValue );

    bounds.setWidth( bounds.width() - contractValue );
    bounds.setHeight( bounds.height() - contractValue );

    iPainter->drawRect( bounds );
}


//--------------------------------------------------------------------------------------
//---------------------------------------------------------------------------- Interface
//--------------------------------------------------------------------------------------


QPixmap*
cDrawingAreaItem::Pixmap()
{
    return  mPixmap;
}


QPixmap*
cDrawingAreaItem::Pixmap( const QPixmap & iPixmap )
{
    delete  mPixmap;
    mPixmap = new QPixmap( iPixmap );
    update();
    return  mPixmap;
}


void
cDrawingAreaItem::Pixmap( QPixmap * iPixmap )
{
    delete  mPixmap;
    mPixmap = iPixmap;
    update();
}


//--------------------------------------------------------------------------------------
//------------------------------------------------------------------------------- Events
//--------------------------------------------------------------------------------------


void cDrawingAreaItem::mousePressEvent( QGraphicsSceneMouseEvent* iEvent )
{
    tSuperClass::mousePressEvent( iEvent );
}


void cDrawingAreaItem::mouseMoveEvent( QGraphicsSceneMouseEvent* iEvent )
{
    tSuperClass::mouseMoveEvent( iEvent );
}


void cDrawingAreaItem::mouseReleaseEvent( QGraphicsSceneMouseEvent *iEvent )
{
    tSuperClass::mouseReleaseEvent( iEvent );
}


void
cDrawingAreaItem::contextMenuEvent( QGraphicsSceneContextMenuEvent * iEvent )
{
    //QMenu menu;
    //menu.addAction("Remove Frame");
    //menu.addAction("Select File");
    //QAction *a = menu.exec( iEvent->screenPos() );
    //if( !a )
    //    return;

    //if( a->text() == "Remove Frame" )
    //{
    //    mParentView->ItemAskToBeRemoved( this ); // DON'T DO ANYTHING AFTER THIS
    //    return;
    //}
    //else if( a->text() == "Select File" )
    //{
    //    _SelectNewFile();
    //}
}


