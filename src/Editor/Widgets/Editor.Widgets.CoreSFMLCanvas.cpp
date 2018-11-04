#include "Editor.Widgets.CoreSFMLCanvas.h"


#include "Core.Application.GlobalAccess.h"

#include "Core.Registries.EntityRegistry.h"
#include "Core.ECS.Core.Entity.h"
#include "Core.ECS.Core.World.h"

#include "Core.ECS.Component.Transformation.h"
#include "Core.ECS.Component.Animations.h"

#include "Core.Mapping.PhysicEntityGrid.h"

#include "Core.Project.Project.h"

#include "Core.Render.Layer.h"
#include "Core.Render.LayerEngine.h"

#include "Core.Screen.Screen.h"
#include "Editor.Models.EntityModel.h"
#include "Editor.Models.ProjectHierarchyModel.h"
#include "Editor.Dialogs.SnapGridSettings.h"
#include "Editor.HUD.HudTransformation.h"
#include "Editor.HUD.SnapGrid.h"


#include <QtGui/QInputEvent>
#include <QtGui/QPainter>


CoreSFMLCanvas::~CoreSFMLCanvas()
{
    delete  mSnapGrid;
}


CoreSFMLCanvas::CoreSFMLCanvas( QWidget* Parent, const QPoint& Position, const QSize& Size, unsigned int FrameTime ) :
    tSuperClass( Parent ),
    mProjectModel( 0 ),
    mState( kIdle ),
    mInitialized( false ),
    mActiveHUD( 0 ),
    mNeedDuplication( false )
{
    // Setup the widget geometry
    move( Position );
    resize( Size );

    Build();
}


CoreSFMLCanvas::CoreSFMLCanvas( QWidget* Parent ) :
    tSuperClass( Parent ),
    mProjectModel( 0 ),
    mState( kIdle ),
    mInitialized( false ),
    mActiveHUD( 0 ),
    mNeedDuplication( false )
{
    Build();
}


void
CoreSFMLCanvas::Build()
{
    mEntityHUDs.reserve( 64 );
    mSelectionShape.setFillColor( sf::Color( 20, 20, 200, 100 ) );
    mSelectionShape.setOutlineColor( sf::Color( 0, 0, 50, 200 ) );
    mSnapGrid = new ::nQt::nHUD::cSnapGrid( 10, 10 );
}


void
CoreSFMLCanvas::ClearHUDs()
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
CoreSFMLCanvas::OnInit()
{
}

void
CoreSFMLCanvas::OnUpdate()
{
    // We don't want the world to update actually in the editor
    //mEditorApp->Update( 0 );
}

void
CoreSFMLCanvas::OnDraw()
{
    sf::RenderWindow::clear( sf::Color( 200, 200, 200 ) );

    if( !_Project() )
        return;

    auto currentScreen = _Project()->CurrentScreen();
    if( currentScreen )
    {
        // Resets the view
        currentScreen->ApplyScreenView();

        if( mSnapGrid->Visible() )
            mSnapGrid->Draw( this );

        DrawSelections();
        _Project()->CurrentScreen()->Draw( this );

        // Resets the view
        currentScreen->ApplyScreenView();

        for( auto hud : mEntityHUDs )
            hud->Draw( this );

        if( mState == kRubberSelection )
            sf::RenderWindow::draw( mSelectionShape );
    }

    sf::RenderWindow::display();
}


void
CoreSFMLCanvas::resizeEvent( QResizeEvent * event )
{
    if( mInitialized && _Project() )
    {
        sf::RenderWindow::setSize( sf::Vector2u( event->size().width(), event->size().height() ) );

        auto currentScreen = _Project()->CurrentScreen();
        if( currentScreen )
        {
            // Setting the view
            auto defView = currentScreen->View();
            defView.setSize( event->size().width(), event->size().height() );
            defView.zoom( currentScreen->ZoomFactor() );

            currentScreen->View( defView );
        }
    }
}


void
CoreSFMLCanvas::showEvent( QShowEvent*  event )
{
    QSFMLWidget::showEvent( event );

    if( !mInitialized )
    {
        ::nCore::nApplication::cGlobalAccess::Instance()->TheMainWindow( this );

        // Let the derived class do its specific stuff
        OnInit();

        mInitialized = true;
    }
}


