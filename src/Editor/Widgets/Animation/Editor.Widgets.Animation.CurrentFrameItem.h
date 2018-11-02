#pragma once

#include <QGraphicsItem>

class  cAnimationTimeline;

class cAnimationCurrentFrameItem :
    public QGraphicsItem
{
public:
    typedef QGraphicsItem tSuperClass;

public:
    virtual  ~cAnimationCurrentFrameItem();
    cAnimationCurrentFrameItem( cAnimationTimeline* iParentTimeline, QGraphicsItem *iParent = Q_NULLPTR );

public:
    // Get/Set
    void  IsAnimationPlaying( bool iIsAnimationPlaying );

public:
    // QGraphicsItem overrides
    QRectF      boundingRect() const override;
    void        paint( QPainter* iPainter, const QStyleOptionGraphicsItem* iOption, QWidget* iWidget ) override;
    QVariant    itemChange( GraphicsItemChange iChange, const QVariant& iValue ) override;


private:
    cAnimationTimeline*     mParentTimeline;
    QColor                  mColor;

    bool                    mIsAnimationPlaying;
};

