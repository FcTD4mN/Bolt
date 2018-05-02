#include "Editor.HUD.HudTransformation.h"

#include "Core.ECS.Core.Entity.h"
#include "Core.ECS.Core.Component.h"

#include "Core.ECS.Component.Position.h"
#include "Core.ECS.Component.Size.h"

namespace  nQt {
namespace  nHUD {


cHudTransformation::~cHudTransformation()
{
    for( auto handle : mScaleHandles )
        delete  handle;
}


cHudTransformation::cHudTransformation( ::nECS::cEntity * iEntity ) :
    tSuperClass( iEntity )
{
    mScaleHandles.reserve( 8 );
    BuildHUD();
}


void
cHudTransformation::BuildHUD()
{
    auto position = dynamic_cast< ::nECS::cPosition* >( mEntity->GetComponentByName( "position" ) );
    auto size = dynamic_cast< ::nECS::cSize* >( mEntity->GetComponentByName( "size" ) );

    if( !position || !size )
        return;

    mIsHUDValid = true;

    float handleSize = 5.0F;

    // From top left, going clockwise, we create each handles
    mScaleHandles.push_back( new cHudHandle( this, -handleSize/2, -handleSize/2, handleSize, handleSize ) );
    mScaleHandles.push_back( new cHudHandle( this, size->W() / 2 - handleSize/2, -handleSize/2, handleSize, handleSize ) );
    mScaleHandles.push_back( new cHudHandle( this, size->W() - handleSize/2, -handleSize/2, handleSize, handleSize ) );

    mScaleHandles.push_back( new cHudHandle( this, size->W() - handleSize/2, size->H() / 2 - handleSize/2, handleSize, handleSize ) );

    mScaleHandles.push_back( new cHudHandle( this, size->W() - handleSize/2, size->H() - handleSize/2, handleSize, handleSize ) );
    mScaleHandles.push_back( new cHudHandle( this, size->W()/2 - handleSize/2, size->H() - handleSize/2, handleSize, handleSize ) );
    mScaleHandles.push_back( new cHudHandle( this, -handleSize/2, size->H() - handleSize/2, handleSize, handleSize ) );

    mScaleHandles.push_back( new cHudHandle( this, - handleSize/2, size->H() / 2 - handleSize/2, handleSize, handleSize ) );
}


void
cHudTransformation::Draw( sf::RenderTarget* iRenderTarget )
{
    if( !mIsHUDValid )
        return;

    auto position   = dynamic_cast< ::nECS::cPosition* >( mEntity->GetComponentByName( "position" ) );
    auto size       = dynamic_cast< ::nECS::cSize* >( mEntity->GetComponentByName( "size" ) );

    sf::RectangleShape outline;
    outline.setPosition( position->AsVector2F() );
    outline.setSize( size->AsVector2F() );
    outline.setOutlineThickness( 2 );
    outline.setFillColor( sf::Color( 0, 0, 0, 0 ) );
    outline.setOutlineColor( sf::Color( 20, 20, 255 ) );

    iRenderTarget->draw( outline );

    for( auto handle : mScaleHandles )
        handle->Draw( iRenderTarget );
}


bool
cHudTransformation::ContainsPoint( const  sf::Vector2f& iPoint ) const
{
    auto position   = dynamic_cast< ::nECS::cPosition* >( mEntity->GetComponentByName( "position" ) );
    auto size       = dynamic_cast< ::nECS::cSize* >( mEntity->GetComponentByName( "size" ) );

    sf::FloatRect rect( position->AsVector2F(), size->AsVector2F() );

    return  rect.contains( iPoint );
}


void
cHudTransformation::mousePressEvent( QMouseEvent *iEvent, const sf::RenderWindow* iRenderWindow )
{
    for( auto handle : mScaleHandles )
    {
        sf::Vector2f mouseCoordMapped( iRenderWindow->mapPixelToCoords( sf::Vector2i( iEvent->x(), iEvent->y() ) ) );
        if( handle->ContainsPoint( mouseCoordMapped ) )
        {
            handle->mousePressEvent( iEvent, iRenderWindow );
            break;
        }
    }
}


void
cHudTransformation::mouseMoveEvent( QMouseEvent *iEvent, const sf::RenderWindow* iRenderWindow )
{
    // Nothing to do here
}


void
cHudTransformation::mouseReleaseEvent( QMouseEvent *iEvent, const sf::RenderWindow* iRenderWindow )
{
    // Nothing to do here
}


} // nHUD
} // nQt
