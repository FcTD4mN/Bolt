#include "Editor.Widgets.Animation.Canvas.h"


#include "Editor.Models.DrawingToolModelBase.h"
#include "Editor.Widgets.Animation.DrawingAreaItem.h"
#include "Editor.Widgets.Animation.GridItem.h"
#include "Editor.Shortcuts.ShortcutManager.h"


#include <QApplication>
#include <QClipboard>
#include <QColorDialog>
#include <QDragEnterEvent>
#include <QMimeData>



cCanvas::~cCanvas()
{
    delete  mDrawingToolModel;
    delete  mPainter;
}


cCanvas::cCanvas( QWidget* iParent ) :
    tSuperClass( iParent ),
    mItemPixmap( 0 ),
    mDrawingToolModel( 0 ),
    mPainter( 0 ),
    mToolHUDPixmap( 0 )
{
    // Config
    setAcceptDrops( true );

    // Scene
    QGraphicsScene* scene = new QGraphicsScene( this );
    setScene( scene );
    setAlignment( Qt::AlignCenter );

    mDrawingAreaItem = new cDrawingAreaItem();
    scene->addItem( mDrawingAreaItem );
    QRectF sceneRect = geometry();
    setSceneRect( sceneRect );

    mGridItem = new cGridItem();
    scene->addItem( mGridItem );

    setStyleSheet( "background-color: #555555" );

    _ShortcutInit();
}


//--------------------------------------------------------------------------------------
//------------------------------------------------------------------------------- Events
//--------------------------------------------------------------------------------------


void
cCanvas::dragEnterEvent( QDragEnterEvent * iEvent )
{
    iEvent->acceptProposedAction();
}


void
cCanvas::dragMoveEvent( QDragMoveEvent * iEvent )
{
    iEvent->acceptProposedAction();
}


void
cCanvas::dragLeaveEvent( QDragLeaveEvent * iEvent )
{
    iEvent->accept();
}


void
cCanvas::dropEvent( QDropEvent * iEvent )
{
    const QMimeData* mimeData = iEvent->mimeData();
    if( mimeData->hasImage() )
    {
    }
    else if( mimeData->hasUrls() )
    {
    }

    iEvent->acceptProposedAction();
}


void
cCanvas::keyPressEvent( QKeyEvent * iEvent )
{
    if( iEvent->key() == Qt::Key_Alt && QApplication::mouseButtons() & Qt::MouseButton::LeftButton )
        mState = kPan;

    tSuperClass::keyPressEvent( iEvent );
}


void
cCanvas::keyReleaseEvent( QKeyEvent * iEvent )
{
    if( iEvent->key() == Qt::Key_Alt )
    {
        mState = kIdle;
    }
    else if( iEvent->key() == Qt::Key_Delete )
    {
        ClearPixmap();
        currentFrameGotPainted( *mItemPixmap );
        mDrawingAreaItem->update();
    }

    tSuperClass::keyReleaseEvent( iEvent );
}


void
cCanvas::mousePressEvent( QMouseEvent * iEvent )
{
    mClickPos = iEvent->pos();

    if( iEvent->button() == Qt::LeftButton )
    {
        if( QApplication::keyboardModifiers() & Qt::AltModifier )
        {
            mState = kPan;
        }
        else
        {
            mState = kDrawing;
            mPainter = mDrawingToolModel->CreateNewPainter( mItemPixmap );
        }
    }
    else if( iEvent->button() == Qt::RightButton )
    {
        if( QApplication::keyboardModifiers() & Qt::AltModifier )
        {
            mDrawingToolModel->OpenToolDialogAtPosition( iEvent->screenPos(), this );
        }
    }

    tSuperClass::mousePressEvent( iEvent );
}


void
cCanvas::mouseMoveEvent( QMouseEvent * iEvent )
{
    if( mState == kPan )
    {
        QPointF offset = iEvent->pos() - mClickPos;
        QPointF pos = mDrawingAreaItem->pos() + offset;
        mDrawingAreaItem->setPos( pos );
        mGridItem->setPos( pos );
    }
    else if( mState == kDrawing && mPainter )
    {
        QPointF originInItemCoordinate = mDrawingAreaItem->mapFromScene( mapToScene( mClickPos.x(), mClickPos.y() ) );
        QPointF newPointInItemCoordinate = mDrawingAreaItem->mapFromScene( mapToScene( iEvent->pos().x(), iEvent->pos().y() ) );
        mPainter->drawLine( originInItemCoordinate, newPointInItemCoordinate );
        mDrawingAreaItem->update();
        currentFrameGotPainted( *mItemPixmap ); // Slow but works here, if we need optimization, we must either figure why this doiesn't work in Pixmap function below, or add a flag to only send those events when animation is playing back
    }

    mClickPos = iEvent->pos();
    tSuperClass::mouseMoveEvent( iEvent );
}


