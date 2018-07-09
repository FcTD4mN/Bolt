#include "Editor.BoltQtWidgets.SFMLCanvas.h"


#include "Core.Application.GlobalAccess.h"

#include "Core.ECS.Utilities.EntityParser.h"
#include "Core.ECS.Core.Entity.h"
#include "Core.ECS.Core.World.h"
#include "Core.ECS.Core.GlobalEntityMap.h"

#include "Core.ECS.Component.Position.h"
#include "Core.ECS.Component.Size.h"
#include "Core.ECS.Component.SpriteAnimated.h"

#include "Core.Mapping.PhysicEntityGrid.h"

#include "Core.Render.Layer.h"

#include "Core.Screen.Screen.h"

#include "Editor.Application.EditorApplication.h"
#include "Editor.BoltQtModels.EntityModel.h"
#include "Editor.BoltQtDialogs.SnapGridSettings.h"
#include "Editor.HUD.HudTransformation.h"
#include "Editor.HUD.SnapGrid.h"


#include <QtGui/QInputEvent>
#include <QtGui/QPainter>


SFMLCanvas::~SFMLCanvas()
{
    delete  mSnapGrid;
}


SFMLCanvas::SFMLCanvas( QWidget* Parent, const QPoint& Position, const QSize& Size, unsigned int FrameTime ) :
    QWidget( Parent ),
    mRenderWindow( 0 ),
    mState( kIdle ),
    mInitialized( false ),
    mActiveHUD( 0 )
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
    mEntityHUDs.reserve( 64 );
    mSelectionShape.setFillColor( sf::Color( 20, 20, 200, 100 ) );
    mSelectionShape.setOutlineColor( sf::Color( 0, 0, 50, 200 ) );
    mSnapGrid = new ::nQt::nHUD::cSnapGrid( 10, 10 );
}


void
SFMLCanvas::ClearHUDs()
{
    for( auto hud : mEntityHUDs )
    {
        disconnect( hud, SIGNAL( MovedEntity( float, float ) ), this, SLOT( EntityMoved( float, float ) ) );
        disconnect( hud, SIGNAL( ScaledEntity( float, float ) ), this, SLOT( EntityScaled( float, float ) ) );

        delete  hud;
    }

    mEntityHUDs.clear();
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
        mRenderWindow->setSize( sf::Vector2u( iEvent->size().width(), iEvent->size().height() ) );

		auto defView = ::nApplication::cEditorApplication::App()->CurrentScreen()->View();
        defView.setSize( iEvent->size().width(), iEvent->size().height() );
		defView.zoom( ::nApplication::cEditorApplication::App()->CurrentScreen()->ZoomFactor() );

		::nApplication::cEditorApplication::App()->CurrentScreen()->View( defView );
    }
}


void
SFMLCanvas::paintEvent( QPaintEvent* )
{
    mRenderWindow->clear( sf::Color( 200, 200, 200 ) );

	// Resets the view
	mEditorApp->CurrentScreen()->ApplyScreenView();

    if( mSnapGrid->Visible() )
        mSnapGrid->Draw( mRenderWindow );

    DrawSelections();
    mEditorApp->Draw( mRenderWindow );

	// Resets the view
	mEditorApp->CurrentScreen()->ApplyScreenView();

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
		::nGlobal::cGlobalProperties::Instance()->SetTheMainWindow( mRenderWindow );

		// Setting the view
		auto defView = ::nApplication::cEditorApplication::App()->CurrentScreen()->View();
		defView.setSize( mRenderWindow->getSize().x, mRenderWindow->getSize().y );
		defView.zoom( ::nApplication::cEditorApplication::App()->CurrentScreen()->ZoomFactor() );

		::nApplication::cEditorApplication::App()->CurrentScreen()->View( defView );

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
}


