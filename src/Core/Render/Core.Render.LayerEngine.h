#pragma once


#include <SFML/Graphics.hpp>
#include <tinyxml2.h>


#include <unordered_map>


namespace nECS { class cEntity; }


namespace nRender {


class cLayer;


class cLayerEngine
{
public:
    // Contruction/Destruction
    ~cLayerEngine();
    cLayerEngine();

public:
    // Update/Draw
    void  ProcessDrawing();
    void  Draw( sf::RenderTarget* iRenderTarget );

public:
    // Layer
    void AddLayer();

public:
    // Entity
    void AddEntityInLayer( ::nECS::cEntity* iEntity, int iLayerIndex );

protected:
    std::list< cLayer >  mLayers;
};


} // namespace nECS

