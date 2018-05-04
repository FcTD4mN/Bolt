#include "Editor.HUD.SnapGrid.h"

namespace  nQt {
namespace  nHUD {


cSnapGrid::~cSnapGrid()
{
}


cSnapGrid::cSnapGrid( int iWidth, int iHeight ) :
    mWidth( iWidth ),
    mHeight( iHeight ),
    mVisible( true )
{
}


void
cSnapGrid::Width( int iWidth )
{
    mWidth = iWidth;
}


void
cSnapGrid::Height( int iHeight )
{
    mHeight = iHeight;
}


void
cSnapGrid::Visible( bool iVisible)
{
    mVisible = iVisible;
}


bool
cSnapGrid::Visible()
{
    return  mVisible;
}


void
cSnapGrid::Draw( sf::RenderTarget * iRenderTarget )
{
    if( !mVisible )
        return;

    sf::VertexArray line( sf::LineStrip, 2 );

    // The whole idea is to draw a grid at 0.0 that is perfectly correct, and then shift it at the right place to overlay with the current screen position
    // So we need a modulo thing, that will do a final shift to match grid coordinates at current location
    auto view = iRenderTarget->getView();
    sf::Vector2f viewPosition( view.getCenter().x - view.getSize().x/2, view.getCenter().y - view.getSize().y / 2 );

    sf::Vector2f moduloVector( float((int(viewPosition.x) % mWidth) + mWidth), float((int(viewPosition.y) % mHeight) + mHeight) );

    for( int i = 0; i < (int( view.getSize().x) / mWidth) + 2; ++i )
    {
        line.clear();
                                                        // The first shift here is to go to the current location, then modulo fine tunes it
        line.append( sf::Vector2f( float(i * mWidth), 0.0F ) + viewPosition - moduloVector );
        line.append( sf::Vector2f( float(i * mWidth), float( view.getSize().y + 2*mHeight) ) + viewPosition - moduloVector );
        line[ 0 ].color = sf::Color( 0, 0, 0, 200 );
        line[ 1 ].color = sf::Color( 0, 0, 0, 200 );

        iRenderTarget->draw( line );
    }

    for( int i = 0; i < (int( view.getSize().y ) / mHeight) + 2; ++i )
    {
        line.clear();

        line.append( sf::Vector2f( 0.0F, float(i * mHeight) ) + viewPosition - moduloVector );
                                                                        // The first shift here is to go to the current location, then modulo fine tunes it
        line.append( sf::Vector2f( float( view.getSize().x + 2*mWidth), float(i * mHeight) ) + viewPosition - moduloVector );

        line[ 0 ].color = sf::Color( 0, 0, 0, 200 );
        line[ 1 ].color = sf::Color( 0, 0, 0, 200 );

        iRenderTarget->draw( line );
    }
}

} // nHUD
} // nQt

