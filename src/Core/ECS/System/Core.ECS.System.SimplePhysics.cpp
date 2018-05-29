 #include "Core.ECS.System.SimplePhysics.h"

#include "Core.ECS.Core.Entity.h"
#include "Core.ECS.Core.ScreenEntityMap.h"

#include "Core.ECS.Component.Position.h"
#include "Core.ECS.Component.SimplePhysic.h"
#include "Core.ECS.Component.Size.h"

#include "Core.Math.Edge.h"
#include "Core.Math.Utils.h"



namespace nECS {


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------ Construction/Destruction
// -------------------------------------------------------------------------------------


cSimplePhysics::~cSimplePhysics()
{
}


cSimplePhysics::cSimplePhysics() :
    tSuperClass(),
    mGlobalGravity( 0.0 )
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
            sf::FloatRect entityHitbox = GetEntityHitBoxAndCenter( 0, entity );

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
            //    auto simplephysicSurr = dynamic_cast< cSimplePhysic* >( surroundingEntity->GetComponentByName( "simplephysic" ) );

            //    sf::VertexArray lines( sf::LinesStrip, 2 );
            //    lines[ 0 ].position = sf::Vector2f( simplephysic->mHitBox.left + simplephysic->mHitBox.width / 2, simplephysic->mHitBox.top + simplephysic->mHitBox.height / 2 );
            //    lines[ 0 ].color = sf::Color( 20, 20, 255, 150 );
            //    lines[ 1 ].position = sf::Vector2f( simplephysicSurr->mHitBox.left + simplephysicSurr->mHitBox.width / 2, simplephysicSurr->mHitBox.top + simplephysicSurr->mHitBox.height / 2 );
            //    lines[ 1 ].color = sf::Color( 20, 20, 255, 150 );

            //    iRenderTarget->draw( lines );
            //}

        }

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
    ::nMapping::cEntityGrid* entityMap = ::nECS::cScreenEntityMap::Instance()->mEntityGrid;

    for( int i = 0; i < mDynamicEntities.size(); ++i )
    {
        cEntity* entity = mDynamicEntities[ i ];
        sf::Vector2f entityCenterPoint;

        auto simplephysic   = dynamic_cast< cSimplePhysic* >( entity->GetComponentByName( "simplephysic" ) );

        entityHitBox = GetEntityHitBoxAndCenter( &entityCenterPoint, entity );

        bool collided = false;

        // Applying gravity
        simplephysic->mVelocity.y += mGlobalGravity * ( iDeltaTime * 1E-6F );

        projection = entityHitBox;
        projection.left += simplephysic->mVelocity.x;
        projection.top += simplephysic->mVelocity.y;

        std::vector< cEntity* > surrounding;
        entityMap->GetSurroundingEntitiesOf( &surrounding, entity, 1 );

        for( int j = 0; j < surrounding.size(); ++j )
        {
            cEntity* surroundingEntity = surrounding[ j ];

            sf::FloatRect surrENtHitBox = GetEntityHitBoxAndCenter( 0, surroundingEntity );

            if( projection.intersects( surrENtHitBox ) )
            {
                collided = true;
                //sf::Vector2f motionVector = sf::Vector2f( projection.left, projection.top ) - sf::Vector2f( entityHitBox.left, entityHitBox.top );

                //sf::VertexArray polygonCradePourTestSiCaMarcheTavu;
                //polygonCradePourTestSiCaMarcheTavu.append( sf::Vector2f( surrENtHitBox.left, surrENtHitBox.top ) );
                //polygonCradePourTestSiCaMarcheTavu.append( sf::Vector2f( surrENtHitBox.left, surrENtHitBox.top + surrENtHitBox.height ) );
                //polygonCradePourTestSiCaMarcheTavu.append( sf::Vector2f( surrENtHitBox.left + surrENtHitBox.width, surrENtHitBox.top + surrENtHitBox.height ) );
                //polygonCradePourTestSiCaMarcheTavu.append( sf::Vector2f( surrENtHitBox.left + surrENtHitBox.width, surrENtHitBox.top ) );

                //::nMath::cEdgeF closestEdge = ::nMath::GetClosestEdgeIntersectingFromPolygon( polygonCradePourTestSiCaMarcheTavu, ::nMath::cEdgeF::MakePointDirection( entityCenterPoint, motionVector ) );
                //mDebugEdge = closestEdge;

                simplephysic->mVelocity.x = 0.0F;
                simplephysic->mVelocity.y = 0.0F;
                break;
            }
        }

        if( !collided && ( simplephysic->mVelocity.x != 0.0F || simplephysic->mVelocity.y != 0.0F ) )
        {
            auto position = dynamic_cast< cPosition* >( entity->GetComponentByName( "position" ) );
            ::nBase::cVariant* positionX = position->GetVar( "x" );
            ::nBase::cVariant* positionY = position->GetVar( "y" );

            // Remove Entity before changing its position, so it's quick and easy
            entityMap->RemoveEntityNotUpdated( entity );

            positionX->SetValueNumber( positionX->GetValueNumber() + simplephysic->mVelocity.x );
            positionY->SetValueNumber( positionY->GetValueNumber() + simplephysic->mVelocity.y );

            // Add it back at its new position
            entityMap->AddEntity( entity );
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
cSimplePhysics::GetEntityHitBoxAndCenter( sf::Vector2f* oCenter, ::nECS::cEntity * iEntity )
{
    auto simplephysic   = dynamic_cast< cSimplePhysic* >( iEntity->GetComponentByName( "simplephysic" ) );
    auto position       = dynamic_cast< cPosition* >( iEntity->GetComponentByName( "position" ) );
    auto size           = dynamic_cast< cSize* >( iEntity->GetComponentByName( "size" ) );

    sf::Vector2f entityCenter = position->AsVector2F();
    if( size )
        entityCenter += size->AsVector2F() / 2.0F;

    if( oCenter )
        *oCenter = entityCenter;

    return  simplephysic->GetAbsoluteHitBoxUsingCenterPosition( entityCenter );
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
        ::nECS::cScreenEntityMap::Instance()->mEntityGrid->AddEntity( iEntity );

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
    ::nECS::cScreenEntityMap::Instance()->mEntityGrid->RemoveEntityNotUpdated( iEntity );
}


} // namespace nECS

