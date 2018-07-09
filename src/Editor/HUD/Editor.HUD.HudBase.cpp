#include "Editor.HUD.HudBase.h"

#include "Core.ECS.Core.Entity.h"
#include "Core.ECS.Component.Position.h"

#include "Core.Render.Layer.h"

namespace  nQt {
namespace  nHUD {


cHudBase::~cHudBase()
{
}


cHudBase::cHudBase( ::nECS::cEntity * iEntity ) :
    mEntity( iEntity ),
    mIsHUDValid( false )
{
    auto position = dynamic_cast< ::nECS::cPosition* >( mEntity->GetComponentByName( "position" ) );

    if( !position )
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
    auto position = dynamic_cast< ::nECS::cPosition* >( mEntity->GetComponentByName( "position" ) );
	if( !position )
	{
		mIsHUDValid = false;
		return sf::Vector2f( 0.0F, 0.0F );
	}

	auto	layer	= mEntity->Layer();
    return  layer->MapVectToLayer( position->AsVector2F() );
}


::nECS::cEntity *
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