void
CoreSFMLCanvas::DrawSelections() const
{
    sf::RectangleShape entitySelectionBox;
    entitySelectionBox.setFillColor( sf::Color( 200, 100, 100 ) );
    entitySelectionBox.setOutlineColor( sf::Color( 255, 50, 100 ) );

    float expansionSize = 2.0;
}


void
CoreSFMLCanvas::GetEntitySelectionBox( sf::Vector2f* oPosition, sf::Vector2f* oSize, ::nCore::nECS::nCore::cEntity * iEntity ) const
{
    float expansionSize = 2.0;

    auto transformation = dynamic_cast< ::nCore::nECS::nComponent::cTransformation* >( iEntity->GetComponentByID( "transformation" ) );
    if( !transformation )
    {
        *oPosition  = sf::Vector2f( 0.0F, 0.0F );
        *oSize      = sf::Vector2f( 0.0F, 0.0F );
        return;
    }

    sf::Vector2f entiPos = transformation->PositionAsVector2F() - sf::Vector2f( expansionSize, expansionSize );
    sf::Vector2f entiSize = transformation->SizeAsVector2F();

    entiSize += sf::Vector2f( 2 * expansionSize, 2 * expansionSize );

    auto layer = iEntity->Layer();
    if( layer )
        entiPos = layer->MapVectToLayer( entiPos );

    *oPosition = entiPos;
    *oSize = entiSize;
}


sf::Vector2f
CoreSFMLCanvas::GetSizeFromEntity( ::nCore::nECS::nCore::cEntity* iEntity ) const
{
    auto transformation = iEntity->GetComponentByIDAs< ::nCore::nECS::nComponent::cTransformation* >( "transformation" );
    auto animations = iEntity->GetComponentByIDAs< ::nCore::nECS::nComponent::cAnimations* >( "animations" );

    sf::Vector2f entitySize( 1, 1 );
    if( transformation )
    {
        entitySize = transformation->SizeAsVector2F();
    }
    else if( animations )
    {
        entitySize.x = animations->CurrentAnimationSpriteWidth();
        entitySize.y = animations->CurrentAnimationSpriteHeight();
    }

    return  entitySize;
}


//===========================================================================================================
//=========================================================================================== Event Overrides
//===========================================================================================================


void
CoreSFMLCanvas::mousePressEvent( QMouseEvent * iEvent )
{
    if( !_Project() )
        return;

    auto currentScreen = _Project()->CurrentScreen();
    if( !currentScreen )
        return;

    if( iEvent->modifiers() & Qt::AltModifier )
    {
        mState = kPanningCanvas;
    }
    else
    {
        mState = kClickSelection;

        for( auto hud : mEntityHUDs )
        {
            sf::Vector2f mouseCoordMapped( sf::RenderWindow::mapPixelToCoords( sf::Vector2i( iEvent->x(), iEvent->y() ) ) );
            if( hud->ContainsPoint( mouseCoordMapped ) )
            {
                mState      = kHandleHUD;
                mActiveHUD  = hud;
                mActiveHUD->mousePressEvent( iEvent, this );
                break;
            }
        }
    }

    mOriginPosition = sf::Vector2i( iEvent->x(), iEvent->y() );


    tSuperClass::mousePressEvent( iEvent );
}


void
CoreSFMLCanvas::mouseMoveEvent( QMouseEvent * iEvent )
{
    if( !_Project() )
        return;

    sf::Vector2i currentPos = sf::Vector2i( iEvent->x(), iEvent->y() );
    sf::Vector2f offset = sf::RenderWindow::mapPixelToCoords( mOriginPosition ) - sf::RenderWindow::mapPixelToCoords( currentPos );

    auto currentScreen = _Project()->CurrentScreen();
    if( !currentScreen )
        return;

    if( mState == kPanningCanvas )
    {
        auto defView = currentScreen->View();
        defView.move( offset );
        currentScreen->View( defView );
        mOriginPosition = currentPos;
    }
    else if( mState == kClickSelection || mState == kRubberSelection )
    {
        mState = kRubberSelection;

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

        sf::Vector2f xy = sf::RenderWindow::mapPixelToCoords( sf::Vector2i( minX, minY ) );
        sf::Vector2f x2y2 = sf::RenderWindow::mapPixelToCoords( sf::Vector2i( maxX, maxY ) );

        mSelectionShape.setPosition( xy );
        mSelectionShape.setSize( x2y2 - xy );
        mSelectionBox = sf::FloatRect( xy, x2y2 - xy );
    }
    else if( mState == kHandleHUD && mActiveHUD )
    {
        mActiveHUD->mouseMoveEvent( iEvent, this );
    }

    tSuperClass::mouseMoveEvent( iEvent );
}


