#include "Editor.Widgets.Animation.CurrentFrameItem.h"

#include "Editor.Widgets.Animation.Timeline.h"

#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOptionGraphicsItem>


#define WIDTH           mParentTimeline->ItemWidth() + 4
#define FRAMEHEIGHT     mParentTimeline->ItemHeight()
#define HEIGHT          mParentTimeline->height() - 4
#define YPOS            0


cAnimationCurrentFrameItem::~cAnimationCurrentFrameItem()
{
}


cAnimationCurrentFrameItem::cAnimationCurrentFrameItem( cAnimationTimeline* iParentTimeline, QGraphicsItem* iParent ) :
    tSuperClass( iParent ),
    mParentTimeline( iParentTimeline )
{
    setAcceptHoverEvents( true );
    setFlags( ItemIsSelectable | ItemIsMovable | ItemSendsGeometryChanges );
    setZValue( -5 );

    mColor = QColor( 120, 205, 233 );
    mIsAnimationPlaying = false;
}


//--------------------------------------------------------------------------------------
//------------------------------------------------------------------------------ Get/Set
//--------------------------------------------------------------------------------------


void
cAnimationCurrentFrameItem::IsAnimationPlaying( bool iIsAnimationPlaying )
{
    mIsAnimationPlaying = iIsAnimationPlaying;
}


//--------------------------------------------------------------------------------------
//-------------------------------------------------------------- QGraphicsItem overrides
//--------------------------------------------------------------------------------------


QRectF
cAnimationCurrentFrameItem::boundingRect() const
{
    return  QRectF( 0, 0, WIDTH, HEIGHT );
}


void
cAnimationCurrentFrameItem::paint( QPainter* iPainter, const QStyleOptionGraphicsItem* iOption, QWidget* iWidget )
{
    QColor fillColor = mColor;

    if( mIsAnimationPlaying )
        fillColor = QColor( 31, 237, 181 );

    if( iOption->state & QStyle::State_Selected )
        mColor.darker( 150 );

    if( iOption->state & QStyle::State_MouseOver )
        fillColor = fillColor.lighter( 125 );

    iPainter->setBrush( fillColor );
    iPainter->drawRect( 0, 0, WIDTH, HEIGHT );
}


QVariant
cAnimationCurrentFrameItem::itemChange( GraphicsItemChange iChange, const QVariant& iValue )
{
    QPointF newPoint = iValue.toPointF();
    int currentFrame = newPoint.x() / ( mParentTimeline->ItemWidth() + mParentTimeline->ItemSpacing() );

    if( iChange == ItemPositionChange && scene() )
    {
        if( currentFrame < 0 )
            currentFrame = 0;
        if( currentFrame >= mParentTimeline->AnimationImages().size() )
            currentFrame = mParentTimeline->AnimationImages().size() - 1;

        newPoint.setY( 2 );
        newPoint.setX( currentFrame * mParentTimeline->ItemSpacing() + currentFrame * mParentTimeline->ItemWidth() );

        return newPoint;
    }
    else if( iChange == ItemPositionHasChanged && scene() )
    {
        mParentTimeline->CurrentFrameItemStopMoving();
    }

    return tSuperClass::itemChange( iChange, iValue );
}

