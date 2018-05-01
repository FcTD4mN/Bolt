#pragma once

#include <SFML/Graphics.hpp>

namespace  nECS { class cEntity; }

namespace  nQt {
namespace  nHUD {

class  cHudBase
{
public:
    ~cHudBase();
    cHudBase( ::nECS::cEntity* iEntity );

public:
    void Draw( sf::RenderTarget* iRenderTarget );

private:
    ::nECS::cEntity* mEntity;
};

} //nQt
} //nModels