void
CoreSFMLCanvas::mouseReleaseEvent( QMouseEvent* iEvent )
{
    if( !_Project() )
        return;

    if( mState == kRubberSelection || mState == kClickSelection )
    {
        std::set< ::nCore::nECS::nCore::cEntity* > entitiesInEMap;
        std::vector< ::nCore::nECS::nCore::cEntity* > selectedEntities;

        if( !( iEvent->modifiers() & Qt::ControlModifier ) && !( iEvent->modifiers() & Qt::ShiftModifier ) )
        {
            ClearHUDs();
        }

        if( mSelectionBox.width == 0 || mSelectionBox.height == 0 )
        {
            sf::Vector2f xy = sf::RenderWindow::mapPixelToCoords( mOriginPosition );
            mSelectionBox.left = xy.x;
            mSelectionBox.top = xy.y;
            mSelectionBox.width = 1;
            mSelectionBox.height = 1;
        }

        _Project()->CurrentScreen()->LayersEnumerator( [ &entitiesInEMap, this ]( ::nCore::nRender::cLayer* iLayer ) {

            iLayer->EntityGrid()->GetEntitiesInBoundingBox( &entitiesInEMap,  iLayer->MapRectFromLayer( mSelectionBox ) );

        });

        ::nCore::nECS::nCore::cEntity* closestEntityAtClick = 0;

        for( auto ent : entitiesInEMap )
        {
            sf::Vector2f selBoxPos;
            sf::Vector2f selBoxSize;
            GetEntitySelectionBox( &selBoxPos, &selBoxSize, ent );
            sf::FloatRect entitySelBox( selBoxPos, selBoxSize );

            if( mSelectionBox.intersects( entitySelBox ) )
            {
                if( mState == kRubberSelection )
                {
                    // This allows a single pass doing both HUDs and selectedEntities fill in O(n) even though it duplicates code
                    auto newHud = new ::nQt::nHUD::cHudTransformation( ent );
                    connect( newHud, SIGNAL( MovedEntity( float, float  ) ), this, SLOT( EntityMoved( float, float ) ) );
                    connect( newHud, SIGNAL( ScaledEntity( float, float ) ), this, SLOT( EntityScaled( float, float ) ) );
                    connect( newHud, SIGNAL( StartEditing() ), this, SLOT( StartingEntityEdition() ) );

                    mEntityHUDs.push_back( newHud );
                    selectedEntities.push_back( ent );
                }
                else if( mState == kClickSelection ) // No dragging, only one click, we take the closest entity
                {
                    if( !closestEntityAtClick )
                        closestEntityAtClick = ent;

                    // Using the layers obviously to figure entity's positionning on Z axis
                    auto layer = ent->Layer();
                    auto closestLayer = closestEntityAtClick->Layer();

                    if( layer == closestLayer ) // If same layers, we look at the closest in the layer ( greatest index )
                    {
                        if( layer->EntityIndex( closestEntityAtClick ) < layer->EntityIndex( ent ) )
                            closestEntityAtClick = ent;
                    }
                    else // Otherwise, we take the one on the closest layer ( greatest index )
                    {
                        if( closestLayer->LayerIndex() < layer->LayerIndex() )
                            closestEntityAtClick = ent;
                    }
                }
            }
        }

        if( closestEntityAtClick && mState == kClickSelection )
        {
            selectedEntities.push_back( closestEntityAtClick );
            auto newHud = new ::nQt::nHUD::cHudTransformation( closestEntityAtClick );
            connect( newHud, SIGNAL( MovedEntity( float, float ) ), this, SLOT( EntityMoved( float, float ) ) );
            connect( newHud, SIGNAL( ScaledEntity( float, float ) ), this, SLOT( EntityScaled( float, float ) ) );
            connect( newHud, SIGNAL( StartEditing() ), this, SLOT( StartingEntityEdition() ) );

            mEntityHUDs.push_back( newHud );
        }

        mSelectionBox.height = 0;
        mSelectionBox.width = 0;
        mSelectionShape.setSize( sf::Vector2f( 0.0, 0.0 ) );

        ::nCore::nECS::nCore::cEntity* sentEntity = 0;
        if( mEntityHUDs.size() == 1 )
            sentEntity = mEntityHUDs[ 0 ]->Entity();

        mEditedEntityModel = std::make_shared< ::nQt::nModels::cEntityModel >( sentEntity );
        emit selectionChanged( selectedEntities );
    }
    else if( mState == kHandleHUD && mActiveHUD )
    {
        mActiveHUD->mouseReleaseEvent( iEvent, this );
        mActiveHUD = 0;
    }

    mState = kIdle;

    tSuperClass::mouseReleaseEvent( iEvent );
}


