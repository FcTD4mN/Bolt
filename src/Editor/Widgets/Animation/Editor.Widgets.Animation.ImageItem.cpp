#include "Editor.Widgets.Animation.ImageItem.h"

#include "Editor.Widgets.Animation.Timeline.h"

#include <QFileDialog>
#include <QGraphicsSceneMouseEvent>
#include <QMenu>
#include <QPainter>
#include <QStyleOptionGraphicsItem>


cAnimationImageItem::~cAnimationImageItem()
{
}


cAnimationImageItem::cAnimationImageItem( cAnimationTimeline* iParentView, QGraphicsItem *parent ) :
    tSuperClass( parent ),
    mParentTimeline( iParentView ),
    mDrawSelectionState( true ),
    mDirty( false )
{
    setAcceptHoverEvents( true );
    setFlags( ItemIsSelectable | ItemIsMovable | ItemSendsGeometryChanges );
    setShapeMode( BoundingRectShape );

    mColor = Qt::lightGray;
    mColor.setAlpha( 20 );
}


//--------------------------------------------------------------------------------------
//------------------------------------------------------------------------------ Get/Set
//--------------------------------------------------------------------------------------


void
cAnimationImageItem::SetFile( const QString & iFile )
{
    QTransform transform;
    QPixmap pixmap = QPixmap::fromImage( QImage( iFile ) );
    setPixmap( pixmap );
    transform.scale( qreal( mParentTimeline->ItemWidth() ) / qreal( pixmap.width() ), qreal( mParentTimeline->ItemHeight() ) / qreal( pixmap.height() ) );
    setTransform( transform );
}


void
cAnimationImageItem::Dirty( bool iDirty )
{
    mDirty = iDirty;
}


bool
cAnimationImageItem::Dirty() const
{
    return  mDirty;
}


//--------------------------------------------------------------------------------------
//-------------------------------------------------------------- QGraphicsItem overrides
//--------------------------------------------------------------------------------------


QRectF
cAnimationImageItem::boundingRect() const
{
    // Might be able to get rid of this, but i'm waiting to see if there aren't any cases where we wouldn't have a pixmap on item, and thus, require a bounding rect custom
    return  tSuperClass::boundingRect();
}


void
cAnimationImageItem::paint( QPainter* iPainter, const QStyleOptionGraphicsItem* iOption, QWidget* iWidget )
{
    // Background
    QColor background = QColor( 0, 0, 0, 125 );
    iPainter->setBrush( background );
    iPainter->setPen( Qt::transparent );
    iPainter->drawRect( boundingRect() );

    // Pixmap
    iPainter->setRenderHint( QPainter::SmoothPixmapTransform, ( transformationMode() == Qt::SmoothTransformation ) );
    iPainter->drawPixmap( offset(), pixmap() );

    // Hover/Selection
    QColor fillColor = QColor( 20, 20, 200, 50 );
    bool draw = false;

    if( iOption->state & QStyle::State_Selected && mDrawSelectionState )
        draw = true;

    if( iOption->state & QStyle::State_MouseOver )
    {
        fillColor = fillColor.lighter( 125 );
        draw = true;
    }

    if( draw )
    {
        iPainter->setBrush( fillColor );
        iPainter->drawRect( boundingRect() );
    }
}


QVariant
cAnimationImageItem::itemChange( GraphicsItemChange iChange, const QVariant& iValue )
{
    QPointF newPoint = iValue.toPointF();

    if( iChange == ItemPositionChange && scene() )
    {
        newPoint.setY( mParentTimeline->height()/2 - mParentTimeline->ItemHeight()/2 );
        if( newPoint.x() < 0 )
            newPoint.setX( 0 );

        mParentTimeline->ImageIsMoving();
        return newPoint;
    }

    return tSuperClass::itemChange( iChange, iValue );
}


QPainterPath
cAnimationImageItem::shape() const
{
    QPainterPath path;
    path.addRect( boundingRect() );
    return  path;
}


//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------- Events overrides
//--------------------------------------------------------------------------------------


void cAnimationImageItem::mousePressEvent( QGraphicsSceneMouseEvent* iEvent )
{
    setZValue( 1 );
    update();
    mParentTimeline->ItemStartedMoving();
    tSuperClass::mousePressEvent( iEvent );
}


void cAnimationImageItem::mouseMoveEvent( QGraphicsSceneMouseEvent* iEvent )
{
    tSuperClass::mouseMoveEvent( iEvent );
}


void cAnimationImageItem::mouseReleaseEvent( QGraphicsSceneMouseEvent *iEvent )
{
    setZValue( -1 );
    mParentTimeline->ImageStopedMoving();
    update();
    tSuperClass::mouseReleaseEvent( iEvent );
}


void
cAnimationImageItem::mouseDoubleClickEvent( QGraphicsSceneMouseEvent * iEvent )
{
    _SelectNewFile();
}


void
cAnimationImageItem::contextMenuEvent( QGraphicsSceneContextMenuEvent * iEvent )
{
    QMenu menu;
    menu.addAction( "Remove Image" );
    menu.addAction( "Select Image" );
    QAction* action = menu.exec( iEvent->screenPos() );
    if( !action )
        return;

    if( action->text() == "Remove Image" )
    {
        mParentTimeline->RemoveImage( this ); // THIS ITEM WILL BE DELETED AFTER THIS CALL, SO DON'T DO ANYTHING ELSE
        return;
    }
    else if( action->text() == "Select Image" )
    {
        _SelectNewFile();
    }
}


//--------------------------------------------------------------------------------------
//---------------------------------------------------------------------------- _PRIVATE_
//--------------------------------------------------------------------------------------


void
cAnimationImageItem::_SelectNewFile()
{
    QString fileName = QFileDialog::getOpenFileName( 0, "Select Image", "", "Image Files (*.png *.jpg *.bmp)" );
    if( !fileName.isEmpty() )
        mParentTimeline->ItemImageFileChanged( this, fileName );
}