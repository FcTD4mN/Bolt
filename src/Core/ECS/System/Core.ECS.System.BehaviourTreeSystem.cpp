#include "Core.ECS.System.BehaviourTreeSystem.h"

#include "Core.ECS.Component.BehaviourTree.h"
#include "Core.AI.BehaviourTree.h"
#include "Core.ECS.Core.Entity.h"


namespace nCore {
namespace nECS {
namespace nSystem {


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------ Construction/Destruction
// -------------------------------------------------------------------------------------


cBehaviourTreeSystem::~cBehaviourTreeSystem()
{
}


cBehaviourTreeSystem::cBehaviourTreeSystem() :
    tSuperClass( "BehaviourTreeSystem" )
{
}


cBehaviourTreeSystem::cBehaviourTreeSystem( const cBehaviourTreeSystem & iSys ) :
    tSuperClass( iSys )
{
}


::nCore::nECS::nCore::cSystem*
cBehaviourTreeSystem::Clone() const
{
    return  new cBehaviourTreeSystem( *this );
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------- Update/Draw
// -------------------------------------------------------------------------------------


void
cBehaviourTreeSystem::Update( unsigned int iDeltaTime )
{
    for( int i = 0; i < mEntityGroup.size(); ++i )
    {
        ::nCore::nECS::nCore::cEntity* entity = mEntityGroup[ i ];

        auto behaviourTree = entity->GetComponentByNameAs< ::nCore::nECS::nComponent::cBehaviourTree* >( "behaviourtree" );
        behaviourTree->mBehaviourTree = behaviourTree->mBehaviourTree->Update( iDeltaTime );
    }
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------ Entity
// -------------------------------------------------------------------------------------


void
cBehaviourTreeSystem::IncomingEntity( ::nCore::nECS::nCore::cEntity * iEntity )
{
    auto behaviourTree = iEntity->GetComponentByName( "behaviourtree" );

    if( behaviourTree )
        AcceptEntity( iEntity );
}


} // namespace nSystem
} // namespace nECS
} // namespace nCore

