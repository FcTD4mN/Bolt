#include "Editor.HUD.HudTransformation.h"

#include "Core.ECS.Core.Entity.h"
#include "Core.ECS.Core.Component.h"

#include "Core.ECS.Component.Position.h"
#include "Core.ECS.Component.Size.h"
#include "Core.ECS.Component.SpriteAnimated.h"

namespace  nQt {
namespace  nHUD {


cHudTransformation::~cHudTransformation()
{
    for( auto handle : mScaleHandles )
        delete  handle;
}


cHudTransformation::cHudTransformation( ::nECS::cEntity * iEntity ) :
    tSuperClass( iEntity ),
    mCurrentHandle( 0 ),
    mCurrentHandleIndex( -1 )
{
    mScaleHandles.reserve( 8 );
    BuildHUD();
}


void
cHudTransformation::BuildHUD()
{
    auto position = dynamic_cast< ::nECS::cPosition* >( mEntity->GetComponentByName( "position" ) );

    if( !position )
        return;

    mIsHUDValid = true;

    float handleSize = 10.0F;
    sf::Vector2f size = GetSizeFromEntity();


    // From top left, going clockwise, we create each handles
    mScaleHandles.push_back( new cHudHandle( this, -handleSize/2, -handleSize/2, handleSize, handleSize ) );
    mScaleHandles.push_back( new cHudHandle( this, size.x / 2 - handleSize/2, -handleSize/2, handleSize, handleSize ) );
    mScaleHandles.push_back( new cHudHandle( this, size.x - handleSize/2, -handleSize/2, handleSize, handleSize ) );

    mScaleHandles.push_back( new cHudHandle( this, size.x - handleSize/2, size.y / 2 - handleSize/2, handleSize, handleSize ) );

    mScaleHandles.push_back( new cHudHandle( this, size.x - handleSize/2, size.y - handleSize/2, handleSize, handleSize ) );
    mScaleHandles.push_back( new cHudHandle( this, size.x/2 - handleSize/2, size.y - handleSize/2, handleSize, handleSize ) );
    mScaleHandles.push_back( new cHudHandle( this, -handleSize/2, size.y - handleSize/2, handleSize, handleSize ) );

    mScaleHandles.push_back( new cHudHandle( this, - handleSize/2, size.y / 2 - handleSize/2, handleSize, handleSize ) );
}


void
cHudTransformation::UpdateHandlesPositions()
{
    auto position = dynamic_cast< ::nECS::cPosition* >( mEntity->GetComponentByName( "position" ) );

    if( !position )
        return;

    float handleSize = 10.0F;

    sf::Vector2f size = GetSizeFromEntity();

    mScaleHandles[ 1 ]->Position( sf::Vector2f( size.x / 2 - handleSize / 2, -handleSize / 2 ) );
    mScaleHandles[ 2 ]->Position( sf::Vector2f( size.x - handleSize / 2, -handleSize / 2 ) );
    mScaleHandles[ 3 ]->Position( sf::Vector2f( size.x - handleSize / 2, size.y / 2 - handleSize / 2 ) );
    mScaleHandles[ 4 ]->Position( sf::Vector2f( size.x - handleSize / 2, size.y - handleSize / 2 ) );
    mScaleHandles[ 5 ]->Position( sf::Vector2f( size.x / 2 - handleSize / 2, size.y - handleSize / 2 ) );
    mScaleHandles[ 6 ]->Position( sf::Vector2f( -handleSize / 2, size.y - handleSize / 2 ) );
    mScaleHandles[ 7 ]->Position( sf::Vector2f( -handleSize / 2, size.y / 2 - handleSize / 2 ) );
}


void
cHudTransformation::Draw( sf::RenderTarget* iRenderTarget )
{
    if( !mIsHUDValid )
        return;

    auto position           = dynamic_cast< ::nECS::cPosition* >( mEntity->GetComponentByName( "position" ) );

    sf::RectangleShape outline;
    outline.setPosition( position->AsVector2F() );
    outline.setSize( GetSizeFromEntity() );
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
    for( auto handle : mScaleHandles )
    {
        if( handle->ContainsPoint( iPoint ) )
            return  true;
    }

    auto position   = dynamic_cast< ::nECS::cPosition* >( mEntity->GetComponentByName( "position" ) );

    sf::FloatRect rect( position->AsVector2F(), GetSizeFromEntity() );

    return  rect.contains( iPoint );
}


// ==================================================================
// =========================================================== Events
// ==================================================================


void
cHudTransformation::mousePressEvent( QMouseEvent *iEvent, const sf::RenderWindow* iRenderWindow )
{
    for( int i = 0; i < mScaleHandles.size(); ++i )
    {
        sf::Vector2f mouseCoordMapped( iRenderWindow->mapPixelToCoords( sf::Vector2i( iEvent->x(), iEvent->y() ) ) );
        mOriginPosition = iRenderWindow->mapPixelToCoords( sf::Vector2i( iEvent->x(), iEvent->y() ) );

        if( mScaleHandles[ i ]->ContainsPoint( mouseCoordMapped ) )
        {
            mCurrentHandle = mScaleHandles[ i ];
            mCurrentHandle->mousePressEvent( iEvent, iRenderWindow );
            mCurrentHandleIndex = i;
            break;
        }
    }

    emit StartEditing();
}


void
cHudTransformation::mouseMoveEvent( QMouseEvent *iEvent, const sf::RenderWindow* iRenderWindow )
{
    sf::Vector2f currentPos = iRenderWindow->mapPixelToCoords( sf::Vector2i( iEvent->x(), iEvent->y() ) );
    sf::Vector2f offset = mOriginPosition - currentPos;

    if( mCurrentHandle )
    {
        mCurrentHandle->mouseMoveEvent( iEvent, iRenderWindow );

        if( mCurrentHandleIndex == 0 )
        {
            emit  MovedEntity( -offset.x, -offset.y );
            emit  ScaledEntity( offset.x, offset.y );
        }
        else if( mCurrentHandleIndex == 1 )
        {
            emit  MovedEntity( 0, -offset.y );
            emit  ScaledEntity( 0, offset.y );
        }
        else if( mCurrentHandleIndex == 2 )
        {
            emit  MovedEntity( 0, -offset.y );
            emit  ScaledEntity( -offset.x, offset.y );
        }
        else if( mCurrentHandleIndex == 3 )
        {
            emit  ScaledEntity( -offset.x, 0 );
        }
        else if( mCurrentHandleIndex == 4 )
        {
            emit  ScaledEntity( -offset.x, -offset.y );
        }
        else if( mCurrentHandleIndex == 5 )
        {
            emit  ScaledEntity( 0, -offset.y );
        }
        else if( mCurrentHandleIndex == 6 )
        {
            emit  MovedEntity( -offset.x, 0 );
            emit  ScaledEntity( offset.x, -offset.y );
        }
        else if( mCurrentHandleIndex == 7 )
        {
            emit  MovedEntity( -offset.x, 0 );
            emit  ScaledEntity( offset.x, 0 );
        }
    }
    else
    {
        emit  MovedEntity( -offset.x, -offset.y );
    }

    // We don't want micro deltas, but we want the delta from origin
    //mOriginPosition = currentPos;
}


void
cHudTransformation::mouseReleaseEvent( QMouseEvent *iEvent, const sf::RenderWindow* iRenderWindow )
{
    if( mCurrentHandle )
        mCurrentHandle->mouseReleaseEvent( iEvent, iRenderWindow );

    emit FinishedEditing();

    mCurrentHandle = 0;
}


sf::Vector2f
cHudTransformation::GetSizeFromEntity() const
{
    auto size = dynamic_cast< ::nECS::cSize* >( mEntity->GetComponentByName( "size" ) );
    auto spriteanimated = dynamic_cast< ::nECS::cSpriteAnimated* >( mEntity->GetComponentByName( "spriteanimated" ) );

    sf::Vector2f sizeOfTheHud( 1, 1 );
    if( size )
    {
        sizeOfTheHud = size->AsVector2F();
    }
    else if( spriteanimated )
    {
        sizeOfTheHud.x = spriteanimated->mCurrentSpriteRect.width;
        sizeOfTheHud.y = spriteanimated->mCurrentSpriteRect.height;
    }

    return  sizeOfTheHud;
}


} // nHUD
} // nQt
