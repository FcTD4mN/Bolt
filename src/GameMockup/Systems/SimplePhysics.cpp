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
    sf::RectangleShape rect( sf::Vector2f( 10,10 ) );

    for( int i = 0; i < mEntityGroup.size(); ++i )
    {
        cEntity* entity = mEntityGroup[ i ];

        auto simplephysic = dynamic_cast< cSimplePhysic* >( entity->GetComponentByName( "simplephysic" ) );

        rect.setSize( sf::Vector2f( simplephysic->mHitBox.width, simplephysic->mHitBox.height ) );
        rect.setPosition( sf::Vector2f( simplephysic->mHitBox.left, simplephysic->mHitBox.top ) );
        rect.setFillColor( sf::Color( 255, 50, 50, 100 ) );

        iRenderTarget->draw( rect );
    }
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

        projection = simplephysic->mHitBox;
        projection.left += simplephysic->mVelocity.x;
        projection.top += simplephysic->mVelocity.y;

        for( int j = 0; j < mEntityGroup.size(); ++j )
        {
            cEntity* surroundingEntity = mEntityGroup[ j ];
            if( entity == surroundingEntity )
                continue;

            auto simplephysicSurr = dynamic_cast< cSimplePhysic* >( surroundingEntity->GetComponentByName( "simplephysic" ) );
            if( projection.intersects( simplephysicSurr->mHitBox ) )
            {
                simplephysic->mVelocity.x = 0.0F;
                simplephysic->mVelocity.y = 0.0F;
                break;
            }
        }

        position->mPosition.x += simplephysic->mVelocity.x;
        position->mPosition.y += simplephysic->mVelocity.y;
        simplephysic->mHitBox.left += simplephysic->mVelocity.x;
        simplephysic->mHitBox.top += simplephysic->mVelocity.y;
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
        mEntityMap.AddObject( iEntity );
    }
}




