#pragma once

#include "Editor.Widgets.Animation.ImageItem.h"


class cAddImageItem :
    public cAnimationImageItem
{
public:
    typedef cAnimationImageItem tSuperClass;

public:
    virtual  ~cAddImageItem();
    cAddImageItem( cAnimationTimeline* iParentView, QGraphicsItem *iParent = Q_NULLPTR );

protected:
    // Events overrides
    void  mousePressEvent( QGraphicsSceneMouseEvent* iEvent ) override;
    void  mouseMoveEvent( QGraphicsSceneMouseEvent* iEvent ) override;
    void  mouseReleaseEvent( QGraphicsSceneMouseEvent* iEvent ) override;
};
