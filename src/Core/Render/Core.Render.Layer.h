#pragma once


#include <SFML/Graphics.hpp>
#include <tinyxml2.h>


#include <unordered_map>


namespace nECS { class cEntity; }

namespace nRender {

class cLayer
{
public:
    // Contruction/Destruction
    ~cLayer();
    cLayer();

public:
    // Draw related methods
    void  Draw();
    void  Clear();
    void  Display();

public:
    // Entity
    void AddEntity( ::nECS::cEntity* iEntity );

public:
    // Access
    size_t EntityCount() const;
    const sf::Sprite& Sprite() const;

private:
    // Private
    void  RemoveEntity( ::nECS::cEntity* iEntity );

protected:
    std::list< ::nECS::cEntity* >   mEntities;
    sf::RenderTexture*              mRenderTexture;
    sf::Sprite                      mRenderTextureSprite;
};


} // namespace nECS

