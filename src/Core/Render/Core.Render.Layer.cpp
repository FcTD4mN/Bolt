#include "Core.Render.Layer.h"

#include "Core.ECS.Core.Entity.h"
#include "Core.ECS.Component.ZDepth.h"

#include "Core.Mapping.PhysicEntityGrid.h"

#include "Core.Shader.Shader2D.h"

namespace nRender
{


cLayer::~cLayer()
{
	delete  mEntityGrid;

    delete  mShaderRenderTextureInput;
    delete  mShaderRenderTextureOutput;

    for( auto shader : mShaders )
        delete  shader;
}


cLayer::cLayer( const sf::Vector2f& iViewSize ) :
    mName( "Unnammed Layer" ),
	mOffset( sf::Vector2f( 0, 0 ) ),
	mZoomFactor( 1.0 ),
    mZLayer( 1.0F ),
	mEntityGrid( 0 ),
	mFixedLayer( false ),
    mShaderRenderTextureInput( 0 ),
    mShaderRenderTextureOutput( 0 )
{
    mView.setViewport( sf::FloatRect( 0.0F, 0.0F, 1.0F, 1.0F ) );
    mView.setSize( iViewSize );
    if( mZLayer == 0.0F )
        mZLayer = 1.0F;
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
cLayer::AddEntity( ::nECS::cEntity * iEntity )
{
    auto zdepth = dynamic_cast<::nECS::cZDepth*>( iEntity->GetComponentByName( "zdepth" ) );
    double zEnteringEntityDepth = 1.0;
    if( zdepth )
        zEnteringEntityDepth = zdepth->ZDepth();

    auto it = mEntities.begin();
	int index = 0;

    while( it != mEntities.end() )
    {
        auto zdepthEnt = dynamic_cast< ::nECS::cZDepth* >( (*it)->GetComponentByName( "zdepth" ) );
        double entityZDepth = 1.0;
        if( zdepthEnt )
            entityZDepth = zdepthEnt->ZDepth();

        if( entityZDepth > zEnteringEntityDepth )
            break;

        ++it;
		++index;
    }

	mEntityGrid->AddEntity( iEntity );
    mEntities.insert( it, iEntity );
	return  index;
}


void
cLayer::RemoveEntity( ::nECS::cEntity * iEntity )
{
	for( auto it = mEntities.begin(); it != mEntities.end(); ++it )
	{
		if( *it == iEntity )
		{
			mEntities.erase( it );
			break;
		}
	}

	mEntityGrid->RemoveEntityNotUpdated( iEntity );
}


void
cLayer::ZLayer( float iZLayer )
{
    mZLayer = iZLayer;
    if( mZLayer == 0.0F )
        mZLayer = 1.0F;
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


::nMapping::cEntityGrid*
cLayer::EntityGrid()
{
	return  mEntityGrid;
}


// ------------------
// EDITOR -----------
// ------------------


int
cLayer::EntityCount() const
{
    return  int(mEntities.size());
}


::nECS::cEntity*
cLayer::EntityAtIndex( int iIndex )
{
    auto it = mEntities.begin();
    for( int i = 0; i < iIndex; ++i )
        ++it;

    return  *it;
}


void
cLayer::AddShader( ::nShaders::cShader2D* iShader )
{
    mShaders.push_back( iShader );
    if( !mShaderRenderTextureInput )
    {
        mShaderRenderTextureInput = new sf::RenderTexture();
        mShaderRenderTextureInput->create( unsigned int(mView.getSize().x), unsigned int(mView.getSize().y) );
    }
    if( !mShaderRenderTextureOutput )
    {
        mShaderRenderTextureOutput = new sf::RenderTexture();
        mShaderRenderTextureOutput->create( unsigned int(mView.getSize().x), unsigned int(mView.getSize().y) );
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
	//return  sf::FloatRect( (iRect.left + mOffset.x) * mZoomFactor, (iRect.top + mOffset.y) * mZoomFactor, iRect.width * mZoomFactor, iRect.height * mZoomFactor );
}


sf::FloatRect
cLayer::MapRectFromLayer( const sf::FloatRect& iRect ) const
{
	return  sf::FloatRect( iRect.left - mOffset.x, iRect.top - mOffset.y, iRect.width, iRect.height );
	//return  sf::FloatRect( iRect.left / mZoomFactor - mOffset.x, iRect.top / mZoomFactor - mOffset.y, iRect.width / mZoomFactor, iRect.height / mZoomFactor );
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
    iNode->SetAttribute( "viewwidth",	view.x );
    iNode->SetAttribute( "viewheight",	view.y );
    iNode->SetAttribute( "zlayer",		mZLayer );

	// ENTITY MAP
	tinyxml2::XMLElement* entityMap = iDocument->NewElement( "entityMap" );
	entityMap->SetAttribute( "width", mEntityGrid->Width() );
	entityMap->SetAttribute( "height", mEntityGrid->Height() );
	entityMap->SetAttribute( "cellsize", mEntityGrid->CellSize() );
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
	// ====================== EntityMap
	tinyxml2::XMLElement* entityMap = iNode->FirstChildElement( "entityMap" );
	int eMapWidth = entityMap->IntAttribute( "width" );
	int eMapHeight = entityMap->IntAttribute( "height" );
	int eMapCellSize = entityMap->IntAttribute( "cellsize" );

	// Loading means we want a fresh entity map and a fresh world, so if they already exist, we diss them for brand new ones
	if( mEntityGrid )
		delete  mEntityGrid;
	mEntityGrid = new ::nMapping::cPhysicEntityGrid( eMapWidth, eMapHeight, eMapCellSize );
}


}

