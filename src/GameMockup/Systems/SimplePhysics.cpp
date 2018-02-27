 #include "SimplePhysics.h"

#include "ECS/Entity.h"
#include "GameMockup/GameApplication.h"
#include "GameMockup/Components/SimplePhysic.h"
#include "GameMockup/Components/Position.h"


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------ Construction/Destruction
// -------------------------------------------------------------------------------------


cSimplePhysics::~cSimplePhysics()
{
}


cSimplePhysics::cSimplePhysics() :
    tSuperClass(),
    mEntityMap()
{
}


// -------------------------------------------------------------------------------------
// ----------------------------------------------------------------------- Init/Finalize
// -------------------------------------------------------------------------------------


void
cSimplePhysics::Initialize()
{
}


void
cSimplePhysics::Finalize()
{
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------- Update/Draw
// -------------------------------------------------------------------------------------


void
cSimplePhysics::Draw( sf::RenderTarget* iRenderTarget )
{
#ifdef _DEBUG

    sf::RectangleShape rect( sf::Vector2f( 10,10 ) );

    for( int i = 0; i < mEntityGroup.size(); ++i )
    {
        cEntity* entity = mEntityGroup[ i ];

        auto simplephysic = dynamic_cast< cSimplePhysic* >( entity->GetComponentByName( "simplephysic" ) );

        // DEBUG Hitbox Drawing
        rect.setSize( sf::Vector2f( simplephysic->mHitBox.width, simplephysic->mHitBox.height ) );
        rect.setPosition( sf::Vector2f( simplephysic->mHitBox.left, simplephysic->mHitBox.top ) );
        rect.setFillColor( sf::Color( 255, 50, 50, 100 ) );

        iRenderTarget->draw( rect );

        // DEBUG Surrounding Drawing
        std::vector< cEntity* > surrounding = mEntityMap.GetSurroundingEntitiesOf( entity );
        for( int j = 0; j < surrounding.size(); ++j )
        {
            cEntity* surroundingEntity = surrounding[ j ];
            auto simplephysicSurr = dynamic_cast< cSimplePhysic* >( surroundingEntity->GetComponentByName( "simplephysic" ) );

            sf::VertexArray lines( sf::LinesStrip, 2 );
            lines[ 0 ].position = sf::Vector2f( simplephysic->mHitBox.left + simplephysic->mHitBox.width/2, simplephysic->mHitBox.top + simplephysic->mHitBox.height / 2 );
            lines[ 0 ].color = sf::Color( 20, 20, 255, 150 );
            lines[ 1 ].position = sf::Vector2f( simplephysicSurr->mHitBox.left + simplephysicSurr->mHitBox.width / 2, simplephysicSurr->mHitBox.top + simplephysicSurr->mHitBox.height / 2 );
            lines[ 1 ].color = sf::Color( 20, 20, 255, 150 );

            iRenderTarget->draw( lines );
        }
    }

#endif // _DEBUG
}


void
cSimplePhysics::Update( unsigned int iDeltaTime )
{
    sf::Rect< float > projection;
    for( int i = 0; i < mEntityGroup.size(); ++i )
    {
        cEntity* entity = mEntityGroup[ i ];
        auto simplephysic   = dynamic_cast< cSimplePhysic* >( entity->GetComponentByName( "simplephysic" ) );
        auto position       = dynamic_cast< cPosition* >( entity->GetComponentByName( "position" ) );
        bool collided = false;

        projection = simplephysic->mHitBox;
        projection.left += simplephysic->mVelocity.x;
        projection.top += simplephysic->mVelocity.y;

        std::vector< cEntity* > surrounding = mEntityMap.GetSurroundingEntitiesOf( entity );

        for( int j = 0; j < surrounding.size(); ++j )
        {
            cEntity* surroundingEntity = surrounding[ j ];

            auto simplephysicSurr = dynamic_cast< cSimplePhysic* >( surroundingEntity->GetComponentByName( "simplephysic" ) );
            if( projection.intersects( simplephysicSurr->mHitBox ) )
            {
                collided = true;
                simplephysic->mVelocity.x = 0.0F;
                simplephysic->mVelocity.y = 0.0F;
                break;
            }
        }

        if( !collided && ( simplephysic->mVelocity.x != 0.0F || simplephysic->mVelocity.y != 0.0F ) )
        {
            // Remove Entity before changing its position, so it's quick and easy
            mEntityMap.RemoveEntityNotUpdated( entity );

            position->mPosition.x += simplephysic->mVelocity.x;
            position->mPosition.y += simplephysic->mVelocity.y;
            simplephysic->mHitBox.left += simplephysic->mVelocity.x;
            simplephysic->mHitBox.top += simplephysic->mVelocity.y;

            // Add it back at its new position
            mEntityMap.AddEntity( entity );
        }
    }
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------ Entity
// -------------------------------------------------------------------------------------


void
cSimplePhysics::IncomingEntity( cEntity * iEntity )
{
    auto simplephysic = iEntity->GetComponentByName( "simplephysic" );

    if( simplephysic )
    {
        AcceptEntity( iEntity );
        mEntityMap.AddEntity( iEntity );
    }
}


void
cSimplePhysics::EntityLost( cEntity * iEntity )
{
    tSuperClass::EntityLost( iEntity );
    mEntityMap.RemoveEntityNotUpdated( iEntity );
}




