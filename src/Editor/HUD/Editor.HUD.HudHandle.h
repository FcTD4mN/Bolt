#pragma once

#include <SFML/Graphics.hpp>

#include <QtWidgets>

namespace  nQt { namespace  nHUD { class cHudBase; } }

namespace  nQt {
namespace  nHUD {

class  cHudHandle
{
public:
    ~cHudHandle();
    cHudHandle( cHudBase* iParent, float iX, float iY, float iW, float iH );

public:
    void  Position( const sf::Vector2f& iPosition );

public:
    void  Draw( sf::RenderTarget* iRenderTarget );
    bool  ContainsPoint( const  sf::Vector2f& iPoint ) const;

public:
    virtual void mousePressEvent( QMouseEvent *iEvent, const sf::RenderWindow* iRenderWindow );
    virtual void mouseMoveEvent( QMouseEvent *iEvent, const sf::RenderWindow* iRenderWindow );
    virtual void mouseReleaseEvent( QMouseEvent *iEvent, const sf::RenderWindow* iRenderWindow );

protected:
    cHudBase*           mParent;
    sf::RectangleShape  mRectangle;
    sf::Vector2f        mHandlePosition;
    sf::Vector2f        mHandleSize;
};

} //nQt
} //nModels
