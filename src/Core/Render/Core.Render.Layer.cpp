#include "Core.Render.Layer.h"


#include "Core.Application.GlobalAccess.h"
#include "Core.ECS.Core.Entity.h"
#include "Core.ECS.Component.ZDepth.h"
#include "Core.Mapping.EntityMap.h"
#include "Core.Render.LayerEngine.h"
#include "Core.Shader.Shader2D.h"


namespace nCore {
namespace nRender {


cLayer::~cLayer()
{
    while( mEntities.size() > 0 )
        mEntities.back()->Destroy();

    delete  mEntityMap;

    delete  mShaderRenderTextureInput;
    delete  mShaderRenderTextureOutput;

    for( auto shader : mShaders )
        delete  shader;
}


cLayer::cLayer( cLayerEngine* iParentLayerEngine, const sf::Vector2f& iViewSize, eLayerMappingType iType ) :
    mParentLayerEngine( iParentLayerEngine ),
    mName( "Unnammed Layer" ),
    mOffset( sf::Vector2f( 0, 0 ) ),
    mZoomFactor( 1.0 ),
    mZLayer( 1.0F ),
    mEntityMap( 0 ),
    mMappingType( iType ),
    mFixedLayer( false ),
    mVisible( true ),
    mShaderRenderTextureInput( 0 ),
    mShaderRenderTextureOutput( 0 )
{
    mView.setViewport( sf::FloatRect( 0.0F, 0.0F, 1.0F, 1.0F ) );
    mView.setSize( iViewSize );
    mView.setCenter( iViewSize.x / 2, iViewSize.y / 2 );

    if( mZLayer == 0.0F )
        mZLayer = 1.0F;

    if( mMappingType == kPositionSize )
        mEntityMap = new ::nCore::nMapping::cPositionSizeGrid( 100, 100, 32 );
    else if( mMappingType == kPhysics )
        mEntityMap = new ::nCore::nMapping::cPhysicEntityMap( 100, 100, 32 );
}


void
cLayer::Draw( sf::RenderTarget* iRenderTarget )
{
    iRenderTarget->setView( mView );

    if( mShaders.size() == 0 )
    {
        for( auto ent : mEntities )
            ent->DrawUsingObserverSystems( iRenderTarget );
    }
    else
    {
        // We draw in an off-screen buffer
        mShaderRenderTextureInput->clear( sf::Color( 0,0,0,0 ) );

        for( auto ent : mEntities )
            ent->DrawUsingObserverSystems( mShaderRenderTextureInput );

        mShaderRenderTextureInput->display();

        // We then apply shader after shader, on top of each others
        sf::Sprite sprite;
        for( auto shader : mShaders )
        {
            sf::Texture texture = mShaderRenderTextureInput->getTexture();
            shader->GetSFShader()->setUniform( "texture", texture );
            sprite.setTexture( texture );

            mShaderRenderTextureOutput->clear( sf::Color( 0, 0, 0, 0 ) );
            mShaderRenderTextureOutput->draw( sprite, shader->GetSFShader() );
            mShaderRenderTextureOutput->display();

            std::swap( mShaderRenderTextureInput, mShaderRenderTextureOutput );
        }

        // Finally we draw the result in the render target
        sprite.setTexture( mShaderRenderTextureInput->getTexture() );
        iRenderTarget->draw( sprite );
    }
}


int
cLayer::AddEntity( ::nCore::nECS::nCore::cEntity * iEntity )
{
    // If an entity joins a layer, it has to leave any layer it's laready in first
    auto layer = iEntity->Layer();
    if( layer )
        layer->RemoveEntity( iEntity );

    auto zdepth = iEntity->GetComponentByIDAs< ::nCore::nECS::nComponent::cZDepth* >( "zdepth" );

    double zEnteringEntityDepth = 1.0;
    if( zdepth )
        zEnteringEntityDepth = zdepth->ZDepth();

    auto it = mEntities.begin();
    int index = 0;

    while( it != mEntities.end() )
    {
        auto zdepthEnt = iEntity->GetComponentByIDAs< ::nCore::nECS::nComponent::cZDepth* >( "zdepth" );
        double entityZDepth = 1.0;
        if( zdepthEnt )
            entityZDepth = zdepthEnt->ZDepth();

        if( entityZDepth > zEnteringEntityDepth )
            break;

        ++it;
        ++index;
    }

    mEntityMap->AddEntity( iEntity );
    mEntities.insert( it, iEntity );

    iEntity->mContainerLayer = this;

    return  index;
}


void
cLayer::RemoveEntity( ::nCore::nECS::nCore::cEntity * iEntity )
{
    for( auto it = mEntities.begin(); it != mEntities.end(); ++it )
    {
        if( *it == iEntity )
        {
            mEntities.erase( it );
            break;
        }
    }

    mEntityMap->RemoveEntity( iEntity );
    iEntity->mContainerLayer = 0;
}


void
cLayer::ZLayer( float iZLayer )
{
    mZLayer = iZLayer;
    if( mZLayer == 0.0F )
        mZLayer = 1.0F;
}


float
cLayer::ZLayer() const
{
    return  mZLayer;
}


void
cLayer::SetView( const sf::View & iView )
{
    if ( !mFixedLayer )
    {
        mView = iView;
        mView.setCenter( iView.getCenter() / mZLayer );
        mOffset = iView.getCenter() - mView.getCenter();
    }
}


sf::View
cLayer::View()
{
    return  mView;
}


void
cLayer::ApplyZoom( float iZoom )
{
    if ( !mFixedLayer )
    {
        mView.zoom( iZoom );
        mZoomFactor *= iZoom;
    }
}


const std::string &
cLayer::Name() const
{
    return  mName;
}


void
cLayer::Name( const std::string & iName )
{
    mName = iName;
}


bool
cLayer::Fixed() const
{
    return  mFixedLayer;
}


void
cLayer::Fixed( bool iFixed )
{
    mFixedLayer = iFixed;
    if( mFixedLayer )
    {
        mView = sf::View();
        mView.setSize( sf::Vector2f( MAINWIN->getSize() ) );
        mView.setCenter( mView.getSize().x / 2, mView.getSize().y/2 );
        mOffset = sf::Vector2f( 0, 0 );
    }
}


bool
cLayer::Visible() const
{
    return  mVisible;
}


void
cLayer::Visible( bool iVisible )
{
    mVisible = iVisible;
}


int
cLayer::Index() const
{
    return 0;
}


::nCore::nMapping::cEntityMap*
cLayer::EntityMap()
{
    return  mEntityMap;
}


// ------------------
// EDITOR -----------
// ------------------


int
cLayer::EntityCount() const
{
    return  int(mEntities.size());
}


::nCore::nECS::nCore::cEntity*
cLayer::EntityAtIndex( int iIndex )
{
    auto it = mEntities.begin();
    for( int i = 0; i < iIndex; ++i )
        ++it;

    return  *it;
}


int
cLayer::EntityIndex( ::nCore::nECS::nCore::cEntity * iEntity )
{
    int index = 0;
    for( auto& ent : mEntities )
    {
        if( ent == iEntity )
            return  index;

        ++index;
    }

    return  -1;
}


int
cLayer::LayerIndex() const
{
    if( mParentLayerEngine )
        return  mParentLayerEngine->LayerIndex( this );

    return  -1;
}


void
cLayer::AddShader( ::nCore::nShader::cShader2D* iShader )
{
    mShaders.push_back( iShader );
    if( !mShaderRenderTextureInput )
    {
        mShaderRenderTextureInput = new sf::RenderTexture();
        mShaderRenderTextureInput->create( (unsigned int)(mView.getSize().x), (unsigned int)(mView.getSize().y) );
    }
    if( !mShaderRenderTextureOutput )
    {
        mShaderRenderTextureOutput = new sf::RenderTexture();
        mShaderRenderTextureOutput->create( (unsigned int)(mView.getSize().x), (unsigned int)(mView.getSize().y) );
    }
}


sf::Vector2f
cLayer::MapVectToLayer( const sf::Vector2f& iVector ) const
{
    return  iVector + mOffset;
}


sf::Vector2f
cLayer::MapVectFromLayer( const sf::Vector2f& iVector ) const
{
    return  iVector - mOffset;
}


sf::FloatRect
cLayer::MapRectToLayer( const sf::FloatRect& iRect ) const
{
    return  sf::FloatRect( (iRect.left + mOffset.x), (iRect.top + mOffset.y), iRect.width, iRect.height );
}


sf::FloatRect
cLayer::MapRectFromLayer( const sf::FloatRect& iRect ) const
{
    return  sf::FloatRect( iRect.left - mOffset.x, iRect.top - mOffset.y, iRect.width, iRect.height );
}


// ------------------
// PRIVATE ----------
// ------------------


void
cLayer::ClearShaders()
{
    for( auto shader : mShaders )
        delete shader;

    mShaders.clear();
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------ Input/Output
// -------------------------------------------------------------------------------------


void
cLayer::SaveXML( tinyxml2::XMLElement* iNode, tinyxml2::XMLDocument* iDocument )
{
    auto view = mView.getSize();

    // VIEW
    iNode->SetAttribute( "name",        mName.c_str() );
    iNode->SetAttribute( "viewwidth",   view.x );
    iNode->SetAttribute( "viewheight",  view.y );
    iNode->SetAttribute( "zlayer",      mZLayer );
    iNode->SetAttribute( "fixed",       mFixedLayer );
    iNode->SetAttribute( "zoom",        mZoomFactor );

    // ENTITY MAP
    tinyxml2::XMLElement* entityMap = iDocument->NewElement( "entityMap" );
    entityMap->SetAttribute( "width", mEntityMap->Width() );
    entityMap->SetAttribute( "height", mEntityMap->Height() );
    entityMap->SetAttribute( "cellsize", mEntityMap->CellSize() );
    iNode->LinkEndChild( entityMap );

    // SHADERS
    tinyxml2::XMLElement* shadersNode = iDocument->NewElement( "shaders" );
    for( auto shader : mShaders )
    {
        tinyxml2::XMLElement* shaderNode = iDocument->NewElement( "shader" );
        shader->SaveXML( shaderNode, iDocument );
        shaderNode->SetAttribute( "file", shader->GetPathToProgram().filename().string().c_str() );
        shadersNode->LinkEndChild( shaderNode );
    }
    iNode->LinkEndChild( shadersNode );

    // ENTITIES
    tinyxml2::XMLElement* entitiesNode = iDocument->NewElement( "entities" );

    for( auto entity : mEntities )
    {
        tinyxml2::XMLElement* entityNode = iDocument->NewElement( "entity" );
        entity->SaveXML( entityNode, iDocument );
        entitiesNode->LinkEndChild( entityNode );
    }

    iNode->LinkEndChild( entitiesNode );
}


void
cLayer::LoadXML( tinyxml2::XMLElement* iNode )
{
    mName = iNode->Attribute( "name" );

    int viewWidth   = iNode->IntAttribute( "viewwidth" );
    int viewHeight  = iNode->IntAttribute( "viewheight" );
    float zoom      = iNode->FloatAttribute( "zoom" );

    sf::View view = sf::View();
    view.setSize( sf::Vector2f( float(viewWidth), float(viewHeight) ) );

    SetView( view );
    ApplyZoom( zoom );
    Fixed( iNode->BoolAttribute( "fixed" ) );
    ZLayer( iNode->FloatAttribute( "zlayer" ) );

    // ====================== EntityMap
    tinyxml2::XMLElement* entityMap = iNode->FirstChildElement( "entityMap" );
    int eMapWidth = entityMap->IntAttribute( "width" );
    int eMapHeight = entityMap->IntAttribute( "height" );
    int eMapCellSize = entityMap->IntAttribute( "cellsize" );

    // Loading means we want a fresh entity map and a fresh world, so if they already exist, we diss them for brand new ones
    if( mEntityMap )
        delete  mEntityMap;

    if( mMappingType == kPositionSize )
        mEntityMap = new ::nCore::nMapping::cPositionSizeGrid( 100, 100, 32 );
    else if( mMappingType == kPhysics )
        mEntityMap = new ::nCore::nMapping::cPhysicEntityMap( 100, 100, 32 );
}


} // namespace nRender
} // namespace nCore

