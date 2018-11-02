#include "Editor.Widgets.Animation.Timeline.h"


#include "Core.Animation.Animation.h"
#include "Core.Application.GlobalAccess.h"
#include "Core.Base.ResourceManager.h"
#include "Core.Base.Utilities.h"


#include "Editor.Shortcuts.ShortcutManager.h"
#include "Editor.Widgets.Animation.ImageItem.h"
#include "Editor.Widgets.Animation.AddImageItem.h"
#include "Editor.Widgets.Animation.CurrentFrameItem.h"


#include <QDragEnterEvent>
#include <QMimeData>
#include <QtGlobal>
#include <QShortcut>


#define ITEMYPOSITION height()/2 - mItemHeight/2

cAnimationTimeline::~cAnimationTimeline()
{
    delete  mAddImageItem;
    delete  mCurrentFrameItem;
}


cAnimationTimeline::cAnimationTimeline( QWidget *parent ) :
    QGraphicsView( parent ),
    mAnimation( 0 ),
    mCurrentFrame( 0 ),
    mItemWidth( 64 ),
    mItemHeight( 64 ),
    mItemSpacing( 5 ),
    mFirstLeftOffset( 2 ),
    mItemMovingLock( false )
{
    // View setup
    setDragMode( RubberBandDrag );
    setAcceptDrops( true );
    setFixedHeight( mItemHeight + 32 );

    // Graphic scene
    QGraphicsScene* scene = new QGraphicsScene( this );
    setScene( scene );
    setAlignment( Qt::AlignVCenter | Qt::AlignLeft );

    mAddImageItem = new  cAddImageItem( this );
    mAddImageItem->setZValue( -1 );
    scene->addItem( mAddImageItem );

    mCurrentFrameItem = new cAnimationCurrentFrameItem( this );
    scene->addItem( mCurrentFrameItem );

    _UpdateAllItemsPositions();
    _UpdateCurrentFrameItemPosition();
    _UpdateSceneRect();

    _ShortcutInit();
}


//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------- Events overrides
//--------------------------------------------------------------------------------------


void
cAnimationTimeline::mousePressEvent( QMouseEvent * iEvent )
{
    mClickOrigin = iEvent->pos();
    tSuperClass::mousePressEvent( iEvent );
}


void
cAnimationTimeline::mouseReleaseEvent( QMouseEvent * iEvent )
{
    QGraphicsView::mouseReleaseEvent( iEvent );

    if( !mAnimation )
        return;

    QPoint delta = iEvent->pos() - mClickOrigin;

    if( delta.x() <= -1 || delta.x() >= 1 )
    {
        for( auto imageItem : mAllAnimationImages )
            if( imageItem->isSelected() )
                return;
    }

    auto clickPosInScene = mapToScene( iEvent->pos() );

    int index = clickPosInScene.x() / (mItemWidth + mItemSpacing);
    if( index >= 0 && index < mAllAnimationImages.size() )
        CurrentFrameChanged( index );
}


void
cAnimationTimeline::keyReleaseEvent( QKeyEvent * iEvent )
{
    if( !mAnimation )
        return;

    if( iEvent->key() == Qt::Key_Delete && !mItemMovingLock )
    {
        for( int i = mAllAnimationImages.size() - 1; i >= 0; --i )
            if( mAllAnimationImages[ i ]->isSelected() )
                RemoveImage( mAllAnimationImages[ i ] );

        if( mCurrentFrame >= mAllAnimationImages.size() )
            CurrentFrameChanged( mAllAnimationImages.size() - 1 );

        _UpdateSceneRect();
    }

    tSuperClass::keyPressEvent( iEvent );
}


void
cAnimationTimeline::dragEnterEvent( QDragEnterEvent * iEvent )
{
    iEvent->acceptProposedAction();
}


void
cAnimationTimeline::dragMoveEvent( QDragMoveEvent * iEvent )
{
    iEvent->acceptProposedAction();
}


void
cAnimationTimeline::dragLeaveEvent( QDragLeaveEvent * iEvent )
{
    iEvent->accept();
}


void
cAnimationTimeline::dropEvent( QDropEvent * iEvent )
{
    if( !mAnimation )
        return;

    const QMimeData* mimeData = iEvent->mimeData();
    if( mimeData->hasImage() )
    {
        // Here we don't even have a reference file, so it's hard to handle
        //auto item = new  cAnimationImageItem( this );
        //item->setZValue( -1 );
        //item->setPixmap( qvariant_cast<QPixmap>( mimeData->imageData() ) );
        //scene()->addItem( item );
        //mAllAnimationImages.push_back( item );
        //_UpdateAllItemsPositions();
        //_UpdateSceneRect();
    }
    else if( mimeData->hasUrls() )
    {
        QList< QUrl > urlList = mimeData->urls();
        for( auto& url : urlList )
        {
            mAnimation->AddImage( url.toLocalFile().toStdString() );
            _AddImageItem();
            LoadSpriteAtIndex( mAnimation->SpriteCount()-1 );
            _UpdateAllItemsPositions();
        }
        _UpdateSceneRect();
    }

    iEvent->acceptProposedAction();
}


