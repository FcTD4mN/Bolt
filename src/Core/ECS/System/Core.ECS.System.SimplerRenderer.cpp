 #include "Core.ECS.System.SimplerRenderer.h"


#include "Core.ECS.Component.Color.h"
#include "Core.ECS.Component.Text.h"
#include "Core.ECS.Component.Transformation.h"
#include "Core.ECS.Core.Entity.h"
#include "Core.Math.Utils.h"


namespace nCore {
namespace nECS {
namespace nSystem {


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------ Construction/Destruction
// -------------------------------------------------------------------------------------


cSimplerRenderer::~cSimplerRenderer()
{
}


cSimplerRenderer::cSimplerRenderer() :
    tSuperClass( "SimpleRenderer" )
{
}


cSimplerRenderer::cSimplerRenderer( const cSimplerRenderer & iSys ) :
    tSuperClass( iSys )
{
}


void
cSimplerRenderer::Initialize()
{
    mFont = sf::Font();

    mFont.loadFromFile( "resources/Shared/Fonts/arial.ttf" );
}

::nCore::nECS::nCore::cSystem*
cSimplerRenderer::Clone() const
{
    return  new cSimplerRenderer( *this );
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------- Update/Draw
// -------------------------------------------------------------------------------------


void
cSimplerRenderer::DrawEntity( sf::RenderTarget * iRenderTarget, ::nCore::nECS::nCore::cEntity * iEntity )
{
    sf::RectangleShape rect( sf::Vector2f( 10, 10 ) );
    sf::CircleShape triangle( 80.0F, 3 ); // 3 sides circle = triangle
    sf::Vector2f origin;

    auto transformation = iEntity->GetComponentByNameAs< ::nCore::nECS::nComponent::cTransformation* >( "transformation" );
    auto color = iEntity->GetComponentByNameAs< ::nCore::nECS::nComponent::cColor* >( "color" );
    auto text = iEntity->GetComponentByNameAs< ::nCore::nECS::nComponent::cText* >( "text" );

    if( color )
    {
        rect.setSize( transformation->SizeAsVector2F() );
        rect.setPosition( transformation->PositionAsVector2F() );
        rect.setFillColor( color->AsSFCOlor() );
        iRenderTarget->draw( rect );
    }

    if( text )
    {
        sf::Text textToDraw = sf::Text( text->Text(), mFont );
        textToDraw.setPosition( transformation->PositionAsVector2F() );
        iRenderTarget->draw( textToDraw );
    }
}


void
cSimplerRenderer::Update( unsigned int iDeltaTime )
{
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------ Entity
// -------------------------------------------------------------------------------------


void
cSimplerRenderer::IncomingEntity( ::nCore::nECS::nCore::cEntity * iEntity )
{
    auto transformation = iEntity->GetComponentByName( "transformation" );
    auto color          = iEntity->GetComponentByName( "color" );
    auto text           = iEntity->GetComponentByName( "text" );

    if( transformation && ( color || text ) )
        AcceptEntity( iEntity );
}


} // namespace nSystem
} // namespace nECS
} // namespace nCore

