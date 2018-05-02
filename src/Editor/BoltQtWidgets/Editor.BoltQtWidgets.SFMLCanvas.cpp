#include "Editor.BoltQtWidgets.SFMLCanvas.h"

#include "Editor.Application.EditorApplication.h"

#include "Core.ECS.Utilities.EntityParser.h"
#include "Core.ECS.Core.Entity.h"
#include "Core.ECS.Core.World.h"
#include "Core.ECS.Core.GlobalEntityMap.h"

#include "Core.ECS.Component.Position.h"
#include "Core.ECS.Component.Size.h"
#include "Core.ECS.Component.SpriteAnimated.h"

#include "Editor.HUD.HudTransformation.h"

#include "Core.Mapping.PhysicEntityGrid.h"

#include <QtGui/QInputEvent>
#include <QtGui/QPainter>


SFMLCanvas::SFMLCanvas( QWidget* Parent, const QPoint& Position, const QSize& Size, unsigned int FrameTime ) :
    QWidget( Parent ),
    mRenderWindow( 0 ),
    mState( kIdle ),
    mInitialized( false )
{
    // Setup some states to allow direct rendering into the widget
    setAttribute( Qt::WA_PaintOnScreen );
    setAttribute( Qt::WA_OpaquePaintEvent );
    setAttribute( Qt::WA_NoSystemBackground );

    // Set strong focus to enable keyboard events to be received
    setFocusPolicy( Qt::StrongFocus );

    // Setup the widget geometry
    move( Position );
    resize( Size );

    // Setup the timer
    mTimer.setInterval( FrameTime );

    Build();
}


SFMLCanvas::SFMLCanvas( QWidget* Parent ) :
    QWidget( Parent ),
    mRenderWindow( 0 ),
    mState( kIdle ),
    mInitialized( false )
{
    // Setup some states to allow direct rendering into the widget
    setAttribute( Qt::WA_PaintOnScreen );
    setAttribute( Qt::WA_OpaquePaintEvent );
    setAttribute( Qt::WA_NoSystemBackground );

    // Set strong focus to enable keyboard events to be received
    setFocusPolicy( Qt::StrongFocus );

    // Setup the timer
    mTimer.setInterval( 0 );

    Build();
}


void
SFMLCanvas::SetEditorApp( ::nApplication::cEditorApplication * iEditorApp )
{
    mEditorApp = iEditorApp;
}


void
SFMLCanvas::Build()
{
    mEntitySelection.reserve( 64 );
    mSelectionShape.setFillColor( sf::Color( 20, 20, 200, 100 ) );
    mSelectionShape.setOutlineColor( sf::Color( 0, 0, 50, 200 ) );
}


void
SFMLCanvas::OnInit()
{
}

void
SFMLCanvas::OnUpdate()
{
    // We don't want the world to update actually in the editor
    //mEditorApp->Update( 0 );
}


void
SFMLCanvas::resizeEvent( QResizeEvent * iEvent )
{
    if( mRenderWindow )
    {
        auto defView = mRenderWindow->getView();
        defView.setSize( iEvent->size().width(), iEvent->size().height() );
        mRenderWindow->setView( defView );

        mRenderWindow->setSize( sf::Vector2u( iEvent->size().width(), iEvent->size().height() ) );
    }
}


void
SFMLCanvas::paintEvent( QPaintEvent* )
{
    mRenderWindow->clear( sf::Color( 200, 200, 200 ) );


    DrawSelections();
    mEditorApp->Draw( mRenderWindow );

    for( auto hud : mEntityHUDs )
        hud->Draw( mRenderWindow );

    if( mState == kSelecting )
        mRenderWindow->draw( mSelectionShape );


    mRenderWindow->display();
}


void
SFMLCanvas::showEvent( QShowEvent* )
{
    if( !mInitialized )
    {
        // Under X11, we need to flush the commands sent to the server to ensure that
        // SFML will get an updated view of the windows
#ifdef Q_WS_X11
        XFlush( QX11Info::display() );
#endif

        // Create the SFML window with the widget handle
        mRenderWindow = new sf::RenderWindow( ( sf::WindowHandle )winId() );

        // Let the derived class do its specific stuff
        OnInit();

        // Setup the timer to trigger a refresh at specified framerate
        connect( &mTimer, SIGNAL( timeout() ), this, SLOT( repaint() ) );
        mTimer.start();

        mInitialized = true;
    }
}


