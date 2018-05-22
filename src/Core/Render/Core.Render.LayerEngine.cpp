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
cLayerEngine::ProcessDrawing()
{
    for( auto layer : mLayers )
    {
        layer.Clear();
        layer.Draw();
    }
}


void
cLayerEngine::Draw( sf::RenderTarget * iRenderTarget )
{
    for( auto layer : mLayers )
    {
        layer.Display();
        iRenderTarget->draw( layer.Sprite() );
    }
}


void
cLayerEngine::AddLayer()
{
    mLayers.push_back( cLayer() );
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

