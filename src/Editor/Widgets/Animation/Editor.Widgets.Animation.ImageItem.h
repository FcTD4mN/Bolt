#pragma once

#include <QGraphicsPixmapItem>

class  cAnimationTimeline;

class cAnimationImageItem :
    public QGraphicsPixmapItem
{
public:
    typedef QGraphicsPixmapItem tSuperClass;

public:
    virtual     ~cAnimationImageItem();
                cAnimationImageItem( cAnimationTimeline* iParentView, QGraphicsItem *parent = Q_NULLPTR );

public:
    // Get/Set
    void    SetFile( const QString& iFile );
    void    Dirty( bool iDirty );
    bool    Dirty() const;

public:
    // QGraphicsItem overrides
    QRectF          boundingRect() const override;
    void            paint( QPainter* iPainter, const QStyleOptionGraphicsItem* iOption, QWidget* iWidget ) override;
    QVariant        itemChange( GraphicsItemChange iChange, const QVariant& iValue ) override;
    QPainterPath    shape() const override;

protected:
    // Events overrides
    void        mousePressEvent( QGraphicsSceneMouseEvent* iEvent ) override;
    void        mouseMoveEvent( QGraphicsSceneMouseEvent* iEvent ) override;
    void        mouseReleaseEvent( QGraphicsSceneMouseEvent* iEvent ) override;
    void        mouseDoubleClickEvent( QGraphicsSceneMouseEvent* iEvent ) override;

    void        contextMenuEvent( QGraphicsSceneContextMenuEvent* iEvent ) override;

private:
    // _PRIVATE_
    void  _SelectNewFile();

protected:
    QColor                  mColor;
    cAnimationTimeline*     mParentTimeline;
    bool                    mDrawSelectionState;
    bool                    mDirty; // Dirty == has been modifed and needs a save
};