QPaintEngine*
SFMLCanvas::paintEngine() const
{
    return  0;
}


void
SFMLCanvas::DrawSelections() const
{
    sf::RectangleShape entitySelectionBox;
    entitySelectionBox.setFillColor( sf::Color( 200, 100, 100 ) );
    entitySelectionBox.setOutlineColor( sf::Color( 255, 50, 100 ) );

    float expansionSize = 2.0;

    for( auto ent : mEntitySelection )
    {
        sf::Vector2f selBoxPos;
        sf::Vector2f selBoxSize;
        GetEntitySelectionBox( &selBoxPos, &selBoxSize, ent );
        entitySelectionBox.setPosition( selBoxPos );
        entitySelectionBox.setSize( selBoxSize );

        mRenderWindow->draw( entitySelectionBox );
    }
}


void
SFMLCanvas::GetEntitySelectionBox( sf::Vector2f* oPosition, sf::Vector2f* oSize, ::nECS::cEntity * iEntity ) const
{
    float expansionSize = 2.0;

    auto position = dynamic_cast< ::nECS::cPosition* >( iEntity->GetComponentByName( "position" ) );
    sf::Vector2f entiPos = position->AsVector2F() - sf::Vector2f( expansionSize, expansionSize );
    sf::Vector2f entiSize( 1, 1 );

    auto size = dynamic_cast< ::nECS::cSize* >( iEntity->GetComponentByName( "size" ) );
    if( size )
        entiSize = size->AsVector2F();

    auto sprite = dynamic_cast< ::nECS::cSpriteAnimated* >( iEntity->GetComponentByName( "spriteanimated" ) );
    if( sprite )
        entiSize = sf::Vector2f( sprite->mCurrentSpriteRect.width, sprite->mCurrentSpriteRect.height );

    entiSize += sf::Vector2f( 2 * expansionSize, 2 * expansionSize );

    *oPosition = entiPos;
    *oSize = entiSize;
}


//===========================================================================================================
//=========================================================================================== Event Overrides
//===========================================================================================================


void
SFMLCanvas::mousePressEvent( QMouseEvent * iEvent )
{
    if( iEvent->modifiers() & Qt::AltModifier )
        mState = kPanningCanvas;
    else
        mState = kSelecting;

    for( auto hud : mEntityHUDs )
    {
        sf::Vector2f mouseCoordMapped( mRenderWindow->mapPixelToCoords( sf::Vector2i( iEvent->x(), iEvent->y() ) ) );
        if( hud->ContainsPoint( mouseCoordMapped ) )
        {
            mState = kHandleHUD;
            hud->mousePressEvent( iEvent, mRenderWindow );
            break;
        }
    }

    mOriginPosition = sf::Vector2i( iEvent->x(), iEvent->y() );

    for( auto ent : mEntitySelection )
    {
        sf::Vector2f selBoxPos;
        sf::Vector2f selBoxSize;
        GetEntitySelectionBox( &selBoxPos, &selBoxSize, ent );

        sf::FloatRect entSelBox( selBoxPos, selBoxSize );

        if( entSelBox.contains( mRenderWindow->mapPixelToCoords( sf::Vector2i( iEvent->x(), iEvent->y() ) ) ) )
        {
            mState = kMoveEntity;
            break;
        }
    }

    tSuperClass::mousePressEvent( iEvent );
}


void
SFMLCanvas::mouseMoveEvent( QMouseEvent * iEvent )
{
    sf::Vector2i currentPos = sf::Vector2i( iEvent->x(), iEvent->y() );
    sf::Vector2i offset = mOriginPosition - currentPos;

    if( mState == kPanningCanvas )
    {
        auto defView = mRenderWindow->getView();
        defView.move( sf::Vector2f( float(offset.x), float(offset.y) ) );
        mRenderWindow->setView( defView );
        mOriginPosition = currentPos;
    }
    else if( mState == kSelecting )
    {
        int minX = mOriginPosition.x;
        int minY = mOriginPosition.y;

        int maxX = iEvent->x();
        int maxY = iEvent->y();

        if( minX > maxX )
        {
            minX = maxX;
            maxX = mOriginPosition.x;
        }

        if( minY > maxY )
        {
            minY = maxY;
            maxY = mOriginPosition.y;
        }

        sf::Vector2f xy = mRenderWindow->mapPixelToCoords( sf::Vector2i( minX, minY ) );
        sf::Vector2f x2y2 = mRenderWindow->mapPixelToCoords( sf::Vector2i( maxX, maxY ) );

        mSelectionShape.setPosition( xy );
        mSelectionShape.setSize( x2y2 - xy );
        mSelectionBox = sf::FloatRect( xy, x2y2 - xy );
    }
    else if( mState == kMoveEntity )
    {
        for( auto ent : mEntitySelection )
        {
            auto position = dynamic_cast< ::nECS::cPosition* >( ent->GetComponentByName( "position" ) );
            position->X( position->X() - offset.x );
            position->Y( position->Y() - offset.y );
        }

        mOriginPosition = currentPos;
    }

    tSuperClass::mouseMoveEvent( iEvent );
}


