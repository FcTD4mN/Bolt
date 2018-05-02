#pragma once

#include "Editor.HUD.HudBase.h"

#include "Editor.HUD.HudHandle.h"

namespace  nECS { class cEntity; }

namespace  nQt {
namespace  nHUD {

class  cHudTransformation :
    public  cHudBase
{
public:
    typedef cHudBase tSuperClass;

public:
    ~cHudTransformation();
    cHudTransformation( ::nECS::cEntity* iEntity );

public:
    void BuildHUD();

public:
    virtual  void Draw( sf::RenderTarget* iRenderTarget ) override;
    virtual  bool ContainsPoint( const  sf::Vector2f& iPoint ) const  override;

public:
    virtual void mousePressEvent( QMouseEvent *iEvent, const sf::RenderWindow* iRenderWindow ) override;
    virtual void mouseMoveEvent( QMouseEvent *iEvent, const sf::RenderWindow* iRenderWindow ) override;
    virtual void mouseReleaseEvent( QMouseEvent *iEvent, const sf::RenderWindow* iRenderWindow ) override;

private:
    std::vector< cHudHandle* > mScaleHandles;
};

} //nQt
} //nModels