void
CoreSFMLCanvas::mouseDoubleClickEvent( QMouseEvent * iEvent )
{
    if( !mCurrentPrototypeEntitySelected.isValid() || !_Project() )
        return;

    auto ep = ::nCore::nRegistries::cEntityRegistry::Instance();
    auto world = _Project()->CurrentScreen()->World();

    std::string name = mCurrentPrototypeEntitySelected.data( Qt::DisplayRole ).toString().toStdString();
    ::nCore::nECS::nCore::cEntity* theEnti = ep->CreateEntityFromPrototypeMap( name.c_str() );

    sf::Vector2f convert = sf::RenderWindow::mapPixelToCoords( sf::Vector2i( iEvent->localPos().x() , iEvent->localPos().y() ) );

    auto transformation = dynamic_cast< ::nCore::nECS::nComponent::cTransformation* >( theEnti->GetComponentByID( "transformation" ) );
    if( transformation )
    {
        transformation->X( convert.x );
        transformation->Y( convert.y );
    }

    //world->AddEntity( theEnti );
    mProjectModel->AddEntityToCurrentScreenInLayer( theEnti, 0 );

    tSuperClass::mouseDoubleClickEvent( iEvent );
}


void
CoreSFMLCanvas::keyReleaseEvent( QKeyEvent * iEvent )
{
    if( iEvent->key() == Qt::Key_Delete && _Project() )
    {
        for( auto hud : mEntityHUDs )
        {
            ::nCore::nECS::nCore::cEntity* entity = hud->Entity();
            auto layer = entity->Layer();

            mProjectModel->RemoveEntity( entity );
            emit selectionChanged( std::vector< ::nCore::nECS::nCore::cEntity* >() );
        }

        ClearHUDs();
        _Project()->CurrentScreen()->World()->PurgeEntities();
    }

    tSuperClass::keyReleaseEvent( iEvent );
}


void
CoreSFMLCanvas::wheelEvent( QWheelEvent * iEvent )
{
    if( !_Project() )
        return;

    auto currentScreen = _Project()->CurrentScreen();
    if( !currentScreen )
        return;

    if( iEvent->modifiers() & Qt::AltModifier )
    {
        double zoomFactor = 1.5;
        if( iEvent->delta() > 0 )
            zoomFactor = 0.7;

        currentScreen->ZoomBy( zoomFactor );
    }

    tSuperClass::wheelEvent( iEvent );
}


void
CoreSFMLCanvas::ScreenEditionAsked( const QModelIndex& iIndex )
{
    if( !_Project() )
        return;

    _Project()->SetCurrentScreen( iIndex.data( Qt::DisplayRole ).toString().toStdString() );
}


void
CoreSFMLCanvas::CurrentPrototypeChanged( const QModelIndex& iIndex )
{
    mCurrentPrototypeEntitySelected = iIndex;
}


void
CoreSFMLCanvas::StartingEntityEdition()
{
    if( qApp->keyboardModifiers() & Qt::ControlModifier )
        mNeedDuplication = true;

    mEntitiesOriginalPositions.clear();
    mEntitiesOriginalSizes.clear();

    for( auto hud : mEntityHUDs )
    {
        auto transformation = dynamic_cast< ::nCore::nECS::nComponent::cTransformation* >( hud->Entity()->GetComponentByID( "transformation" ) );
        if( transformation )
            mEntitiesOriginalPositions.push_back( transformation->PositionAsVector2F() );

        mEntitiesOriginalSizes.push_back( GetSizeFromEntity( hud->Entity() ) );
    }

    Q_ASSERT( mEntitiesOriginalPositions.size() == mEntityHUDs.size() );
    Q_ASSERT( mEntitiesOriginalSizes.size() == mEntityHUDs.size() );
}


