#pragma once

#include <QGraphicsView>


namespace nCore::nAnimation { class cAnimation; }

class  cAnimationImageItem;
class  cAddImageItem;
class  cAnimationCurrentFrameItem;

class cAnimationTimeline :
    public QGraphicsView
{
    Q_OBJECT

public:
    typedef QGraphicsView tSuperClass;

public:
    virtual  ~cAnimationTimeline();
    cAnimationTimeline( QWidget *parent = Q_NULLPTR );

public:
    // Events overrides
    void  mousePressEvent( QMouseEvent* iEvent ) override;
    void  mouseReleaseEvent( QMouseEvent* iEvent ) override;

    void  keyReleaseEvent( QKeyEvent* iEvent ) override;

    void  dragEnterEvent( QDragEnterEvent* iEvent ) override;
    void  dragMoveEvent( QDragMoveEvent* iEvent ) override;
    void  dragLeaveEvent( QDragLeaveEvent* iEvent ) override;
    void  dropEvent( QDropEvent* iEvent ) override;

public:
    // Getters
    QVector< cAnimationImageItem* >&  AnimationImages();

    int  ItemWidth() const;
    int  ItemHeight() const;
    int  ItemSpacing() const;

public:
    // AnimationsComponent Interface
    //void  AddImageFromTexture( const sf::Texture& iTexture );
    void  SetupAnimation( ::nCore::nAnimation::cAnimation* iAnimation );
    void  LoadSpriteAtIndex( int iIndex );



    // Below methods are essentally item-timeline communication
public:
    // Items interface
    void    AddEmptyImage();
    void    RemoveImage( cAnimationImageItem* iItem );

    void    ItemStartedMoving(); // Needed because deleting an item whil moving it, will cause mouseRelease to never being called on the delete item, causing bugs
    void    ImageIsMoving();
    void    ImageStopedMoving();
    void    CurrentFrameItemStopMoving();

    void    CurrentFrameChanged( int iCurrent );
    void    GoToNextFrame();
    void    GoToPreviousFrame();
    void    GoToFrame( int iFrame );

    void    ItemImageFileChanged( const cAnimationImageItem* iItem, const QString& iNewFile );

    // Let's hope copying QPixmap isn't too cost heavy, but item's.pixmap() function returns QPixmap ...
    QPixmap CurrentPixmap() const;


signals:
    void    currentFrameChanged();
    void    numberOfFrameChanged();
    void    askPlayAnimation();

public slots:
    void    CurrentFrameGotPainted( const QPixmap& iNewPixmap );
    void    SaveAnimationToFiles();
    void    CurrentFrameSizeChanged( const QSize& iSize );


private:
    // _PRIVATE_
        // Shortcuts
    void                    _ShortcutInit();

        // Items
    cAnimationImageItem*    _AddImageItem();
    void                    _UpdateAllItemsPositions();
    void                    _UpdateCurrentFrameItemPosition();
    void                    _SortImageItems();
    int                     _GetItemIndex( const cAnimationImageItem* iItem ) const;
    void                    _DeleteAllImageItems();

        // Scene
    void                    _UpdateSceneRect();


private:
    // The animation
    ::nCore::nAnimation::cAnimation*    mAnimation;
    int                                 mCurrentFrame;

    // All items
    QVector< cAnimationImageItem* >     mAllAnimationImages;
    cAddImageItem*                      mAddImageItem;
    cAnimationCurrentFrameItem*         mCurrentFrameItem;

    // Item values
    int                                 mItemWidth;
    int                                 mItemHeight;
    int                                 mItemSpacing;
    int                                 mFirstLeftOffset;
    bool                                mItemMovingLock;

    QPoint                              mClickOrigin;
};