void
SFMLCanvas::mouseReleaseEvent( QMouseEvent* iEvent )
{
    if( mState == kSelecting )
    {
        std::vector< ::nECS::cEntity* > entitiesInEMap;

        if( !( iEvent->modifiers() & Qt::ControlModifier ) && !( iEvent->modifiers() & Qt::ShiftModifier ) )
        {
            for( auto hud : mEntityHUDs )
                delete  hud;

            mEntityHUDs.clear();
            mEntitySelection.clear();
        }

        ::nECS::cGlobalEntityMap::Instance()->mEntityGrid->GetEntitiesInBoundingBox( &entitiesInEMap, mSelectionBox );

        for( auto ent : entitiesInEMap )
        {
            sf::Vector2f selBoxPos;
            sf::Vector2f selBoxSize;
            GetEntitySelectionBox( &selBoxPos, &selBoxSize, ent );

            if( mSelectionBox.contains( selBoxPos ) && mSelectionBox.contains( selBoxPos + selBoxSize ) )
            {
                mEntityHUDs.push_back( new ::nQt::nHUD::cHudTransformation( ent ) );
                mEntitySelection.push_back( ent );
            }
        }

        mSelectionBox.height = 0;
        mSelectionBox.width = 0;
        mSelectionShape.setSize( sf::Vector2f( 0.0, 0.0 ) );

        ::nECS::cEntity* sentEntity = 0;
        if( mEntitySelection.size() == 1 )
            sentEntity = mEntitySelection[ 0 ];

        emit SelectionChanged( sentEntity );
    }

    mState = kIdle;

    tSuperClass::mouseReleaseEvent( iEvent );
}


void
SFMLCanvas::mouseDoubleClickEvent( QMouseEvent * iEvent )
{
    if( !mCurrentPrototypeEntitySelected.isValid() )
        return;

    ::nECS::cEntityParser* ep = ::nECS::cEntityParser::Instance();
    ::nECS::cWorld* world = mEditorApp->World();

    std::string name = mCurrentPrototypeEntitySelected.data( Qt::DisplayRole ).toString().toStdString();
    ::nECS::cEntity* theEnti = ep->CreateEntityFromPrototypeMap( name.c_str() );


    sf::Vector2f convert = mRenderWindow->mapPixelToCoords( sf::Vector2i( iEvent->localPos().x() , iEvent->localPos().y() ) );

    auto position = dynamic_cast< ::nECS::cPosition* >( theEnti->GetComponentByName( "position" ) );
    if( position )
    {
        position->X( convert.x );
        position->Y( convert.y );
    }
    world->AddEntity( theEnti );

    ::nECS::cGlobalEntityMap::Instance()->mEntityGrid->AddEntity( theEnti );

    tSuperClass::mouseDoubleClickEvent( iEvent );
}


void
SFMLCanvas::keyReleaseEvent( QKeyEvent * iEvent )
{
    if( iEvent->key() == Qt::Key_Delete )
    {
        for( auto ent : mEntitySelection )
        {
            ::nECS::cGlobalEntityMap::Instance()->mEntityGrid->RemoveEntityNotUpdated( ent );
            ent->Destroy();
        }

        mEntitySelection.clear();
        mEditorApp->World()->PurgeEntities();
    }

    tSuperClass::keyReleaseEvent( iEvent );
}


void
SFMLCanvas::CurrentPrototypeChanged( const QModelIndex& iIndex )
{
    mCurrentPrototypeEntitySelected = iIndex;
}

