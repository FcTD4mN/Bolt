#include "Core.ECS.System.BehaviourTreeSystem.h"

#include "Core.ECS.Component.BehaviourTree.h"
#include "Core.AI.BehaviourTreeV2.h"
#include "Core.ECS.Core.Entity.h"


namespace nECS {


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


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------- Update/Draw
// -------------------------------------------------------------------------------------


void
cBehaviourTreeSystem::Update( unsigned int iDeltaTime )
{
    for( int i = 0; i < mEntityGroup.size(); ++i )
    {
        cEntity* entity = mEntityGroup[ i ];

        auto behaviourTree = dynamic_cast< ::nECS::cBehaviourTree* >( entity->GetComponentByName( "behaviourtree" ) );
        behaviourTree->mBehaviourTree = behaviourTree->mBehaviourTree->Update( iDeltaTime );
    }
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------ Entity
// -------------------------------------------------------------------------------------


void
cBehaviourTreeSystem::IncomingEntity( cEntity * iEntity )
{
    auto behaviourTree = iEntity->GetComponentByName( "behaviourtree" );

    if( behaviourTree )
        AcceptEntity( iEntity );
}


}

