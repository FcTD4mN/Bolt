#include "Core.Render.Layer.h"

#include "Core.ECS.Core.Entity.h"
#include "Core.ECS.Component.ZDepth.h"

namespace nRender
{


cLayer::~cLayer()
{
    delete  mShaderRenderTextureInput;
    delete  mShaderRenderTextureOutput;
}


cLayer::cLayer( const sf::Vector2f& iViewSize ) :
    mZLayer( 1.0F ),
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
            shader->setUniform( "texture", texture );
            sprite.setTexture( texture );

            mShaderRenderTextureOutput->clear( sf::Color( 0, 0, 0, 0 ) );
            mShaderRenderTextureOutput->draw( sprite, shader );
            mShaderRenderTextureOutput->display();

            std::swap( mShaderRenderTextureInput, mShaderRenderTextureOutput );
        }

        // Finally we draw the result in the render target
        sprite.setTexture( mShaderRenderTextureInput->getTexture() );
        iRenderTarget->draw( sprite );
    }
}


void
cLayer::AddEntity( ::nECS::cEntity * iEntity )
{
    auto zdepth = dynamic_cast<::nECS::cZDepth*>( iEntity->GetComponentByName( "zdepth" ) );
    double zEnteringEntityDepth = 1.0;
    if( zdepth )
        zEnteringEntityDepth = zdepth->ZDepth();

    auto it = mEntities.begin();

    while( it != mEntities.end() )
    {
        auto zdepthEnt = dynamic_cast< ::nECS::cZDepth* >( (*it)->GetComponentByName( "zdepth" ) );
        double entityZDepth = 1.0;
        if( zdepthEnt )
            entityZDepth = zdepthEnt->ZDepth();

        if( entityZDepth > zEnteringEntityDepth )
            break;

        ++it;
    }

    mEntities.insert( it, iEntity );
}


void
cLayer::ZLayer( float iZLayer )
{
    mZLayer = iZLayer;
    if( mZLayer == 0.0F )
        mZLayer = 1.0F;
}


void
cLayer::SetViewCenter( const sf::Vector2f & iCenter )
{
    mView.setCenter( iCenter / mZLayer );
}


void
cLayer::AddShader( sf::Shader* iShader )
{
    mShaders.push_back( iShader );
    if( !mShaderRenderTextureInput )
    {
        mShaderRenderTextureInput = new sf::RenderTexture();
        mShaderRenderTextureInput->create( mView.getSize().x, mView.getSize().y );
    }
    if( !mShaderRenderTextureOutput )
    {
        mShaderRenderTextureOutput = new sf::RenderTexture();
        mShaderRenderTextureOutput->create( mView.getSize().x, mView.getSize().y );
    }
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
}


}

