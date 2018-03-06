#include "SightSystem.h"

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

    iRenderTarget->draw( lines );
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

        for( int j = 0; j < mPointsOfInterest.size(); ++j )
        {
            cEntity* poi = mPointsOfInterest[ j ];

            auto positionPOI = dynamic_cast< cPosition* >( poi->GetComponentByName( "position" ) );
            sf::Vector2f entityToPOI( positionPOI->mPosition.x - position->mPosition.x , positionPOI->mPosition.y - position->mPosition.y );

            float dotProduct = entityToPOI.x * direction->mDirection.x + entityToPOI.y * direction->mDirection.y;
            float magnetudeA = sqrt( entityToPOI.x * entityToPOI.x + entityToPOI.y *entityToPOI.y );
            float magnetudeB = sqrt( direction->mDirection.x * direction->mDirection.x + direction->mDirection.y *direction->mDirection.y );
            float angle = acos( dotProduct / ( magnetudeA * magnetudeB ) ) * 180 / 3.141592653589793238463;

            if( angle < 90.0F )
            {
                printf( "IN FOV\n" );
                auto entityMap = cGameApplication::App()->EntityMap();
                bool sure = false;

                sf::Vector2f e2poiNormalized = entityToPOI;
                e2poiNormalized /= magnetudeA;
                mDEBUGSightLine = entityToPOI;
                mDEBUGSightPA = position->mPosition;
                mDEBUGSightPB = positionPOI->mPosition;

                std::vector< cEntity* > entInTheWay = entityMap->GetEntitiesFollwingVectorFromEntity( entity, e2poiNormalized );
                for( auto enti : entInTheWay )
                {
                    if( enti->HasTag( "wall" ) )
                    {
                        printf( "DON'T SEE\n" );
                        sure = true;
                        break;
                    }
                    if( enti->HasTag( "hero" ) )
                    {
                        printf( "I SEE YOU BITCH\n" );
                        sure = true;
                        break;
                    }
                }

                if( !sure )
                    printf( "I PROBABLY SEE YOU !\n" );
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

