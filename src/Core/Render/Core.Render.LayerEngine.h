#pragma once


#include <SFML/Graphics.hpp>
#include <tinyxml2.h>


#include <functional>
#include <unordered_map>


namespace nECS { class cEntity; }
namespace nShaders { class cShader2D; }


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
    void  AddLayer( const sf::Vector2f& iViewSize, float iDistance );
    void  AddLayerAtIndex( const sf::Vector2f& iViewSize, float iDistance, int iIndex );
    void  SetLayersView( const sf::View& iLayerView );
    void  ApplyZoomToLayers( float iZoom );
    void  LayerDistanceAtIndex( float iDistance, int iLayerIndex );
    void  AddShaderToLayer( ::nShaders::cShader2D* iShader, int iLayerIndex );

	void  LayersEnumerator( std::function< void( ::nRender::cLayer* ) > iFunction );

    // EDITOR
    int      LayerCount() const;
    cLayer*  LayerAtIndex( int iLayerIndex );

public:
    // Entity
    void AddEntityInLayer( ::nECS::cEntity* iEntity, int iLayerIndex );

public:
    // Input/Output
    virtual  void SaveXML( tinyxml2::XMLElement* iNode, tinyxml2::XMLDocument* iDocument );
    virtual  void LoadXML( tinyxml2::XMLElement* iNode );

protected:
    std::list< cLayer* >  mLayers;
};


} // namespace nECS

