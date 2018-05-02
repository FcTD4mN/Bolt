#pragma once

#include <SFML/Graphics.hpp>

#include <QtWidgets>

namespace  nECS { class cEntity; }

namespace  nQt {
namespace  nHUD {

class  cHudBase :
    public QObject
{
    Q_OBJECT

public:
    ~cHudBase();
    cHudBase( ::nECS::cEntity* iEntity );

public:
    virtual  void Draw( sf::RenderTarget* iRenderTarget ) = 0;

public:
    float  GetXPosition() const;
    float  GetYPosition() const;
    sf::Vector2f GetPosition() const;
    ::nECS::cEntity*  Entity();

public:
    virtual  void  UpdateHandlesPositions();

public:
    bool  ContainsPoint( float iX, float iY ) const;
    virtual  bool  ContainsPoint( const  sf::Vector2f& iPoint ) const;

public:
    virtual void mousePressEvent( QMouseEvent *iEvent, const sf::RenderWindow* iRenderWindow );
    virtual void mouseMoveEvent( QMouseEvent *iEvent, const sf::RenderWindow* iRenderWindow );
    virtual void mouseReleaseEvent( QMouseEvent *iEvent, const sf::RenderWindow* iRenderWindow );

signals:
    void MovedEntity( float iDeltaX, float iDeltaY );
    void ScaledEntity( float iDeltaW, float iDeltaH );

protected:
    ::nECS::cEntity* mEntity;
    bool  mIsHUDValid;
};

} //nQt
} //nModels
