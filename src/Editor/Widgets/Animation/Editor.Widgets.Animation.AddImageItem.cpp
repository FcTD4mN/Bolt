#include "Editor.Widgets.Animation.AddImageItem.h"

#include "Editor.Widgets.Animation.Timeline.h"

#include <QGraphicsSceneMouseEvent>


cAddImageItem::~cAddImageItem()
{
}


cAddImageItem::cAddImageItem( cAnimationTimeline* iParentView, QGraphicsItem *iParent ) :
    tSuperClass( iParentView, iParent )
{
    setFlags( ItemIsSelectable );
    SetFile( "resources/Editor/icons/AnimationAddImage.png" );
    mDrawSelectionState = false;
}


//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------- Events overrides
//--------------------------------------------------------------------------------------


void
cAddImageItem::mousePressEvent( QGraphicsSceneMouseEvent * iEvent )
{
    QGraphicsPixmapItem::mousePressEvent( iEvent );
}


void
cAddImageItem::mouseMoveEvent( QGraphicsSceneMouseEvent * iEvent )
{
    QGraphicsPixmapItem::mouseMoveEvent( iEvent );
}


void cAddImageItem::mouseReleaseEvent( QGraphicsSceneMouseEvent *iEvent )
{
    mParentTimeline->AddEmptyImage();
    QGraphicsPixmapItem::mouseReleaseEvent( iEvent );
}

