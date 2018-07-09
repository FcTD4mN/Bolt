#include "Core.Render.LayerEngine.h"


#include "Core.Application.GlobalAccess.h"

#include "Core.Render.Layer.h"


namespace nRender
{


cLayerEngine::~cLayerEngine()
{
	for( auto layer : mLayers )
		delete  layer;

	mLayers.clear();
}


cLayerEngine::cLayerEngine()
{
}


void
cLayerEngine::Draw( sf::RenderTarget* iRenderTarget )
{
    for( auto layer : mLayers )
        layer->Draw( iRenderTarget );
}


void
cLayerEngine::AddLayer( const sf::Vector2f& iViewSize, float iDistance )
{
    cLayer* newLayer = new cLayer( iViewSize );
    newLayer->Name( "Layer " + std::to_string( mLayers.size() ) );
	newLayer->ZLayer( iDistance );
    mLayers.push_back( newLayer );
}


void
cLayerEngine::AddLayer()
{
	auto theMainWindow = ::nGlobal::cGlobalProperties::Instance()->GetTheMainWindow();
	if( theMainWindow )
	{
		sf::Vector2u windowSize = ::nGlobal::cGlobalProperties::Instance()->GetTheMainWindow()->getSize();
		AddLayer( sf::Vector2f( float(windowSize.x), float(windowSize.y) ), 1.0F );
	}
	else
	{
		AddLayer( ::nGlobal::cGlobalProperties::Instance()->GetProjectSize(), 1.0F );
	}
}


void
cLayerEngine::AddLayerAtIndex( const sf::Vector2f& iViewSize, float iDistance, int iIndex )
{
    auto it = mLayers.begin();
    for( int i = 0; i < iIndex; ++i )
        ++it;

	cLayer* newLayer = new cLayer( iViewSize );
	newLayer->Name( "Layer " + std::to_string( mLayers.size() ) );
	newLayer->ZLayer( iDistance );

    mLayers.insert( it, newLayer );
}


void
cLayerEngine::AddLayerAtIndex( int iIndex )
{
	auto theMainWindow = ::nGlobal::cGlobalProperties::Instance()->GetTheMainWindow();
	if( theMainWindow )
	{
		sf::Vector2u windowSize = ::nGlobal::cGlobalProperties::Instance()->GetTheMainWindow()->getSize();
		AddLayerAtIndex( sf::Vector2f( float(windowSize.x), float(windowSize.y) ), 1.0F, iIndex );
	}
	else
	{
		AddLayerAtIndex( ::nGlobal::cGlobalProperties::Instance()->GetProjectSize(), 1.0F, iIndex );
	}
}


void
cLayerEngine::SetLayersView( const sf::View& iLayerView )
{
    for( auto layer : mLayers )
        layer->SetView( iLayerView );
}


void
cLayerEngine::ApplyZoomToLayers( float iZoom )
{
	for( auto layer : mLayers )
		layer->ApplyZoom( iZoom );
}


void
cLayerEngine::LayerDistanceAtIndex( float iDistance, int iLayerIndex )
{
    auto it = mLayers.begin();
    for( int i = 0; i < iLayerIndex; ++i )
        ++it;

    ( *it )->ZLayer( iDistance );
}


void
cLayerEngine::AddShaderToLayer( ::nShaders::cShader2D* iShader, int iLayerIndex )
{
    auto it = mLayers.begin();
    for( int i = 0; i < iLayerIndex; ++i )
        ++it;

    ( *it )->AddShader( iShader );
}


void
cLayerEngine::LayersEnumerator( std::function<void( ::nRender::cLayer* )> iFunction )
{
	for( auto layer : mLayers )
		iFunction( layer );
}


int
cLayerEngine::LayerCount() const
{
    return  int(mLayers.size());
}


cLayer*
cLayerEngine::LayerAtIndex( int iLayerIndex )
{
    if( iLayerIndex < 0 || iLayerIndex > mLayers.size() )
        return  mLayers.back(); // Completely wrong, we really need to change layers to pointer in the list !!

    auto it = mLayers.begin();
    for( int i = 0; i < iLayerIndex; ++i )
        ++it;

    return  *it;
}


void
cLayerEngine::AddEntityInLayer( ::nECS::cEntity * iEntity, int iLayerIndex )
{
    auto it = mLayers.begin();
    for( int i = 0; i < iLayerIndex; ++i )
        ++it;

    ( *it )->AddEntity( iEntity );
}


void
cLayerEngine::SaveXML( tinyxml2::XMLElement * iNode, tinyxml2::XMLDocument * iDocument )
{
    for( auto layer : mLayers )
    {
        // LAYERS
        tinyxml2::XMLElement* layerNode = iDocument->NewElement( "layer" );
        layer->SaveXML( layerNode, iDocument );
        iNode->LinkEndChild( layerNode );
    }
}


void
cLayerEngine::LoadXML( tinyxml2::XMLElement * iNode )
{
    // Nothing because already done in an unsymmetrical manner by the world
}


}

