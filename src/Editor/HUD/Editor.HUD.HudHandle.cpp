#include "Editor.HUD.HudHandle.h"

#include "Editor.HUD.HudBase.h"


namespace  nQt {
namespace  nHUD {


cHudHandle::~cHudHandle()
{
}


cHudHandle::cHudHandle( cHudBase* iParent, float iX, float iY, float iW, float iH ) :
    mParent( iParent ),
    mHandlePosition( iX, iY ),
    mHandleSize( iW, iH )
{
    mRectangle.setPosition( mParent->GetPosition() + mHandlePosition );
    mRectangle.setSize( mHandleSize );
    mRectangle.setFillColor( sf::Color( 50, 50, 200, 180 ) );
    mRectangle.setOutlineColor( sf::Color( 100, 100, 200 ) );
}


void
cHudHandle::Position( const sf::Vector2f & iPosition )
{
    mHandlePosition = iPosition;
}


void
cHudHandle::Draw( sf::RenderTarget* iRenderTarget )
{
    mRectangle.setPosition( mParent->GetPosition() + mHandlePosition );

    iRenderTarget->draw( mRectangle );
}


bool
cHudHandle::ContainsPoint( const sf::Vector2f & iPoint ) const
{
    auto position = mParent->GetPosition() + mHandlePosition;

    sf::FloatRect rect( position, mHandleSize ); // Make it bigger so it's clickable easily

    return  rect.contains( iPoint );
}


void
cHudHandle::mousePressEvent( QMouseEvent *iEvent, const sf::RenderWindow* iRenderWindow )
{
}


void
cHudHandle::mouseMoveEvent( QMouseEvent *iEvent, const sf::RenderWindow* iRenderWindow )
{
}


void
cHudHandle::mouseReleaseEvent( QMouseEvent *iEvent, const sf::RenderWindow* iRenderWindow )
{
}



} // nHUD
} // nQt




