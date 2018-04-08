 #include "Core.ECS.System.AnimationRenderer.h"


#include "Core.ECS.Core.Entity.h"

#include "Core.ECS.Component.Position.h"
#include "Core.ECS.Component.SpriteAnimated.h"


namespace nECS {


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------ Construction/Destruction
// -------------------------------------------------------------------------------------


cAnimationRenderer::~cAnimationRenderer()
{
}


cAnimationRenderer::cAnimationRenderer() :
    tSuperClass()
{
}


// -------------------------------------------------------------------------------------
// ----------------------------------------------------------------------- Init/Finalize
// -------------------------------------------------------------------------------------


void
cAnimationRenderer::Initialize()
{
}


void
cAnimationRenderer::Finalize()
{
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------- Update/Draw
// -------------------------------------------------------------------------------------


void
cAnimationRenderer::Draw( sf::RenderTarget* iRenderTarget )
{
    sf::RectangleShape rect;

    for( int i = 0; i < mEntityGroup.size(); ++i )
    {
        cEntity* entity = mEntityGroup[ i ];

        auto spriteanimated = dynamic_cast< cSpriteAnimated* >( entity->GetComponentByName( "spriteanimated" ) );
        auto position       = dynamic_cast< cPosition* >( entity->GetComponentByName( "position" ) );

        // Because sprite's origin is set to be the very center of the image, we need to
        // reposition it so it matches top left format given by position
        spriteanimated->mSprite.setPosition( position->mPosition + spriteanimated->mSprite.getOrigin() );

        iRenderTarget->draw( spriteanimated->mSprite );
    }
}


void
cAnimationRenderer::Update( unsigned int iDeltaTime )
{
    for( int i = 0; i < mEntityGroup.size(); ++i )
    {
        cEntity* entity = mEntityGroup[ i ];

        auto spriteanimated = dynamic_cast< cSpriteAnimated* >( entity->GetComponentByName( "spriteanimated" ) );
        auto position       = dynamic_cast< cPosition* >( entity->GetComponentByName( "position" ) );
        spriteanimated->mSprite.setPosition( position->mPosition );

        if( spriteanimated->mPaused )
            continue;

        if( spriteanimated->mClock.getElapsedTime().asSeconds() > 1 / spriteanimated->mFrameRate )
        {
            spriteanimated->NextFrame();
            spriteanimated->mClock.restart();
        }
    }
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------ Entity
// -------------------------------------------------------------------------------------


void
cAnimationRenderer::IncomingEntity( cEntity * iEntity )
{
    auto spriteanimated = iEntity->GetComponentByName( "spriteanimated" );
    auto position = iEntity->GetComponentByName( "position" );

    if( spriteanimated && position )
        AcceptEntity( iEntity );
}


} // namespace nECS

