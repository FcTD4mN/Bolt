#include "Core.ECS.System.BehaviourTreeSystem.h"

#include "Core.ECS.Component.BehaviourTree.h"
#include "Core.AI.BehaviourTreeV2.h"
#include "Core.ECS.Core.Entity.h"


namespace nECS {


cBehaviourTreeSystem::~cBehaviourTreeSystem()
{
}


cBehaviourTreeSystem::cBehaviourTreeSystem() :
    tSuperClass()
{
}


void
cBehaviourTreeSystem::Initialize()
{
}


void
cBehaviourTreeSystem::Finalize()
{
}


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


void
cBehaviourTreeSystem::IncomingEntity( cEntity * iEntity )
{
    auto behaviourTree = iEntity->GetComponentByName( "behaviourtree" );

    if( behaviourTree )
        AcceptEntity( iEntity );
}


}

