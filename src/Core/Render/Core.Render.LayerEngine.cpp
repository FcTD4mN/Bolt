#include "Core.Render.LayerEngine.h"


#include "Core.Application.GlobalAccess.h"

#include "Core.Render.Layer.h"


namespace nCore {
namespace nRender {


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
    {
        if( layer->Visible() )
            layer->Draw( iRenderTarget );
    }
}


void
cLayerEngine::AddLayer( const sf::Vector2f& iViewSize, float iDistance )
{
#ifdef EDITOR
    cLayer* newLayer = new cLayer( this, iViewSize, ::nCore::nRender::cLayer::kPositionSize );
#else
    cLayer* newLayer = new cLayer( this, iViewSize, ::nCore::nRender::cLayer::kPhysics );
#endif

    newLayer->Name( "Layer " + std::to_string( mLayers.size() ) );
    newLayer->ZLayer( iDistance );
    mLayers.push_back( newLayer );
}


void
cLayerEngine::AddLayer()
{
    auto theMainWindow = ::nCore::nApplication::cGlobalAccess::Instance()->TheMainWindow();
    if( theMainWindow )
    {
        sf::Vector2u windowSize = theMainWindow->getSize();
        AddLayer( sf::Vector2f( float(windowSize.x), float(windowSize.y) ), 1.0F );
    }
    else
    {
        AddLayer( ::nCore::nApplication::cGlobalAccess::Instance()->ProjectSize(), 1.0F );
    }
}


void
cLayerEngine::AddLayerAtIndex( const sf::Vector2f& iViewSize, float iDistance, int iIndex )
{
    auto it = mLayers.begin();
    for( int i = 0; i < iIndex; ++i )
        ++it;

#ifdef EDITOR
    cLayer* newLayer = new cLayer( this, iViewSize, ::nCore::nRender::cLayer::kPositionSize );
#else
    cLayer* newLayer = new cLayer( this, iViewSize, ::nCore::nRender::cLayer::kPhysics );
#endif

    newLayer->Name( "Layer " + std::to_string( mLayers.size() ) );
    newLayer->ZLayer( iDistance );

    mLayers.insert( it, newLayer );
}


void
cLayerEngine::AddLayerAtIndex( int iIndex )
{
    auto theMainWindow = ::nCore::nApplication::cGlobalAccess::Instance()->TheMainWindow();
    if( theMainWindow )
    {
        sf::Vector2u windowSize = theMainWindow->getSize();
        AddLayerAtIndex( sf::Vector2f( float(windowSize.x), float(windowSize.y) ), 1.0F, iIndex );
    }
    else
    {
        AddLayerAtIndex( ::nCore::nApplication::cGlobalAccess::Instance()->ProjectSize(), 1.0F, iIndex );
    }
}


void
cLayerEngine::AddLayerAtIndex( cLayer * iLayer, int iIndex )
{
    auto it = mLayers.begin();
    for( int i = 0; i < iIndex; ++i )
        ++it;

    mLayers.insert( it, iLayer );
}


void
cLayerEngine::DeleteLayerAtIndex( int iIndex )
{
    auto it = mLayers.begin();
    for( int i = 0; i < iIndex; ++i )
        ++it;

    delete  *it;
    mLayers.erase( it );
}


void
cLayerEngine::MoveLayerToIndex( cLayer * iLayer, int iIndex )
{
    int layerIndex = 0;
    auto it = mLayers.begin();

    // We get iLayer's original index
    while( it != mLayers.end() )
    {
        if( *it == iLayer )
            break;
        ++it; ++layerIndex;
    }

    // We compute the new index
    int insertionIndex = iIndex;
    if( iIndex > layerIndex ) // Shift by one as iLayer will be removed,
        --insertionIndex;

    // Remove old position
    if( it != mLayers.end() )
        mLayers.erase( it );

    AddLayerAtIndex( iLayer, insertionIndex );
}


void
cLayerEngine::LayersView( const sf::View& iLayerView )
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
cLayerEngine::AddShaderToLayer( ::nCore::nShader::cShader2D* iShader, int iLayerIndex )
{
    auto it = mLayers.begin();
    for( int i = 0; i < iLayerIndex; ++i )
        ++it;

    ( *it )->AddShader( iShader );
}


int
cLayerEngine::LayerIndex( const cLayer * iLayer ) const
{
    int i = 0;
    for( auto layer : mLayers )
    {
        if( layer == iLayer )
            return  i;
        ++i;
    }

    return  -1;
}


void
cLayerEngine::LayersEnumerator( std::function<void( ::nCore::nRender::cLayer* )> iFunction )
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
        return  mLayers.back();

    auto it = mLayers.begin();
    for( int i = 0; i < iLayerIndex; ++i )
        ++it;

    return  *it;
}


int
cLayerEngine::AddEntityInLayer( ::nCore::nECS::nCore::cEntity * iEntity, int iLayerIndex )
{
    if( mLayers.size() == 0 )
        AddLayer();

    if( iLayerIndex < 0 || iLayerIndex >= mLayers.size() )
        return  -1;

    auto it = mLayers.begin();
    for( int i = 0; i < iLayerIndex; ++i )
        ++it;

    return  ( *it )->AddEntity( iEntity );
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


} // namespace nRender
} // namespace nCore

