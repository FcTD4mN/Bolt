#include "Editor.HUD.HudTransformation.h"

#include "Core.ECS.Core.Entity.h"
#include "Core.ECS.Core.Component.h"

#include "Core.ECS.Component.Transformation.h"
#include "Core.ECS.Component.Animations.h"

#include "Core.Render.Layer.h"

namespace  nQt {
namespace  nHUD {


cHudTransformation::~cHudTransformation()
{
    for( auto handle : mScaleHandles )
        delete  handle;
}


cHudTransformation::cHudTransformation( ::nCore::nECS::nCore::cEntity * iEntity ) :
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
    auto transformation = dynamic_cast< ::nCore::nECS::nComponent::cTransformation* >( mEntity->GetComponentByName( "transformation" ) );

    if( !transformation )
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

	sf::Vector2f positionMapped = GetPosition();

	sf::RectangleShape outline;
    outline.setPosition( positionMapped );
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
	if( !mIsHUDValid )
		return  false;

    for( auto handle : mScaleHandles )
    {
        if( handle->ContainsPoint( iPoint ) )
            return  true;
    }

    auto transformation     = dynamic_cast< ::nCore::nECS::nComponent::cTransformation* >( mEntity->GetComponentByName( "transformation" ) );
	auto layer		        = mEntity->Layer();

    sf::FloatRect rect( layer->MapVectToLayer( transformation->PositionAsVector2F() ), GetSizeFromEntity() );

    return  rect.contains( iPoint );
}


// ==================================================================
// =========================================================== Events
// ==================================================================


void
cHudTransformation::mousePressEvent( QMouseEvent *iEvent, const sf::RenderWindow* iRenderWindow )
{
	if( !mIsHUDValid )
		return;

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
	if( !mIsHUDValid )
		return;

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
    // mOriginPosition = currentPos;
}


void
cHudTransformation::mouseReleaseEvent( QMouseEvent *iEvent, const sf::RenderWindow* iRenderWindow )
{
	if( !mIsHUDValid )
		return;

    if( mCurrentHandle )
        mCurrentHandle->mouseReleaseEvent( iEvent, iRenderWindow );

    emit FinishedEditing();

    mCurrentHandle = 0;
}


sf::Vector2f
cHudTransformation::GetSizeFromEntity() const
{
    auto transformation = mEntity->GetComponentByNameAs< ::nCore::nECS::nComponent::cTransformation* >( "transformation" );
    auto animations     = mEntity->GetComponentByNameAs< ::nCore::nECS::nComponent::cAnimations* >( "animations" );

    sf::Vector2f sizeOfTheHud( 1, 1 );
    if( transformation )
    {
        sizeOfTheHud = transformation->SizeAsVector2F();
    }
    else if( animations )
    {
        sizeOfTheHud.x = animations->CurrentAnimationSpriteWidth();
        sizeOfTheHud.y = animations->CurrentAnimationSpriteHeight();
    }

    return  sizeOfTheHud;
}


} // nHUD
} // nQt
