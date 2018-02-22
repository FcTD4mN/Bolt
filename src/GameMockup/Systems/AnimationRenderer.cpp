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
    sf::RectangleShape rect;

    for( int i = 0; i < mEntityGroup.size(); ++i )
    {
        cEntity* entity = mEntityGroup[ i ];

        auto spriteanimated = dynamic_cast< cSpriteAnimated* >( entity->GetComponentByName( "spriteanimated" ) );
        auto position = dynamic_cast< cPosition* >( entity->GetComponentByName( "position" ) );

        rect.setPosition( position->mPosition );
        rect.setSize( sf::Vector2f( spriteanimated->mCurrentSpriteRect.width, spriteanimated->mCurrentSpriteRect.height ) );
        rect.setOutlineColor( sf::Color( 255, 0, 0, 200 ) );
        rect.setFillColor( sf::Color( 255, 0, 0, 200 ) );

        iRenderTarget->draw( spriteanimated->mSprite );
        iRenderTarget->draw( rect );
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