void
cCanvas::mouseReleaseEvent( QMouseEvent * iEvent )
{
    if( mState == kDrawing )
    {
        delete  mPainter;
        mPainter = 0;
        currentFrameGotPainted( *mItemPixmap );
    }

    mState = kIdle;
    tSuperClass::mouseReleaseEvent( iEvent );
}


void
cCanvas::wheelEvent( QWheelEvent * iEvent )
{
    int delta = iEvent->delta();
    if( QApplication::keyboardModifiers() & Qt::AltModifier )
    {
        if( delta > 0 )
            mDrawingAreaItem->setScale( mDrawingAreaItem->scale() * 1.5 );
        else
            mDrawingAreaItem->setScale( mDrawingAreaItem->scale() / 1.5 );

        _UpdateGridItem();
        _RenewToolHUD();
    }

    tSuperClass::wheelEvent( iEvent );
}


//--------------------------------------------------------------------------------------
//---------------------------------------------------------------------------- Interface
//--------------------------------------------------------------------------------------


void
cCanvas::Pixmap( const QPixmap & iPixmap )
{
    if( mState == kDrawing )
    {
        delete  mPainter;
        //previousFrameGotPainted( *mItemPixmap );
    }

    mItemPixmap = mDrawingAreaItem->Pixmap( iPixmap );
    update();


    if( mState == kDrawing )
    {
        mPainter = mDrawingToolModel->CreateNewPainter( mItemPixmap );
    }
}


void
cCanvas::ClearPixmap()
{
    if( mItemPixmap )
        mItemPixmap->fill( Qt::transparent );
}


void
cCanvas::DrawingToolModel( ::nQt::nModels::cDrawingToolModelBase * iDrawingToolModel )
{
    if( mDrawingToolModel )
        disconnect( mDrawingToolModel, &::nQt::nModels::cDrawingToolModelBase::hudInvalidated, this, &cCanvas::_HUDInvalidated );

    mDrawingToolModel = iDrawingToolModel;

    _RenewToolHUD();
    connect( mDrawingToolModel, &::nQt::nModels::cDrawingToolModelBase::hudInvalidated, this, &cCanvas::_HUDInvalidated );
}


void
cCanvas::CopyPixmapToClipboard()
{
    if( !mItemPixmap )
        return;

    QClipboard* clipboard = QApplication::clipboard();
    clipboard->setPixmap( *mItemPixmap );
}


void
cCanvas::PastePixmapFromCliboard()
{
    if( !mItemPixmap )
        return;

    // This will paste the clipboard at 0,0 in the dest pixmap
    QPainter painter( mItemPixmap );
    QClipboard* clipboard = QApplication::clipboard();
    auto clipboardPixmap = clipboard->pixmap();

    painter.drawPixmap( 0, 0, clipboardPixmap );
    mDrawingAreaItem->update();

    currentFrameGotPainted( *mItemPixmap );
}


//--------------------------------------------------------------------------------------
//-------------------------------------------------------------------------- __PRIVATE__
//--------------------------------------------------------------------------------------


void
cCanvas::_HUDInvalidated()
{
    _RenewToolHUD();
}



void
cCanvas::_ShortcutInit()
{
    auto  copy = SHORTCUT( "AnimationImageCopy" );
    connect( copy, &QShortcut::activated, this, &cCanvas::CopyPixmapToClipboard );
    auto  paste = SHORTCUT( "AnimationImagePaste" );
    connect( paste, &QShortcut::activated, this, &cCanvas::PastePixmapFromCliboard );
}


void
cCanvas::_UpdateGridItem()
{
    float  pixelSize = mDrawingAreaItem->sceneBoundingRect().width() / mDrawingAreaItem->boundingRect().width();

    mGridItem->ImageSize( pixelSize );
    mGridItem->Size( mDrawingAreaItem->sceneBoundingRect().size() );
}


void
cCanvas::_RenewToolHUD()
{
    delete  mToolHUDPixmap;
    mToolHUDPixmap = mDrawingToolModel->CreateHUDPixmap( mDrawingAreaItem->scale() );
    _UpdateToolHUD();
}


void
cCanvas::_UpdateToolHUD()
{
    // If the HUD is bigger than the widget, we don't draw it, we just use an arrow cursor
    if( mToolHUDPixmap->height() > width() )
        setCursor( Qt::ArrowCursor );
    else
        setCursor( QCursor( *mToolHUDPixmap ) );
}