void
CoreSFMLCanvas::EntityMoved( float iDeltaX, float iDeltaY )
{
    int indexSync = 0;

    Q_ASSERT( mEntitiesOriginalPositions.size() == mEntityHUDs.size() );
    Q_ASSERT( mEntitiesOriginalSizes.size() == mEntityHUDs.size() );

    for( auto hud : mEntityHUDs )
    {
        ::nCore::nECS::nCore::cEntity* entity = hud->Entity();

        if( mNeedDuplication )
            mProjectModel->CloneEntity( entity );

        auto transformation = dynamic_cast< ::nCore::nECS::nComponent::cTransformation* >( entity->GetComponentByID( "transformation" ) );
        double newX = mEntitiesOriginalPositions[ indexSync ].x + iDeltaX;
        double newY = mEntitiesOriginalPositions[ indexSync ].y + iDeltaY;

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

        transformation->X( newX );
        transformation->Y( newY );

        ++indexSync;
    }

    for( auto hud : mEntityHUDs )
        hud->UpdateHandlesPositions();

    mEditedEntityModel->UpdateModelByComponentName( "position" );
    emit  forceRefresh();

    mNeedDuplication = false;
}


void
CoreSFMLCanvas::EntityScaled( float iDeltaW, float iDeltaH )
{
    int indexSync = -1;

    Q_ASSERT( mEntitiesOriginalPositions.size() == mEntityHUDs.size() );
    Q_ASSERT( mEntitiesOriginalSizes.size() == mEntityHUDs.size() );

    for( auto hud : mEntityHUDs )
    {
        ++indexSync;
        auto transformation = dynamic_cast< ::nCore::nECS::nComponent::cTransformation* >( hud->Entity()->GetComponentByID( "transformation" ) );
        if( !transformation )
            continue;

        double newW = mEntitiesOriginalSizes[ indexSync ].x + iDeltaW;
        double newH = mEntitiesOriginalSizes[ indexSync ].y + iDeltaH;

        if( mSnapGrid->Visible() )
        {
            // the rounding below does this  :  22 -> 20 --> Going left
            //                                 -22 -> -20 --> Going Right
            // So entities get closer by 1 cell size each time you drag ...
            // So, because we want to warp to top left of a cell, when negative, we minus one cell
            // To be simple : Going negative reverses the rounding, so if we are, or we go negative, we compensate
            if( newW < 0 || ( newW == 0 && iDeltaW < 0 ) ) newW -= mSnapGrid->Width();
            if( newH < 0 || ( newH == 0 && iDeltaH < 0 ) ) newH -= mSnapGrid->Height();

            newW = int( newW / mSnapGrid->Width() ) * mSnapGrid->Width();
            newH = int( newH / mSnapGrid->Height() ) * mSnapGrid->Height();
        }

        transformation->W( newW );
        transformation->H( newH );
    }

    for( auto hud : mEntityHUDs )
    {
        hud->UpdateHandlesPositions();
    }

    mEditedEntityModel->UpdateModelByComponentName( "size" );
    emit  forceRefresh();
}


void
CoreSFMLCanvas::ProjectLoaded( ::nQt::nModels::cProjectHierarchyModel * iProject )
{
    mProjectModel = iProject;

    auto currentScreen = _Project()->CurrentScreen();
    if( currentScreen )
    {
        // Setting the view
        auto defView = currentScreen->View();
        defView.setSize( sf::RenderWindow::getSize().x, sf::RenderWindow::getSize().y );
        defView.zoom( currentScreen->ZoomFactor() );

        currentScreen->View( defView );
    }
}


::nCore::nProject::cProject*
CoreSFMLCanvas::_Project()
{
    if( mProjectModel )
        return  mProjectModel->Project();
    else
        return  0;
}


void
CoreSFMLCanvas::ToggleGridVisible()
{
    mSnapGrid->Visible( !mSnapGrid->Visible() );
}


void
CoreSFMLCanvas::SetSnapGridUp()
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