void
SFMLCanvas::GetEntitySelectionBox( sf::Vector2f* oPosition, sf::Vector2f* oSize, ::nECS::cEntity * iEntity ) const
{
    float expansionSize = 2.0;

    auto position = dynamic_cast< ::nECS::cPosition* >( iEntity->GetComponentByName( "position" ) );
	if( !position )
	{
		*oPosition	= sf::Vector2f( 0.0F, 0.0F );
		*oSize		= sf::Vector2f( 0.0F, 0.0F );
		return;
	}

    sf::Vector2f entiPos = position->AsVector2F() - sf::Vector2f( expansionSize, expansionSize );
    sf::Vector2f entiSize( 1, 1 );

    auto size = dynamic_cast< ::nECS::cSize* >( iEntity->GetComponentByName( "size" ) );
    if( size )
        entiSize = size->AsVector2F();

    auto sprite = dynamic_cast< ::nECS::cSpriteAnimated* >( iEntity->GetComponentByName( "spriteanimated" ) );
    if( sprite )
        entiSize = sf::Vector2f( sprite->mCurrentSpriteRect.width, sprite->mCurrentSpriteRect.height );

    entiSize += sf::Vector2f( 2 * expansionSize, 2 * expansionSize );

	auto layer = iEntity->Layer();
	if( layer )
		entiPos = layer->MapVectToLayer( entiPos );

    *oPosition = entiPos;
    *oSize = entiSize;
}


sf::Vector2f
SFMLCanvas::GetSizeFromEntity( ::nECS::cEntity* iEntity ) const
{
    auto size = dynamic_cast< ::nECS::cSize* >( iEntity->GetComponentByName( "size" ) );
    auto spriteanimated = dynamic_cast< ::nECS::cSpriteAnimated* >( iEntity->GetComponentByName( "spriteanimated" ) );

    sf::Vector2f entitySize( 1, 1 );
    if( size )
    {
        entitySize = size->AsVector2F();
    }
    else if( spriteanimated )
    {
        entitySize.x = spriteanimated->mCurrentSpriteRect.width;
        entitySize.y = spriteanimated->mCurrentSpriteRect.height;
    }

    return  entitySize;
}


//===========================================================================================================
//=========================================================================================== Event Overrides
//===========================================================================================================


void
SFMLCanvas::mousePressEvent( QMouseEvent * iEvent )
{
    if( iEvent->modifiers() & Qt::AltModifier )
    {
        mState = kPanningCanvas;
    }
    else
    {
        mState = kSelecting;

        for( auto hud : mEntityHUDs )
        {
            sf::Vector2f mouseCoordMapped( mRenderWindow->mapPixelToCoords( sf::Vector2i( iEvent->x(), iEvent->y() ) ) );
            if( hud->ContainsPoint( mouseCoordMapped ) )
            {
                mState		= kHandleHUD;
                mActiveHUD	= hud;
                mActiveHUD->mousePressEvent( iEvent, mRenderWindow );
                break;
            }
        }
    }

    mOriginPosition = sf::Vector2i( iEvent->x(), iEvent->y() );

    tSuperClass::mousePressEvent( iEvent );
}


