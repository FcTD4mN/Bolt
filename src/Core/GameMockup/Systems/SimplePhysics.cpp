 #include "SimplePhysics.h"

#include "ECS/Core/Entity.h"
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
    tSuperClass()
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
    if( 1 ) // Cuz this is really cost heavy
    {
        sf::RectangleShape rect( sf::Vector2f( 10, 10 ) );

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
            //std::vector< cEntity* > surrounding = cGameApplication::App()->EntityMap()->GetSurroundingEntitiesOf( entity );
            //for( int j = 0; j < surrounding.size(); ++j )
            //{
            //    cEntity* surroundingEntity = surrounding[ j ];
            //    auto simplephysicSurr = dynamic_cast< cSimplePhysic* >( surroundingEntity->GetComponentByName( "simplephysic" ) );

            //    sf::VertexArray lines( sf::LinesStrip, 2 );
            //    lines[ 0 ].position = sf::Vector2f( simplephysic->mHitBox.left + simplephysic->mHitBox.width / 2, simplephysic->mHitBox.top + simplephysic->mHitBox.height / 2 );
            //    lines[ 0 ].color = sf::Color( 20, 20, 255, 150 );
            //    lines[ 1 ].position = sf::Vector2f( simplephysicSurr->mHitBox.left + simplephysicSurr->mHitBox.width / 2, simplephysicSurr->mHitBox.top + simplephysicSurr->mHitBox.height / 2 );
            //    lines[ 1 ].color = sf::Color( 20, 20, 255, 150 );

            //    iRenderTarget->draw( lines );
            //}
        }
    }

#endif // _DEBUG
}


void
cSimplePhysics::Update( unsigned int iDeltaTime )
{
    sf::Rect< float > projection;
    cEntityGrid* entityMap = cGameApplication::App()->EntityMap();
    for( int i = 0; i < mDynamicEntities.size(); ++i )
    {
        cEntity* entity = mDynamicEntities[ i ];
        auto simplephysic   = dynamic_cast< cSimplePhysic* >( entity->GetComponentByName( "simplephysic" ) );
        auto position       = dynamic_cast< cPosition* >( entity->GetComponentByName( "position" ) );
        bool collided = false;

        projection = simplephysic->mHitBox;
        projection.left += simplephysic->mVelocity.x;
        projection.top += simplephysic->mVelocity.y;

        std::vector< cEntity* > surrounding;
        entityMap->GetSurroundingEntitiesOf( &surrounding, entity );

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
            entityMap->RemoveEntityNotUpdated( entity );

            position->mPosition.x += simplephysic->mVelocity.x;
            position->mPosition.y += simplephysic->mVelocity.y;
            simplephysic->mHitBox.left += simplephysic->mVelocity.x;
            simplephysic->mHitBox.top += simplephysic->mVelocity.y;

            // very basic test just to test
            if( position->mPosition.x > 900 )
                entity->Destroy();

            // Add it back at its new position
            entityMap->AddEntity( entity );
        }
    }
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------ Entity
// -------------------------------------------------------------------------------------


void
cSimplePhysics::IncomingEntity( cEntity * iEntity )
{
    auto simplephysic = dynamic_cast< cSimplePhysic* >( iEntity->GetComponentByName( "simplephysic" ) );

    if( simplephysic )
    {
        AcceptEntity( iEntity );
        cGameApplication::App()->EntityMap()->AddEntity( iEntity );

        if( simplephysic->mType == cSimplePhysic::eType::kStatic )
            mStaticEntities.push_back( iEntity );
        else if( simplephysic->mType == cSimplePhysic::eType::kDynamic )
            mDynamicEntities.push_back( iEntity );
    }
}


void
cSimplePhysics::EntityLost( cEntity * iEntity )
{
    // Getting type to quickly know in which vector we should look to remove entity
    auto simplephysic = dynamic_cast< cSimplePhysic* >( iEntity->GetComponentByName( "simplephysic" ) );

    if( simplephysic->mType == cSimplePhysic::eType::kStatic )
    {
        for( int i = 0; i < mStaticEntities.size(); ++i )
        {
            if( mStaticEntities[ i ] == iEntity )
                mStaticEntities.erase( mStaticEntities.begin() + i );
        }
    }
    else if( simplephysic->mType == cSimplePhysic::eType::kDynamic )
    {
        for( int i = 0; i < mDynamicEntities.size(); ++i )
        {
            if( mDynamicEntities[ i ] == iEntity )
                mDynamicEntities.erase( mDynamicEntities.begin() + i );
        }
    }

    tSuperClass::EntityLost( iEntity );
    cGameApplication::App()->EntityMap()->RemoveEntityNotUpdated( iEntity );
}