//--------------------------------------------------------------------------------------
//------------------------------------------------------------------------------ Getters
//--------------------------------------------------------------------------------------


QVector< cAnimationImageItem* >&
cAnimationTimeline::AnimationImages()
{
    return  mAllAnimationImages;
}


int
cAnimationTimeline::ItemWidth() const
{
    return  mItemWidth;
}


int
cAnimationTimeline::ItemHeight() const
{
    return  mItemHeight;
}


int
cAnimationTimeline::ItemSpacing() const
{
    return  mItemSpacing;
}


//--------------------------------------------------------------------------------------
//-------------------------------------------------------- AnimationsComponent Interface
//--------------------------------------------------------------------------------------


void
cAnimationTimeline::SetupAnimation( ::nCore::nAnimation::cAnimation * iAnimation )
{
    _DeleteAllImageItems();

    mAnimation = iAnimation;

    if( mAnimation )
    {
        for( int i = 0; i < mAnimation->SpriteCount(); ++i )
        {
            _AddImageItem();
            LoadSpriteAtIndex( i );
        }
        CurrentFrameChanged( mCurrentFrame );
    }
}


void
cAnimationTimeline::LoadSpriteAtIndex( int iIndex )
{
    if( !mAnimation )
        return;

    auto imageItem = dynamic_cast<cAnimationImageItem*>( mAllAnimationImages[ iIndex ] );
    if( !imageItem )
        return;

    sf::Sprite* sprite = mAnimation->SpriteAtIndex( iIndex );
    const sf::Texture* texture = sprite->getTexture();

    // Setting size, if there are images, we'll use the last image's size, which should make sense as you are trying to complete the animation
    // Here we are in loadSpriteAtIndex, which will load into a newlyCreated imageItem the sprite of the animation.
    // Therefore, the last loaded image from animation is not the last item, but the one before.
    QSize newSpriteSize( mItemWidth, mItemHeight );
    if( mAllAnimationImages.size() > 1 )
        newSpriteSize = mAllAnimationImages[ mAllAnimationImages.size() - 2 ]->pixmap().size();

    QPixmap pixmap( newSpriteSize );
    pixmap.fill( Qt::transparent );
    if( texture )
    {
        sf::Image image = texture->copyToImage();
        const uchar* data = image.getPixelsPtr();
        pixmap = QPixmap::fromImage( QImage( data, image.getSize().x, image.getSize().y, QImage::Format_RGBA8888 ) );
        // From here, it can have noAlpha if image has no transparent pixels
    }

    QTransform transform;
    imageItem->setPixmap( pixmap );
    transform.scale( qreal(mItemWidth) / qreal(pixmap.width()), qreal(mItemHeight) / qreal(pixmap.height()) );
    imageItem->setTransform( transform );

    if( iIndex == mCurrentFrame )
        emit  currentFrameChanged();
}


//--------------------------------------------------------------------------------------
//---------------------------------------------------------------------- Items interface
//--------------------------------------------------------------------------------------


void
cAnimationTimeline::AddEmptyImage()
{
    if( !mAnimation )
        return;

    mAnimation->AddImage( "" );
    _AddImageItem();
    LoadSpriteAtIndex( mAnimation->SpriteCount() - 1 );
    _UpdateAllItemsPositions();
    _UpdateSceneRect();
}


void
cAnimationTimeline::RemoveImage( cAnimationImageItem * iItem )
{
    if( !mAnimation )
        return;

    mAnimation->RemoveImageByIndex( _GetItemIndex( iItem ) );

    scene()->removeItem( iItem );
    delete  iItem;
    _SortImageItems();
    _UpdateAllItemsPositions();
    _UpdateSceneRect();

    CurrentFrameChanged( ::nCore::nBase::Clamp( mCurrentFrame, 0, int(mAnimation->SpriteCount()) - 1 ) );
    emit numberOfFrameChanged();
}



void
cAnimationTimeline::ItemStartedMoving()
{
    mItemMovingLock = true;
}

void
cAnimationTimeline::ImageIsMoving()
{
    // Preview stuff todo one day
}


