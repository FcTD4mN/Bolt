#pragma once


#include <SFML/Graphics.hpp>
#include <tinyxml2.h>


#include <functional>
#include <unordered_map>
#include <list>

namespace nCore  { namespace nECS { namespace nCore { class cEntity; } } }
namespace nCore { namespace nShader { class cShader2D; } }
namespace nCore { namespace nRender { class cLayer; } }


namespace nCore {
namespace nRender {


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
    void  AddLayer();
    void  AddLayerAtIndex( const sf::Vector2f& iViewSize, float iDistance, int iIndex );
    void  AddLayerAtIndex( int iIndex );
    void  AddLayerAtIndex( cLayer* iLayer, int iIndex );
    void  DeleteLayerAtIndex( int iIndex );
    void  MoveLayerToIndex( cLayer* iLayer, int iIndex );
    void  LayersView( const sf::View& iLayerView );
    void  ApplyZoomToLayers( float iZoom );
    void  LayerDistanceAtIndex( float iDistance, int iLayerIndex );
    void  AddShaderToLayer( ::nCore::nShader::cShader2D* iShader, int iLayerIndex );
    int   LayerIndex( const cLayer* iLayer ) const;

    void  LayersEnumerator( std::function< void( ::nCore::nRender::cLayer* ) > iFunction );

    // EDITOR
    int      LayerCount() const;
    cLayer*  LayerAtIndex( int iLayerIndex );

public:
    // Entity
    int AddEntityInLayer( ::nCore::nECS::nCore::cEntity* iEntity, int iLayerIndex );

public:
    // Input/Output
    virtual  void SaveXML( tinyxml2::XMLElement* iNode, tinyxml2::XMLDocument* iDocument );
    virtual  void LoadXML( tinyxml2::XMLElement* iNode );

protected:
    std::list< cLayer* >  mLayers;
};


} // namespace nRender
} // namespace nCore