void
SFMLCanvas::mouseMoveEvent( QMouseEvent * iEvent )
{
    sf::Vector2i currentPos = sf::Vector2i( iEvent->x(), iEvent->y() );
    sf::Vector2f offset = mRenderWindow->mapPixelToCoords( mOriginPosition ) - mRenderWindow->mapPixelToCoords( currentPos );

    if( mState == kPanningCanvas )
    {
        auto defView = ::nApplication::cEditorApplication::App()->CurrentScreen()->View();
        defView.move( offset );
		::nApplication::cEditorApplication::App()->CurrentScreen()->View( defView );
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
    else if( mState == kHandleHUD && mActiveHUD )
    {
        mActiveHUD->mouseMoveEvent( iEvent, mRenderWindow );
    }

    tSuperClass::mouseMoveEvent( iEvent );
}


void
SFMLCanvas::mouseReleaseEvent( QMouseEvent* iEvent )
{
    if( mState == kSelecting )
    {
        std::set< ::nECS::cEntity* > entitiesInEMap;

        if( !( iEvent->modifiers() & Qt::ControlModifier ) && !( iEvent->modifiers() & Qt::ShiftModifier ) )
        {
            ClearHUDs();
        }

		mEditorApp->CurrentScreen()->LayersEnumerator( [ &entitiesInEMap, this ]( ::nRender::cLayer* iLayer ) {

			iLayer->EntityGrid()->GetEntitiesInBoundingBox( &entitiesInEMap,  iLayer->MapRectFromLayer( mSelectionBox ) );

		});

		//::nECS::cGlobalEntityMap::Instance()->mEntityGrid->GetEntitiesInBoundingBox( &entitiesInEMap, mSelectionBox );
		//::nApplication::cEditorApplication::App()->CurrentScreen()->World()->EntityMap()->GetEntitiesInBoundingBox( &entitiesInEMap, mSelectionBox );

        for( auto ent : entitiesInEMap )
        {
            sf::Vector2f selBoxPos;
            sf::Vector2f selBoxSize;
            GetEntitySelectionBox( &selBoxPos, &selBoxSize, ent );

            if( mSelectionBox.contains( selBoxPos ) && mSelectionBox.contains( selBoxPos + selBoxSize ) )
            {
                auto newHud = new ::nQt::nHUD::cHudTransformation( ent );
                connect( newHud, SIGNAL( MovedEntity( float, float  ) ), this, SLOT( EntityMoved( float, float ) ) );
                connect( newHud, SIGNAL( ScaledEntity( float, float ) ), this, SLOT( EntityScaled( float, float ) ) );
                connect( newHud, SIGNAL( StartEditing() ), this, SLOT( StartingEntityEdition() ) );

                mEntityHUDs.push_back( newHud );
            }
        }

        mSelectionBox.height = 0;
        mSelectionBox.width = 0;
        mSelectionShape.setSize( sf::Vector2f( 0.0, 0.0 ) );

        ::nECS::cEntity* sentEntity = 0;
        if( mEntityHUDs.size() == 1 )
            sentEntity = mEntityHUDs[ 0 ]->Entity();

        mEditedEntityModel = new ::nQt::nModels::cEntityModel( sentEntity );

        emit SelectionChanged( sentEntity, mEditedEntityModel );
    }
    else if( mState == kHandleHUD && mActiveHUD )
    {
        mActiveHUD->mouseReleaseEvent( iEvent, mRenderWindow );
        mActiveHUD = 0;
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
    ::nECS::cWorld* world = mEditorApp->CurrentScreen()->World();

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
	//::nApplication::cEditorApplication::App()->CurrentScreen()->World()->EntityMap()->AddEntity( theEnti );

    tSuperClass::mouseDoubleClickEvent( iEvent );
}


void
SFMLCanvas::keyReleaseEvent( QKeyEvent * iEvent )
{
    if( iEvent->key() == Qt::Key_Delete )
    {
        for( auto hud : mEntityHUDs )
        {
			::nECS::cEntity* entity = hud->Entity();
			auto layer = entity->Layer();

			layer->EntityGrid()->RemoveEntity( entity );
            entity->Destroy();
        }

        ClearHUDs();
        mEditorApp->CurrentScreen()->World()->PurgeEntities();
    }

    tSuperClass::keyReleaseEvent( iEvent );
}


void
SFMLCanvas::wheelEvent( QWheelEvent * iEvent )
{
    if( iEvent->modifiers() & Qt::ControlModifier )
    {
        double zoomFactor = 1.5;
        if( iEvent->delta() > 0 )
            zoomFactor = 0.7;

		::nApplication::cEditorApplication::App()->CurrentScreen()->ZoomBy( zoomFactor );
    }

    tSuperClass::wheelEvent( iEvent );
}


void
SFMLCanvas::CurrentPrototypeChanged( const QModelIndex& iIndex )
{
    mCurrentPrototypeEntitySelected = iIndex;
}


void
SFMLCanvas::StartingEntityEdition()
{
    mEntitiesOriginalPositions.clear();
    mEntitiesOriginalSizes.clear();

    for( auto hud : mEntityHUDs )
    {
        auto position = dynamic_cast< ::nECS::cPosition* >( hud->Entity()->GetComponentByName( "position" ) );
        if( position )
            mEntitiesOriginalPositions.push_back( position->AsVector2F() );

        mEntitiesOriginalSizes.push_back( GetSizeFromEntity( hud->Entity() ) );
    }

    Q_ASSERT( mEntitiesOriginalPositions.size() == mEntityHUDs.size() );
    Q_ASSERT( mEntitiesOriginalSizes.size() == mEntityHUDs.size() );
}


void
SFMLCanvas::EntityMoved( float iDeltaX, float iDeltaY )
{
    int indexSync = 0;

    Q_ASSERT( mEntitiesOriginalPositions.size() == mEntityHUDs.size() );
    Q_ASSERT( mEntitiesOriginalSizes.size() == mEntityHUDs.size() );

    for( auto hud : mEntityHUDs )
    {
		::nECS::cEntity* entity = hud->Entity();
		auto layer = entity->Layer();

        auto position = dynamic_cast< ::nECS::cPosition* >( entity->GetComponentByName( "position" ) );
        double newX = mEntitiesOriginalPositions[ indexSync ].x + iDeltaX;
        double newY = mEntitiesOriginalPositions[ indexSync ].y + iDeltaY;

		//::nApplication::cEditorApplication::App()->CurrentScreen()->World()->EntityMap()->RemoveEntityNotUpdated( hud->Entity() );
		//::nECS::cGlobalEntityMap::Instance()->mEntityGrid->RemoveEntityNotUpdated( hud->Entity() );

        if( mSnapGrid->Visible() )
        {
            // the rounding below does this  :  22 ->  20 --> Going left
            //                                 -22 -> -20 --> Going Right
            // So entities get closer by 1 cell size each time you drag ...
            // So, because we want to warp to top left of a cell, when negative, we minus one cell
            // To be simple : Going negative reverses the rounding, so if we are, or we go negative, we compensate
            if( newX < 0 || ( newX == 0 && iDeltaX < 0 ) ) newX -= mSnapGrid->Width();
            if( newY < 0 || ( newY == 0 && iDeltaY < 0 ) ) newY -= mSnapGrid->Height();

            newX = int( newX / mSnapGrid->Width() ) * mSnapGrid->Width();
            newY = int( newY / mSnapGrid->Height() ) * mSnapGrid->Height();
        }

        position->X( newX );
        position->Y( newY );

		//::nApplication::cEditorApplication::App()->CurrentScreen()->World()->EntityMap()->AddEntity( hud->Entity() );
		//::nECS::cGlobalEntityMap::Instance()->mEntityGrid->AddEntity( hud->Entity() );

		layer->EntityGrid()->UpdateEntity( entity );

        ++indexSync;
    }

    for( auto hud : mEntityHUDs )
    {
        hud->UpdateHandlesPositions();
    }

    mEditedEntityModel->UpdateModelByComponentName( "position" );
}


void
SFMLCanvas::EntityScaled( float iDeltaW, float iDeltaH )
{
    int indexSync = -1;

    Q_ASSERT( mEntitiesOriginalPositions.size() == mEntityHUDs.size() );
    Q_ASSERT( mEntitiesOriginalSizes.size() == mEntityHUDs.size() );

    for( auto hud : mEntityHUDs )
    {
        ++indexSync;
        auto size = dynamic_cast< ::nECS::cSize* >( hud->Entity()->GetComponentByName( "size" ) );
        if( !size )
            continue;

        double newW = mEntitiesOriginalSizes[ indexSync ].x + iDeltaW;
        double newH = mEntitiesOriginalSizes[ indexSync ].y + iDeltaH;

        if( mSnapGrid->Visible() )
        {
            // the rounding below does this  : 22 -> 20 --> Going left
            //                                 -22 -> -20 --> Going Right
            // So entities get closer by 1 cell size each time you drag ...
            // So, because we want to warp to top left of a cell, when negative, we minus one cell
            // To be simple : Going negative reverses the rounding, so if we are, or we go negative, we compensate
            if( newW < 0 || ( newW == 0 && iDeltaW < 0 ) ) newW -= mSnapGrid->Width();
            if( newH < 0 || ( newH == 0 && iDeltaH < 0 ) ) newH -= mSnapGrid->Height();

            newW = int( newW / mSnapGrid->Width() ) * mSnapGrid->Width();
            newH = int( newH / mSnapGrid->Height() ) * mSnapGrid->Height();
        }

        size->W( newW );
        size->H( newH );
    }

    for( auto hud : mEntityHUDs )
    {
        hud->UpdateHandlesPositions();
    }

    mEditedEntityModel->UpdateModelByComponentName( "size" );
}


void
SFMLCanvas::ToggleGridVisible()
{
    mSnapGrid->Visible( !mSnapGrid->Visible() );
}


void
SFMLCanvas::SetSnapGridUp()
{
    cSnapGridSettings gridSettingDialog;
    gridSettingDialog.SetCellWidth( mSnapGrid->Width() );
    gridSettingDialog.SetCellHeight( mSnapGrid->Height() );

    if( gridSettingDialog.exec() )
    {
        mSnapGrid->Width( gridSettingDialog.CellWidth() );
        mSnapGrid->Height( gridSettingDialog.CellHeight() );
    }
}