void
cAnimationTimeline::ImageStopedMoving()
{
    if( !mAnimation )
        return;

    mItemMovingLock = false;
    _SortImageItems();
    _UpdateAllItemsPositions();
    emit  currentFrameChanged();
}


void
cAnimationTimeline::CurrentFrameItemStopMoving()
{
    if( !mAnimation )
        return;

    int index = mCurrentFrameItem->pos().x() / (mItemWidth + mItemSpacing);

    mCurrentFrame = ::nCore::nBase::Clamp( index, 0, int( mAnimation->SpriteCount() ) - 1 );
    emit  currentFrameChanged();
}


void
cAnimationTimeline::CurrentFrameChanged( int iCurrent )
{
    if( !mAnimation )
        return;

    mCurrentFrame = ::nCore::nBase::Clamp( iCurrent, 0, int( mAnimation->SpriteCount() ) - 1 );
    _UpdateCurrentFrameItemPosition();
    emit  currentFrameChanged();
}


void
cAnimationTimeline::GoToNextFrame()
{
    if( !mAnimation )
        return;

    CurrentFrameChanged( ++mCurrentFrame % mAllAnimationImages.size() );
}


void
cAnimationTimeline::GoToPreviousFrame()
{
    if( !mAnimation )
        return;

    int prevFrame = mCurrentFrame - 1;
    if( prevFrame < 0 )
        prevFrame = mAllAnimationImages.size() - 1;

    CurrentFrameChanged( prevFrame );
}


void
cAnimationTimeline::GoToFrame( int iFrame )
{
    if( !mAnimation )
        return;

    CurrentFrameChanged( iFrame );
}


void
cAnimationTimeline::ItemImageFileChanged( const cAnimationImageItem* iItem, const QString& iNewFile )
{
    if( !mAnimation )
        return;

    int index = _GetItemIndex( iItem );
    mAnimation->ChangeImageAtIndex( index, iNewFile.toStdString() );
    LoadSpriteAtIndex( index );
}


QPixmap
cAnimationTimeline::CurrentPixmap() const
{
    return  mAllAnimationImages[ mCurrentFrame ]->pixmap();
}


//--------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------- SLOTS
//--------------------------------------------------------------------------------------


void
cAnimationTimeline::CurrentFrameGotPainted( const QPixmap& iNewPixmap )
{
    if( mAllAnimationImages.size() > 0 )
    {
        auto imageItem = mAllAnimationImages[ mCurrentFrame ];
        imageItem->setPixmap( iNewPixmap );
        imageItem->Dirty( true );
    }
}


void
cAnimationTimeline::SaveAnimationToFiles()
{
    for( int i = 0; i < mAllAnimationImages.size(); ++i )
    {
        auto imageItem = mAllAnimationImages[ i ];
        if( imageItem->Dirty() )
        {
            QPixmap px = imageItem->pixmap();
            ::nStdFileSystem::path spriteFile = mAnimation->SpriteFileAtIndex( i );
            if( !::nStdFileSystem::exists( spriteFile ) )
            {
                spriteFile = PROJECTDIR + "/Assets/Images/Animations" + mAnimation->Name() + "/";
                if( !::nStdFileSystem::exists( spriteFile ) )
                    nStdFileSystem::create_directory( spriteFile );

                spriteFile += mAnimation->Name() + "_" + std::to_string( i ) + ".png";

            }

            bool result = px.save( spriteFile.string().c_str(), "PNG" );
            imageItem->Dirty( false );

            // Image changed, so we invalidate it from ResourceManager and reload it in animation
            ::nCore::nBase::cResourceManager::Instance()->InvalidateTexture( spriteFile );
            mAnimation->ChangeImageAtIndex( i, spriteFile );
        }
    }
}


void
cAnimationTimeline::CurrentFrameSizeChanged( const QSize& iSize )
{
    if( mAllAnimationImages.size() == 0 )
        return;

    QPixmap newSizedPixmap( iSize );
    newSizedPixmap.fill( Qt::transparent );
    auto currentImagePixmap = mAllAnimationImages[ mCurrentFrame ]->pixmap();

    QPainter painter( &newSizedPixmap );
    painter.drawPixmap( 0, 0, currentImagePixmap );

    CurrentFrameGotPainted( newSizedPixmap );
    QTransform transform;
    transform.scale( qreal( mItemWidth ) / qreal( newSizedPixmap.width() ), qreal( mItemHeight ) / qreal( newSizedPixmap.height() ) );
    mAllAnimationImages[ mCurrentFrame ]->setTransform( transform );
    emit currentFrameChanged();
}


//--------------------------------------------------------------------------------------
//---------------------------------------------------------------------------- _PRIVATE_
//--------------------------------------------------------------------------------------


