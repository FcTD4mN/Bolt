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
    void  Draw( sf::RenderTarget* iRenderTarget );

public:
    // Layer
    void  AddLayer();
    void  AddLayerAtIndex( int iIndex );
    void  SetLayersCenter( const sf::Vector2f& iLayerCenter );
    void  LayerDistanceAtIndex( float iDistance, int iLayerIndex );
    void  AddShaderToLayer( sf::Shader* iShader, int iLayerIndex );

public:
    // Entity
    void AddEntityInLayer( ::nECS::cEntity* iEntity, int iLayerIndex );

protected:
    std::list< cLayer >  mLayers;
};


} // namespace nECS

