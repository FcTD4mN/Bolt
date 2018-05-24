#include "Core.Render.LayerEngine.h"

#include "Core.Render.Layer.h"


namespace nRender
{


cLayerEngine::~cLayerEngine()
{
}


cLayerEngine::cLayerEngine()
{
    // One layer by default
    AddLayer();
}


void
cLayerEngine::Draw( sf::RenderTarget * iRenderTarget )
{
    for( auto layer : mLayers )
        layer.Draw( iRenderTarget );
}


void
cLayerEngine::AddLayer()
{
    mLayers.push_back( cLayer() );
}


void
cLayerEngine::AddLayerAtIndex( int iIndex )
{
    auto it = mLayers.begin();
    for( int i = 0; i < iIndex; ++i )
        ++it;

    mLayers.insert( it, cLayer() );
}


void
cLayerEngine::SetLayersCenter( const sf::Vector2f & iLayerCenter )
{
    for( auto& layer : mLayers )
        layer.SetViewCenter( iLayerCenter );
}


void
cLayerEngine::LayerDistanceAtIndex( float iDistance, int iLayerIndex )
{
    auto it = mLayers.begin();
    for( int i = 0; i < iLayerIndex; ++i )
        ++it;

    ( *it ).ZLayer( iDistance );
}


void
cLayerEngine::AddShaderToLayer( sf::Shader* iShader, int iLayerIndex )
{
    auto it = mLayers.begin();
    for( int i = 0; i < iLayerIndex; ++i )
        ++it;

    ( *it ).AddShader( iShader );
}


void
cLayerEngine::AddEntityInLayer( ::nECS::cEntity * iEntity, int iLayerIndex )
{
    auto it = mLayers.begin();
    for( int i = 0; i < iLayerIndex; ++i )
        ++it;

    ( *it ).AddEntity( iEntity );
}


}