void cAnimationTimeline::_ShortcutInit()
{
    auto play = SHORTCUT( "AnimationPlay" );
    connect( play, &QShortcut::activated, this, &cAnimationTimeline::askPlayAnimation );

    auto previousFrame = SHORTCUT( "AnimationPreviousFrame" );
    connect( previousFrame, &QShortcut::activated, this, &cAnimationTimeline::GoToPreviousFrame );

    auto nextFrame = SHORTCUT( "AnimationNextFrame" );
    connect( nextFrame, &QShortcut::activated, this, &cAnimationTimeline::GoToNextFrame );
}


void cAnimationTimeline::_SortImageItems()
{
    QVector< cAnimationImageItem* > oldOrder = mAllAnimationImages;

    mAllAnimationImages.clear();
    for( auto item : scene()->items() )
    {
        if( item == mAddImageItem || item == mCurrentFrameItem )
            continue;

        QPointF position = item->pos();

        int i;
        for( i = 0; i < mAllAnimationImages.size(); ++i )
        {
            if( mAllAnimationImages.at( i )->pos().x() > position.x() )
                break;
        }

        auto itemAsGI = dynamic_cast<cAnimationImageItem* >( item );
        if( itemAsGI )
            mAllAnimationImages.insert( i, itemAsGI );
        else
            itemAsGI->acceptDrops(); // CRASH so we are aware in this example if any mistake is done
    }

    // Otherwise, it means we removed elements, and then synchronization is kept
    if( oldOrder.size() == mAllAnimationImages.size() )
    {
        for( int i = 0; i < mAllAnimationImages.size(); ++i )
        {
            if( oldOrder[ i ] != mAllAnimationImages[ i ] )
            {
                int oldItemIndex = 0;
                for( auto itemInOldOrder : oldOrder )
                {
                    if( itemInOldOrder == mAllAnimationImages[ i ] )
                        break;
                    ++oldItemIndex;
                }

                mAnimation->SwapImagesAtIndexes( i, oldItemIndex );
            }
        }
    }
}


int
cAnimationTimeline::_GetItemIndex( const cAnimationImageItem * iItem ) const
{
    int i = -1;
    for( auto item : mAllAnimationImages )
    {
        ++i;
        if( item == iItem )
            return  i;
    }

    return  i;
}


void
cAnimationTimeline::_DeleteAllImageItems()
{
    for( auto item : mAllAnimationImages )
        delete  item;

    mAllAnimationImages.clear();

    _UpdateAllItemsPositions(); // To position the add button
    _UpdateCurrentFrameItemPosition();
    CurrentFrameChanged( 0 );
    _UpdateSceneRect();
}


void
cAnimationTimeline::_UpdateSceneRect()
{
    int imageCount = mAllAnimationImages.size();
    int totalWidth = imageCount * mItemWidth + imageCount * mItemSpacing;

    // As long as mAddItem button thing is in the timeline
    totalWidth += mItemWidth + mItemSpacing;

    setSceneRect( 0, 0, totalWidth, height() );
}


cAnimationImageItem*
cAnimationTimeline::_AddImageItem()
{
    int index = scene()->items().size() - 2; // Cuz addbutton and currentFrame is within
    mAddImageItem->setPos( mFirstLeftOffset + ( index + 1 ) * mItemSpacing + ( index + 1 ) * mItemWidth, ITEMYPOSITION );


    auto imageItem = new  cAnimationImageItem( this );
    imageItem->setPos( mFirstLeftOffset + index * mItemSpacing + index * mItemWidth, ITEMYPOSITION );
    imageItem->setZValue( -1 );
    imageItem->setSelected( true );
    scene()->addItem( imageItem );
    mAllAnimationImages.push_back( imageItem );

    emit numberOfFrameChanged();

    return  imageItem;
}


void
cAnimationTimeline::_UpdateAllItemsPositions()
{
    int i = 0;
    for( i = 0; i < mAllAnimationImages.size(); ++i )
        mAllAnimationImages[ i ]->setPos( mFirstLeftOffset + i * mItemSpacing + i * mItemWidth, ITEMYPOSITION );

    mAddImageItem->setPos( mFirstLeftOffset + i * mItemSpacing + i * mItemWidth, ITEMYPOSITION );
}


void
cAnimationTimeline::_UpdateCurrentFrameItemPosition()
{
    mCurrentFrameItem->setVisible( mAllAnimationImages.size() != 0 );
    mCurrentFrameItem->setPos( mCurrentFrame * mItemSpacing + mCurrentFrame * mItemWidth, 2 );
}


