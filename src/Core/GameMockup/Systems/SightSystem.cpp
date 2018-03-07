#include "SightSystem.h"

#include "Math/Utils.h"

#include "ECS/Core/Entity.h"
#include "ECS/Utilities/EntityParser.h"
#include "ECS/Core/World.h"

#include "GameMockup/GameApplication.h"
#include "GameMockup/Components/FieldOfView.h"
#include "GameMockup/Components/Position.h"
#include "GameMockup/Components/Size.h"
#include "GameMockup/Components/Direction.h"

#include "Mapping/PhysicEntityGrid.h"

#include "SFML/Graphics.hpp"

#include <iostream>

// -------------------------------------------------------------------------------------
// ------------------------------------------------------------ Construction/Destruction
// -------------------------------------------------------------------------------------


cSightSystem::~cSightSystem()
{
}


cSightSystem::cSightSystem() :
    tSuperClass()
{
}


// -------------------------------------------------------------------------------------
// ----------------------------------------------------------------------- Init/Finalize
// -------------------------------------------------------------------------------------


void
cSightSystem::Initialize()
{
}


void
cSightSystem::Finalize()
{
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------- Update/Draw
// -------------------------------------------------------------------------------------


void
cSightSystem::Draw( sf::RenderTarget* iRenderTarget )
{
    sf::VertexArray lines( sf::LinesStrip, 2 );
    lines[ 0 ].position = mDEBUGSightPA;
    lines[ 0 ].color = sf::Color( 20, 20, 255, 150 );
    lines[ 1 ].position = mDEBUGSightPA + mDEBUGSightLine;
    lines[ 1 ].color = sf::Color( 20, 20, 255, 150 );

    sf::ConvexShape sight;
    sight.setPointCount( 3 );
    sight.setPoint( 0, mDEBUGTriangleA );
    sight.setPoint( 1, mDEBUGTriangleB );
    sight.setPoint( 2, mDEBUGTriangleC );
    sight.setFillColor( sf::Color( 0, 0, 255 ) );

    iRenderTarget->draw( lines );
    iRenderTarget->draw( sight );
}


void
cSightSystem::Update( unsigned int iDeltaTime )
{
    for( int i = 0; i < mEntityGroup.size(); ++i )
    {
        cEntity* entity = mEntityGroup[ i ];

        auto position = dynamic_cast< cPosition* >( entity->GetComponentByName( "position" ) );
        auto size = dynamic_cast< cSize* >( entity->GetComponentByName( "size" ) );
        auto direction = dynamic_cast< cDirection* >( entity->GetComponentByName( "direction" ) );
        auto fieldofview = dynamic_cast< cFieldOfView* >( entity->GetComponentByName( "fieldofview" ) );

        // Get FOV triangle
        sf::Vector2f a = position->mPosition;
        float semiAngle = float(fieldofview->mAngle / 2.0F);
        sf::Transform rotation;
        rotation.rotate( semiAngle );

        sf::Vector2f baseVector = direction->mDirection * 500.0F;
        sf::Vector2f b = rotation.transformPoint( baseVector );

        rotation.rotate( float(-fieldofview->mAngle) );
        sf::Vector2f c = rotation.transformPoint( baseVector );

        // Translation
        b += a;
        c += a;

        mDEBUGTriangleA = a;
        mDEBUGTriangleB = b;
        mDEBUGTriangleC = c;

        for( int j = 0; j < mPointsOfInterest.size(); ++j )
        {
            cEntity* poi = mPointsOfInterest[ j ];

            auto positionPOI = dynamic_cast< cPosition* >( poi->GetComponentByName( "position" ) );
            auto sizePOI = dynamic_cast< cSize* >( poi->GetComponentByName( "size" ) );

            // Get 4 extreme points, and then check if any is in FOV
            sf::Vector2f poiA = positionPOI->mPosition;
            sf::Vector2f poiB = poiA;
            poiB.x += sizePOI->mSize.x;
            sf::Vector2f poiC = poiB;
            poiB.y += sizePOI->mSize.y;
            sf::Vector2f poiD = poiA;
            poiD.y += sizePOI->mSize.y;

            if( IsPointInTriangle( poiA,    a, b, c )
                || IsPointInTriangle( poiB, a, b, c )
                || IsPointInTriangle( poiC, a, b, c )
                || IsPointInTriangle( poiD, a, b, c )
                )
            {
                printf( "IN FOV\n" );
                auto entityMap = cGameApplication::App()->EntityMap();
            }
        }
    }
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------ Entity
// -------------------------------------------------------------------------------------


void
cSightSystem::IncomingEntity( cEntity* iEntity )
{
    auto position       = iEntity->GetComponentByName( "position" );
    auto size           = iEntity->GetComponentByName( "size" );
    auto direction      = iEntity->GetComponentByName( "direction" );
    auto fieldofview    = iEntity->GetComponentByName( "fieldofview" );

    if( iEntity->HasTag( "hero" ) )
        mPointsOfInterest.push_back( iEntity );
    else if( position && size && direction && fieldofview )
        AcceptEntity( iEntity );
}

