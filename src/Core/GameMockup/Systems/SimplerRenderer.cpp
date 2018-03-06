 #include "SimplerRenderer.h"

#include "ECS/Core/Entity.h"
#include "GameMockup/GameApplication.h"
#include "GameMockup/Components/Color.h"
#include "GameMockup/Components/Direction.h"
#include "GameMockup/Components/Position.h"
#include "GameMockup/Components/Size.h"

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
cSimplerRenderer::Draw( sf::RenderTarget* iRenderTarget )
{
    sf::RectangleShape rect( sf::Vector2f( 10,10 ) );
    sf::CircleShape triangle( 80.0F, 3 ); // 3 sides circle = triangle

    for( int i = 0; i < mEntityGroup.size(); ++i )
    {
        cEntity* entity = mEntityGroup[ i ];

        auto position   = dynamic_cast< cPosition* >( entity->GetComponentByName( "position" ) );
        auto size       = dynamic_cast< cSize* >( entity->GetComponentByName( "size" ) );
        auto color      = dynamic_cast< cColor* >( entity->GetComponentByName( "color" ) );
        auto direction      = dynamic_cast< cDirection* >( entity->GetComponentByName( "direction" ) );

        if( direction )
        {
            triangle.setRadius( size->mSize.x );
            triangle.setPosition( position->mPosition + size->mSize/2.0F );
            triangle.setFillColor( color->mColor );
            triangle.setOrigin( sf::Vector2f( size->mSize.x / 2.0F, 0.0F ) );
            triangle.setOrigin( size->mSize );

            float dotProduct = -direction->mDirection.y;
            float magnitude = sqrt( direction->mDirection.x * direction->mDirection.x + direction->mDirection.y * direction->mDirection.y );
            float angleRad = acos( dotProduct / magnitude );

            triangle.setRotation( angleRad * float( 180.0 / 3.141592653589793238463 ) );
            iRenderTarget->draw( triangle );
        }
        else
        {
            rect.setSize( size->mSize );
            rect.setPosition( position->mPosition );
            rect.setFillColor( color->mColor );
            iRenderTarget->draw( rect );
        }
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
cSimplerRenderer::IncomingEntity( cEntity * iEntity )
{
    auto position = iEntity->GetComponentByName( "position" );
    auto size = iEntity->GetComponentByName( "size" );
    auto color = iEntity->GetComponentByName( "color" );

    if( position && size && color )
        AcceptEntity( iEntity );
}




