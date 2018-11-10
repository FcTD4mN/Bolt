 #include "Core.ECS.System.AnimationRenderer.h"


#include "Core.ECS.Core.Entity.h"

#include "Core.ECS.Component.Transformation.h"
#include "Core.ECS.Component.Animations.h"


namespace nCore {
namespace nECS {
namespace nSystem {


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------ Construction/Destruction
// -------------------------------------------------------------------------------------


cAnimationRenderer::~cAnimationRenderer()
{
}


cAnimationRenderer::cAnimationRenderer() :
    tSuperClass( "AnimationRenderer" )
{
}


cAnimationRenderer::cAnimationRenderer( const cAnimationRenderer & iSys ) :
    tSuperClass( iSys )
{
}


::nCore::nECS::nCore::cSystem*
cAnimationRenderer::Clone() const
{
    return  new cAnimationRenderer( *this );
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------- Update/Draw
// -------------------------------------------------------------------------------------


void
cAnimationRenderer::DrawEntity( sf::RenderTarget * iRenderTarget, ::nCore::nECS::nCore::cEntity * iEntity )
{
    sf::RectangleShape rect;

    auto animations     = iEntity->GetComponentByIDAs< ::nCore::nECS::nComponent::cAnimations* >( "animations" );
    auto transformation = iEntity->GetComponentByIDAs< ::nCore::nECS::nComponent::cTransformation* >( "transformation" );

    // Because sprite's origin is set to be the very center of the image, we need to
    // reposition it so it matches top left format given by position
    animations->CurrentAnimationSpritePosition( transformation->PositionAsVector2F() );
    animations->CurrentAnimationSpriteOrigin( sf::Vector2f( 0, 0 ) );
    animations->CurrentAnimationSpriteScale( sf::Vector2f( float( transformation->W() ) / float( animations->CurrentAnimationSpriteWidth() ), float( transformation->H() ) / float( animations->CurrentAnimationSpriteHeight() ) ) );
    animations->Draw( iRenderTarget );
}


void
cAnimationRenderer::Update( unsigned int iDeltaTime )
{
    for( int i = 0; i < mEntityGroup.size(); ++i )
    {
        auto animations = mEntityGroup[ i ]->GetComponentByIDAs< ::nCore::nECS::nComponent::cAnimations* >( "animations" );

        animations->Update( iDeltaTime );
    }
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------ Entity
// -------------------------------------------------------------------------------------


void
cAnimationRenderer::IncomingEntity( ::nCore::nECS::nCore::cEntity* iEntity )
{
    auto animations         = iEntity->GetComponentByID( "animations" );
    auto transformation     = iEntity->GetComponentByID( "transformation" );

    if( animations && transformation )
        AcceptEntity( iEntity );
}


} // namespace nSystem
} // namespace nECS
} // namespace nCore

