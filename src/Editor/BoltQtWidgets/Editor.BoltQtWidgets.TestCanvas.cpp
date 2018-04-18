#include "Editor.BoltQtWidgets.TestCanvas.h"

#include "Editor.Application.EditorApplication.h"

#include "Core.ECS.Utilities.EntityParser.h"
#include "Core.ECS.Core.Entity.h"
#include "Core.ECS.Core.World.h"
#include "Core.ECS.Core.GlobalEntityMap.h"

#include "Core.ECS.Component.Position.h"
#include "Core.ECS.Component.Size.h"
#include "Core.Mapping.PhysicEntityGrid.h"


#include <QtGui/QInputEvent>
#include <QtGui/QPainter>


MyCanvas::MyCanvas( QWidget* Parent, const QPoint& Position, const QSize& Size ) :
    QSFMLCanvas( Parent, Position, Size ),
    mState( kIdle )
{
    Build();
}


MyCanvas::MyCanvas( QWidget* Parent ) :
    QSFMLCanvas( Parent ),
    mState( kIdle )
{
    Build();
}


void
MyCanvas::SetEditorApp( ::nApplication::cEditorApplication * iEditorApp )
{
    mEditorApp = iEditorApp;
}


void
MyCanvas::Build()
{
    mEntitySelection.reserve( 64 );
    mSelectionShape.setFillColor( sf::Color( 20, 20, 200, 100 ) );
    mSelectionShape.setOutlineColor( sf::Color( 0, 0, 50, 200 ) );
}


void
MyCanvas::OnInit()
{
}

void
MyCanvas::OnUpdate()
{
    // We don't want the world to update actually in the editor
    //mEditorApp->Update( 0 );
}


void
MyCanvas::resizeEvent( QResizeEvent * iEvent )
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
MyCanvas::paintEvent( QPaintEvent* )
{
    mRenderWindow->clear( sf::Color( 200, 200, 200 ) );


    DrawSelections();
    mEditorApp->Draw( mRenderWindow );

    if( mState == kSelecting )
        mRenderWindow->draw( mSelectionShape );


    mRenderWindow->display();
}


void
MyCanvas::DrawSelections() const
{
    sf::RectangleShape entitySelectionBox;
    entitySelectionBox.setFillColor( sf::Color( 200, 100, 100 ) );
    entitySelectionBox.setOutlineColor( sf::Color( 255, 50, 100 ) );

    float expansionSize = 2.0;

    for( auto ent : mEntitySelection )
    {
        auto position = dynamic_cast< ::nECS::cPosition* >( ent->GetComponentByName( "position" ) );
        sf::Vector2f entiPos = position->AsVector2F() - sf::Vector2f( expansionSize, expansionSize );
        sf::Vector2f entiSize( 1, 1 );
        auto size = dynamic_cast< ::nECS::cSize* >( ent->GetComponentByName( "size" ) );
        if( size )
            entiSize = size->AsVector2F();

        entiSize += sf::Vector2f( 2 * expansionSize, 2 * expansionSize );
        entitySelectionBox.setPosition( entiPos );
        entitySelectionBox.setSize( entiSize );

        mRenderWindow->draw( entitySelectionBox );
    }
}


//===========================================================================================================
//=========================================================================================== Event Overrides
//===========================================================================================================


void
MyCanvas::mousePressEvent( QMouseEvent * iEvent )
{
    if( iEvent->modifiers() & Qt::AltModifier )
        mState = kPanningCanvas;
    else
        mState = kSelecting;

    mOriginPosition = sf::Vector2i( iEvent->x(), iEvent->y() );
    tSuperClass::mousePressEvent( iEvent );
}


void
MyCanvas::mouseMoveEvent( QMouseEvent * iEvent )
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

    tSuperClass::mouseMoveEvent( iEvent );
}


void
MyCanvas::mouseReleaseEvent( QMouseEvent* iEvent )
{
    if( mState == kSelecting )
    {
        std::vector< ::nECS::cEntity* > entitiesInEMap;

        if( !(iEvent->modifiers() & Qt::ControlModifier) && !( iEvent->modifiers() & Qt::ShiftModifier ) )
            mEntitySelection.clear();

        ::nECS::cGlobalEntityMap::Instance()->mEntityGrid->GetEntitiesInBoundingBox( &entitiesInEMap, mSelectionBox );

        for( auto ent : entitiesInEMap )
        {
            auto position = dynamic_cast< ::nECS::cPosition* >( ent->GetComponentByName( "position" ) );
            sf::Vector2f entiPos = position->AsVector2F();
            sf::Vector2f entiSize( 1, 1 );
            auto size = dynamic_cast< ::nECS::cSize* >( ent->GetComponentByName( "size" ) );
            if( size )
                entiSize = size->AsVector2F();

            if( mSelectionBox.contains( entiPos ) && mSelectionBox.contains( entiPos + entiSize ) )
            {
                printf( "Selected : %s\n", ent->ID().c_str() );
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
MyCanvas::mouseDoubleClickEvent( QMouseEvent * iEvent )
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
MyCanvas::CurrentPrototypeChanged( const QModelIndex& iIndex )
{
    mCurrentPrototypeEntitySelected = iIndex;
}

