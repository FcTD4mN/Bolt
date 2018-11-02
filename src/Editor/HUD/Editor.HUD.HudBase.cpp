#include "Editor.HUD.HudBase.h"

#include "Core.ECS.Core.Entity.h"
#include "Core.ECS.Component.Transformation.h"

#include "Core.Render.Layer.h"

namespace  nQt {
namespace  nHUD {


cHudBase::~cHudBase()
{
}


cHudBase::cHudBase( ::nCore::nECS::nCore::cEntity * iEntity ) :
    mEntity( iEntity ),
    mIsHUDValid( false )
{
    auto transformation = dynamic_cast< ::nCore::nECS::nComponent::cTransformation* >( mEntity->GetComponentByName( "transformation" ) );

    if( !transformation )
        return;

    mIsHUDValid = true;
}


float
cHudBase::GetXPosition()
{
	return  GetPosition().x;
}


float
cHudBase::GetYPosition()
{
    return  GetPosition().y;
}


sf::Vector2f
cHudBase::GetPosition()
{
    auto transformation = dynamic_cast< ::nCore::nECS::nComponent::cTransformation* >( mEntity->GetComponentByName( "transformation" ) );
	if( !transformation )
	{
		mIsHUDValid = false;
		return sf::Vector2f( 0.0F, 0.0F );
	}

	auto	layer	= mEntity->Layer();
    return  layer->MapVectToLayer( transformation->PositionAsVector2F() );
}


::nCore::nECS::nCore::cEntity *
cHudBase::Entity()
{
    return  mEntity;
}


void
cHudBase::UpdateHandlesPositions()
{
    // nothing
}


bool
cHudBase::ContainsPoint( float iX, float iY ) const
{
    return  ContainsPoint( sf::Vector2f( iX, iY ) );
}


bool
cHudBase::ContainsPoint( const sf::Vector2f & iPoint ) const
{
    return false;
}


void
cHudBase::mousePressEvent( QMouseEvent *iEvent, const sf::RenderWindow* iRenderWindow )
{
    // Nothing to do here
}


void
cHudBase::mouseMoveEvent( QMouseEvent *iEvent, const sf::RenderWindow* iRenderWindow )
{
    // Nothing to do here
}


void
cHudBase::mouseReleaseEvent( QMouseEvent *iEvent, const sf::RenderWindow* iRenderWindow )
{
    // Nothing to do here
}



} // nHUD
} // nQt
