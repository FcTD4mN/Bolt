#pragma once

#include <QGraphicsView>


namespace  nQt::nModels  { class cDrawingToolModelBase; }

class cDrawingAreaItem;
class cGridItem;

class cCanvas :
    public QGraphicsView
{
    Q_OBJECT

public:
    typedef QGraphicsView  tSuperClass;

public:
    ~cCanvas();
    cCanvas( QWidget *parent = nullptr );

public:
    // Events
    void  dragEnterEvent( QDragEnterEvent* iEvent ) override;
    void  dragMoveEvent( QDragMoveEvent* iEvent ) override;
    void  dragLeaveEvent( QDragLeaveEvent* iEvent ) override;
    void  dropEvent( QDropEvent* iEvent ) override;

    void  keyPressEvent( QKeyEvent* iEvent ) override;
    void  keyReleaseEvent( QKeyEvent* iEvent ) override;

    void  mousePressEvent( QMouseEvent* iEvent )    override;
    void  mouseMoveEvent( QMouseEvent* iEvent )     override;
    void  mouseReleaseEvent( QMouseEvent* iEvent )  override;
    void  wheelEvent( QWheelEvent* iEvent )  override;

public:
    // Interface
    void  Pixmap( const QPixmap& iPixmap );
    void  ClearPixmap();
    void  DrawingToolModel( ::nQt::nModels::cDrawingToolModelBase*  iDrawingToolModel );

    void  CopyPixmapToClipboard();
    void  PastePixmapFromCliboard();

signals:
    // Signals
    void  currentFrameGotPainted( const QPixmap& iPixmap );


    // __PRIVATE__
private slots:
    void  _HUDInvalidated();

private:
    void  _ShortcutInit();
    void  _UpdateGridItem();
    void  _RenewToolHUD();
    void  _UpdateToolHUD();

private:
    enum  eState
    {
        kIdle,
        kPan,
        kZoom,
        kDrawing
    };

    eState              mState;
    cDrawingAreaItem*   mDrawingAreaItem;
    cGridItem*          mGridItem;
    QPointF             mClickPos;
    QPixmap*            mItemPixmap;


    // Drawing Tool
    ::nQt::nModels::cDrawingToolModelBase*  mDrawingToolModel;
    QPainter*                               mPainter;
    QPixmap*                                mToolHUDPixmap;
};


