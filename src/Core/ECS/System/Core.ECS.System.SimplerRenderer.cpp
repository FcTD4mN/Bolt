 #include "Core.ECS.System.SimplerRenderer.h"


#include "Core.ECS.Component.Color.h"
#include "Core.ECS.Component.Position.h"
#include "Core.ECS.Component.Size.h"

#include "Core.ECS.Core.Entity.h"

#include "Core.Math.Utils.h"


namespace nECS {


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------ Construction/Destruction
// -------------------------------------------------------------------------------------


cSimplerRenderer::~cSimplerRenderer()
{
}


cSimplerRenderer::cSimplerRenderer() :
    tSuperClass()
{
}


// -------------------------------------------------------------------------------------
// ----------------------------------------------------------------------- Init/Finalize
// -------------------------------------------------------------------------------------


void
cSimplerRenderer::Initialize()
{
}


void
cSimplerRenderer::Finalize()
{
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------- Update/Draw
// -------------------------------------------------------------------------------------


void
cSimplerRenderer::DrawEntity( sf::RenderTarget * iRenderTarget, cEntity * iEntity )
{
    sf::RectangleShape rect( sf::Vector2f( 10, 10 ) );
    sf::CircleShape triangle( 80.0F, 3 ); // 3 sides circle = triangle
    sf::Vector2f origin;

    auto position = dynamic_cast< cPosition* >( iEntity->GetComponentByName( "position" ) );
    auto size = dynamic_cast< cSize* >( iEntity->GetComponentByName( "size" ) );
    auto color = dynamic_cast< cColor* >( iEntity->GetComponentByName( "color" ) );

    sf::Vector2f positionVector( float( position->X() ), float( position->Y() ) );

    rect.setSize( size->AsVector2F() );
    rect.setPosition( positionVector );
    rect.setFillColor( color->AsSFCOlor() );
    iRenderTarget->draw( rect );
}


void
cSimplerRenderer::Update( unsigned int iDeltaTime )
{
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------ Entity
// -------------------------------------------------------------------------------------


void
cSimplerRenderer::IncomingEntity( cEntity * iEntity )
{
    auto position = iEntity->GetComponentByName( "position" );
    auto size = iEntity->GetComponentByName( "size" );
    auto color = iEntity->GetComponentByName( "color" );

    if( position && size && color )
        AcceptEntity( iEntity );
}


} //nECS

