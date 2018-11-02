#include "Editor.Widgets.Animation.GridItem.h"

#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOptionGraphicsItem>



cGridItem::cGridItem( QGraphicsItem* iParent ) :
    QGraphicsItem( iParent )
{
}


QRectF
cGridItem::boundingRect() const
{
    return  QRectF( 0, 0, mSize.width(), mSize.height() );
}


void
cGridItem::paint( QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget )
{
    if( mImageSize > 10 )
    {
        painter->setPen( QColor( 200, 200, 200, 180 ) );

        int numbOfLines = mSize.width() / mImageSize;
        for( int i = 0; i < numbOfLines; ++i )
        {
            int position = int( i*mImageSize );
            painter->drawLine( position, 0, position, mSize.height() );
        }

        int numbOfColu = mSize.height() / mImageSize;
        for( int i = 0; i < numbOfColu; ++i )
        {
            int position = int( i*mImageSize );
            painter->drawLine( 0, position, mSize.width(), position );
        }
    }
}


void
cGridItem::ImageSize( float iImageSize )
{
    mImageSize = iImageSize;
}


void
cGridItem::Size( const QSizeF & iSize )
{
    mSize = iSize;
}


