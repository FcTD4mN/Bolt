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

    //sf::Shader blur;
    //if( !blur.loadFromFile( "resources/Shared/Shaders/testBlur.frag", sf::Shader::Fragment ) )
    ////if( !blur.loadFromFile( "resources/Shared/Shaders/testEdge.frag", sf::Shader::Fragment ) )
    //    int breakpoint = 1;

    ////blur.setUniform( "edge_threshold", 100.0F );
    ////blur.setUniform( "texture", sf::Shader::CurrentTexture );

    //sf::RenderTexture tempText;
    //tempText.create( 800,600 );
    //tempText.draw( rect );

    iRenderTarget->draw( rect );
    //blur.setUniform( "blur_radius", 2.0F );
    //blur.setUniform( "texture", tempText.getTexture() );
    //iRenderTarget->draw( sf::Sprite( tempText.getTexture() ), &blur );
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

