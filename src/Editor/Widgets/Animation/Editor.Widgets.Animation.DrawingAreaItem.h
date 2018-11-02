#pragma once

#include <QGraphicsPixmapItem>

#include "Core.Base.FileSystem.h"

class  cCustomGraphicsView;

class cDrawingAreaItem :
    public QGraphicsPixmapItem
{
public:
    typedef QGraphicsPixmapItem  tSuperClass;

public:
    virtual  ~cDrawingAreaItem();
    cDrawingAreaItem( QGraphicsItem *parent = Q_NULLPTR );

public:
    // QGraphicsPixmapItem overrides
    QRectF  boundingRect() const override;
    void    paint( QPainter* iPainter, const QStyleOptionGraphicsItem* iOption, QWidget* iWidget ) override;

public:
    // Interface
    QPixmap*    Pixmap();
    QPixmap*    Pixmap( const QPixmap& iPixmap );
    void        Pixmap( QPixmap* iPixmap );

protected:
    // Events
    void    mousePressEvent( QGraphicsSceneMouseEvent* iEvent ) override;
    void    mouseMoveEvent( QGraphicsSceneMouseEvent* iEvent ) override;
    void    mouseReleaseEvent( QGraphicsSceneMouseEvent* iEvent ) override;
    void    contextMenuEvent( QGraphicsSceneContextMenuEvent* iEvent ) override;

private:
    // This pixmap is basically the same concept as the one in QGraphicsPixmapItem,
    // but in QGraphicsPixmapItem, all we can do to setPixmap, is use that function that does copy the entire pixmap everytime ...
    // So here we handle a pointer so we can modify in in canvas freely
    QPixmap*                mPixmap;
};


