 #include "AnimationRenderer.h"

#include "ECS/Entity.h"
#include "GameMockup/GameApplication.h"
#include "GameMockup/Components/Position.h"
#include "GameMockup/Components/SpriteAnimated.h"

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
    for( int i = 0; i < mEntityGroup.size(); ++i )
    {
        cEntity* entity = mEntityGroup[ i ];

        auto spriteanimated = dynamic_cast< cSpriteAnimated* >( entity->GetComponentByName( "spriteanimated" ) );

        iRenderTarget->draw( spriteanimated->mSprite );
    }
}


void
cAnimationRenderer::Update()
{
    for( int i = 0; i < mEntityGroup.size(); ++i )
    {
        cEntity* entity = mEntityGroup[ i ];

        auto spriteanimated = dynamic_cast< cSpriteAnimated* >( entity->GetComponentByName( "spriteanimated" ) );
        auto position = dynamic_cast< cPosition* >( entity->GetComponentByName( "position" ) );
        spriteanimated->mSprite.setPosition( position->mPosition );

        if( spriteanimated->mPaused )
            continue;

        if( mClock.getElapsedTime().asSeconds() > 1 / spriteanimated->mFrameRate )
        {
            spriteanimated->NextFrame();
            mClock.restart();
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




