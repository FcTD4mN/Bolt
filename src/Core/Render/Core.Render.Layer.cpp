#include "Core.Render.Layer.h"

#include "Core.ECS.Core.Entity.h"
#include "Core.ECS.Component.ZDepth.h"

namespace nRender
{


cLayer::~cLayer()
{
}


cLayer::cLayer()
{
    mRenderTexture = new sf::RenderTexture();
    mRenderTexture->create( 800, 600 );
    mRenderTextureSprite.setTexture( mRenderTexture->getTexture() );
}


void
cLayer::Draw()
{
    for( auto ent : mEntities )
        ent->DrawUsingObserverSystems( mRenderTexture );

    mRenderTextureSprite.setTexture( mRenderTexture->getTexture() );
}


void
cLayer::Clear()
{
    mRenderTexture->clear( sf::Color( 0,0,0,0 ) );
}


void
cLayer::Display()
{
    mRenderTexture->display();
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


const sf::Sprite&
cLayer::Sprite() const
{
    return  mRenderTextureSprite;
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

