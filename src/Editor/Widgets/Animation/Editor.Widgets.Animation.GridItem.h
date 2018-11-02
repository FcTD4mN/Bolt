#pragma once

#include <QGraphicsItem>

class cGridItem :
    public QGraphicsItem
{
public:
    typedef QGraphicsItem tSuperClass;

public:
    cGridItem( QGraphicsItem *parent = Q_NULLPTR );

public:
    QRectF  boundingRect() const override;
    void    paint( QPainter *iPainter, const QStyleOptionGraphicsItem *iOption, QWidget *iWidget ) override;

public:
    // Set/Get
    void  ImageSize( float iImageSize );

    void  Size( const QSizeF& iSize );

private:
    float   mImageSize;
    QSizeF  mSize;
};

