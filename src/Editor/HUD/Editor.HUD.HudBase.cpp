#include "Editor.HUD.HudBase.h"

#include "Core.ECS.Core.Entity.h"

#include "Core.ECS.Component.Position.h"

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
cHudBase::GetXPosition() const
{
    auto position = dynamic_cast< ::nECS::cPosition* >( mEntity->GetComponentByName( "position" ) );
    return  position->X();
}


float
cHudBase::GetYPosition() const
{
    auto position = dynamic_cast< ::nECS::cPosition* >( mEntity->GetComponentByName( "position" ) );
    return  position->Y();
}


sf::Vector2f
cHudBase::GetPosition() const
{
    auto position = dynamic_cast< ::nECS::cPosition* >( mEntity->GetComponentByName( "position" ) );
    return  position->AsVector2F();
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
