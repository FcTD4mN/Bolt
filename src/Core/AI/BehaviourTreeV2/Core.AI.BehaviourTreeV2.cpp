#include "Core.AI.BehaviourTreeV2.h"

#include "Core.ECS.Core.Component.h"


namespace nAI {


cBehaviourTreeV2::~cBehaviourTreeV2()
{
}


cBehaviourTreeV2::cBehaviourTreeV2( const std::string& iNodeID, ::nECS::cEntityHandle& iHandle ) :
    mNodeID( iNodeID ),
    mEntityHandle( iHandle )
{
}


void
cBehaviourTreeV2::AddNode( ::nAI::cBehaviourTreeV2 * iNode )
{
    mConnectedNodes.push_back( iNode );
}


cBehaviourTreeV2*
cBehaviourTreeV2::TransitionTo( const std::string & iNodeID )
{
    for( auto node : mConnectedNodes )
    {
        if( node->mNodeID == iNodeID )
        {
            return  node;
        }
    }
    return  0;
}


void
cBehaviourTreeV2::ApplyNode()
{
    if( mEntityHandle.IsHandleValid() )
    {
        for( auto comp : mComponentsSnapShots )
        {
            mEntityHandle.GetEntity()->SetComponent( comp->Clone() );
        }
    }
    else
    {
        SyncNode();
    }
}


void
cBehaviourTreeV2::SyncNode()
{
    mEntityHandle.SyncHandle();

    for( size_t i = mComponentsSnapShots.size() - 1; i >= 0; --i )
    {
        auto comp = mComponentsSnapShots[ i ];

        if( mEntityHandle.GetEntity()->GetComponentByName( comp->Name() ) == nullptr )
        {
            mComponentsSnapShots.erase( mComponentsSnapShots.begin() + i );
            delete  comp;
        }
    }
}


void
cBehaviourTreeV2::AddComponentSnapShot( const std::string & iComponentName )
{
    if( mEntityHandle.IsHandleValid() )
    {
        // If already snapshot, we delete the snap and put the new one
        for( auto comp : mComponentsSnapShots )
        {
            if( comp->Name() == iComponentName )
            {
                delete  comp;
                break;
            }
        }

        mComponentsSnapShots.push_back( mEntityHandle.GetEntity()->GetComponentByName( iComponentName )->Clone() );
    }
    else
    {
        SyncNode();
    }
}

} //nAI
