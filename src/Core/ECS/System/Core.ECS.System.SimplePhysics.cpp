#include "Core.ECS.System.SimplePhysics.h"


#include "Core.ECS.Core.Entity.h"
#include "Core.ECS.Core.World.h"
#include "Core.ECS.Component.Transformation.h"
#include "Core.ECS.Component.SimplePhysic.h"
#include "Core.Render.Layer.h"
#include "Core.Math.Edge.h"
#include "Core.Math.Utils.h"

#include <cassert>

namespace nCore {
namespace nECS {
namespace nSystem {


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------ Construction/Destruction
// -------------------------------------------------------------------------------------


cSimplePhysics::~cSimplePhysics()
{
}


cSimplePhysics::cSimplePhysics() :
    tSuperClass( "SimplePhysics" ),
    mGlobalGravity( 0.0 )
{
}


cSimplePhysics::cSimplePhysics( const cSimplePhysics & iSys ) :
    tSuperClass( iSys )
{
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------- Update/Draw
// -------------------------------------------------------------------------------------


::nCore::nECS::nCore::cSystem*
cSimplePhysics::Clone() const
{
    return  new cSimplePhysics( *this );
}


void
cSimplePhysics::DrawEntity( sf::RenderTarget* iRenderTarget, ::nCore::nECS::nCore::cEntity* iEntity )
{
#ifdef _DEBUG
    if( 1 ) // Cuz this is really cost heavy
    {
        sf::RectangleShape rect( sf::Vector2f( 10, 10 ) );

        //auto simplephysic = dynamic_cast< cSimplePhysic* >( iEntity->GetComponentByID( "simplephysic" ) );
        sf::FloatRect entityHitbox = GetEntityHitBoxAndCenter( 0, iEntity );

        // DEBUG Hitbox Drawing
        rect.setSize( sf::Vector2f( entityHitbox.width, entityHitbox.height ) );
        rect.setPosition( sf::Vector2f( entityHitbox.left, entityHitbox.top ) );
        rect.setFillColor( sf::Color( 255, 50, 50, 100 ) );

        iRenderTarget->draw( rect );

        // DEBUG Surrounding Drawing
        //std::vector< cEntity* > surrounding = cGameApplication::App()->EntityMap()->GetSurroundingEntitiesOf( entity );
        //for( int j = 0; j < surrounding.size(); ++j )
        //{
        //    cEntity* surroundingEntity = surrounding[ j ];
        //    auto simplephysicSurr = dynamic_cast< cSimplePhysic* >( surroundingEntity->GetComponentByID( "simplephysic" ) );

        //    sf::VertexArray lines( sf::LinesStrip, 2 );
        //    lines[ 0 ].position = sf::Vector2f( simplephysic->mHitBox.left + simplephysic->mHitBox.width / 2, simplephysic->mHitBox.top + simplephysic->mHitBox.height / 2 );
        //    lines[ 0 ].color = sf::Color( 20, 20, 255, 150 );
        //    lines[ 1 ].position = sf::Vector2f( simplephysicSurr->mHitBox.left + simplephysicSurr->mHitBox.width / 2, simplephysicSurr->mHitBox.top + simplephysicSurr->mHitBox.height / 2 );
        //    lines[ 1 ].color = sf::Color( 20, 20, 255, 150 );

        //    iRenderTarget->draw( lines );
        //}

        //sf::VertexArray closestLineDebug( sf::Lines );
        //closestLineDebug.append( mDebugEdge.mPoint );
        //closestLineDebug.append( mDebugEdge.mPoint + mDebugEdge.mDirection );
        //closestLineDebug[ 0 ].color = sf::Color::Blue;
        //closestLineDebug[ 1 ].color = sf::Color::Blue;

        //iRenderTarget->draw( closestLineDebug );
    }

#endif // _DEBUG
}


void
cSimplePhysics::Update( unsigned int iDeltaTime )
{
    sf::Rect< float > entityHitBox;
    sf::Rect< float > projection;
    ::nCore::nMapping::cEntityMap* entityMap = 0;

    for( int i = 0; i < mEntityGroup.size(); ++i )
    {
        ::nCore::nECS::nCore::cEntity* entity = mEntityGroup[ i ];
        auto simplephysic = entity->GetComponentByIDAs< ::nCore::nECS::nComponent::cSimplePhysic* >( "simplephysic" );

        if( simplephysic->PhysicType() == ::nCore::nECS::nComponent::cSimplePhysic::kStatic )
            continue;

        auto layer = entity->Layer();
        assert( layer );
        if( layer )
            entityMap = layer->EntityMap();
        else
            return;

        sf::Vector2f entityCenterPoint;
        entityHitBox = GetEntityHitBoxAndCenter( &entityCenterPoint, entity );

        bool blockingCollision = false;

        // Applying gravity
        simplephysic->mVelocity.y += mGlobalGravity * ( float( iDeltaTime ) * 1E-6F ) * float( simplephysic->GravityFactor() );

        projection = entityHitBox;
        projection.left += simplephysic->mVelocity.x;
        projection.top += simplephysic->mVelocity.y;

        std::set< ::nCore::nECS::nCore::cEntity* > surrounding;
        entityMap->GetSurroundingEntitiesOf( &surrounding, entity, 1 );

        for( auto it = surrounding.begin(); it != surrounding.end(); ++it )
        {
            ::nCore::nECS::nCore::cEntity* surroundingEntity = *it;

            sf::FloatRect surrENtHitBox = GetEntityHitBoxAndCenter( 0, surroundingEntity );

            if( projection.intersects( surrENtHitBox ) )
            {
                auto colliderPhysics = entity->GetComponentByIDAs< ::nCore::nECS::nComponent::cSimplePhysic* >( "simplephysic" );
                if( !colliderPhysics )
                    break;

                // If trigger, we can pass through, and we just call CB, otherwise, we block
                if( !colliderPhysics->IsTrigger() && !simplephysic->IsTrigger() )
                {
                    simplephysic->mVelocity.x = 0.0F;
                    simplephysic->mVelocity.y = 0.0F;
                    blockingCollision = true;
                }

                // Collision callbacks for both entities
                colliderPhysics->CallCollisionCB( entity );
                simplephysic->CallCollisionCB( surroundingEntity );

                break;
            }
        }

        if( !blockingCollision && ( simplephysic->mVelocity.x != 0.0F || simplephysic->mVelocity.y != 0.0F ) )
        {
            auto transformation = entity->GetComponentByIDAs< ::nCore::nECS::nComponent::cTransformation* >( "transformation" );
            ::nCore::nBase::cVariant* positionX = transformation->GetVar( "x" );
            ::nCore::nBase::cVariant* positionY = transformation->GetVar( "y" );

            positionX->SetValueNumber( positionX->GetValueNumber() + simplephysic->mVelocity.x );
            positionY->SetValueNumber( positionY->GetValueNumber() + simplephysic->mVelocity.y );

            // Add it back at its new position
            simplephysic->InvalidCache();
        }
    }
}


void
cSimplePhysics::SetGravity( float iGravity )
{
    mGlobalGravity = iGravity;
}


sf::FloatRect
cSimplePhysics::GetEntityHitBoxAndCenter( sf::Vector2f* oCenter, ::nCore::nECS::nCore::cEntity * iEntity )
{
    auto simplephysic   = iEntity->GetComponentByIDAs< ::nCore::nECS::nComponent::cSimplePhysic* >( "simplephysic" );
    auto transformation = iEntity->GetComponentByIDAs< ::nCore::nECS::nComponent::cTransformation* >( "transformation" );

    sf::Vector2f entityCenter = transformation->PositionAsVector2F() + transformation->SizeAsVector2F() / 2.0F;

    if( oCenter )
        *oCenter = entityCenter;

    return  simplephysic->GetAbsoluteHitBoxUsingCenterPosition( entityCenter );
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------ Entity
// -------------------------------------------------------------------------------------


void
cSimplePhysics::IncomingEntity( ::nCore::nECS::nCore::cEntity*  iEntity )
{
    auto simplephysic = iEntity->GetComponentByID( "simplephysic" );

    if( simplephysic )
    {
        AcceptEntity( iEntity );
    }
}


} // namespace nSystem
} // namespace nECS
} // namespace nCore

