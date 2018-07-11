#include "Core.AI.BehaviourTreeV2.h"

#include "Core.ECS.Core.Component.h"


namespace nAI {


cBehaviourTreeV2::~cBehaviourTreeV2()
{
}


cBehaviourTreeV2::cBehaviourTreeV2( const std::string& iNodeID, ::nECS::cEntityHandle iHandle ) :
    mNodeID( iNodeID ),
    mEntityHandle( iHandle ),
    mOnStateEnter( 0 ),
    mOnStateUpdate( 0 ),
    mOnStateLeaving( 0 )
{
}


void
cBehaviourTreeV2::AddNode( ::nAI::cBehaviourTreeV2 * iNode, const std::string& iConnexionName )
{
    cNodeConnexion connexion;
    connexion.mConnexionName = iConnexionName;
    connexion.mNode = iNode;
    connexion.mTransitionCondition = 0;

    mConnexions.push_back( connexion );
}


void
cBehaviourTreeV2::AddNodeConditionnal( ::nAI::cBehaviourTreeV2 * iNode, const std::string & iConnexionName, std::function<bool( ::nECS::cEntity* )> iCondition )
{
    cNodeConnexion connexion;
    connexion.mConnexionName = iConnexionName;
    connexion.mNode = iNode;
    connexion.mTransitionCondition = iCondition;

    mConnexions.push_back( connexion );
}


cBehaviourTreeV2*
cBehaviourTreeV2::TransitionTo( const std::string & iNodeID )
{
    for( auto connexion : mConnexions )
    {
        if( connexion.mConnexionName == iNodeID )
        {
            if( !mEntityHandle.IsHandleValid() )
                SyncNode();

            if( mOnStateLeaving )
                mOnStateLeaving( mEntityHandle.GetEntity() );

            connexion.mNode->ApplyNode();
            return  connexion.mNode;
        }
    }
    return  0;
}


void
cBehaviourTreeV2::ApplyNode()
{
    if( mNodeID == "idle" )
        int a = 1;
    DebugPRINT();
    if( !mEntityHandle.IsHandleValid() )
        SyncNode();

    if( mOnStateEnter )
        mOnStateEnter( mEntityHandle.GetEntity() );

    for( auto comp : mComponentsSnapShots )
        mEntityHandle.GetEntity()->SetComponent( comp->Clone() );
}


void
cBehaviourTreeV2::SyncNode()
{
    mEntityHandle.SyncHandle();

    for( int i = int(mComponentsSnapShots.size()) - 1; i >= 0; --i )
    {
        auto comp = mComponentsSnapShots[ i ];

        if( mEntityHandle.GetEntity()->GetComponentByName( comp->Name() ) == nullptr )
        {
            mComponentsSnapShots.erase( mComponentsSnapShots.begin() + i );
            delete  comp;
        }
    }
}


cBehaviourTreeV2*
cBehaviourTreeV2::Update( unsigned int iDeltaTime )
{
    if( !mEntityHandle.IsHandleValid() )
        SyncNode();

    for( auto connexion : mConnexions )
    {
        if( connexion.mTransitionCondition && connexion.mTransitionCondition( mEntityHandle.GetEntity() ) )
        {
            // Code duplicated to avoid the for loop in transitionTo again ...
            if( mOnStateLeaving )
                mOnStateLeaving( mEntityHandle.GetEntity() );

            connexion.mNode->ApplyNode();
            return  connexion.mNode;
        }
    }

    if( mOnStateUpdate )
        mOnStateUpdate( mEntityHandle.GetEntity(), iDeltaTime );

    return  this;
}


void
cBehaviourTreeV2::AddComponentSnapShot( const std::string & iComponentName )
{
    if( !mEntityHandle.IsHandleValid() )
        SyncNode();

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


::nECS::cComponent*
cBehaviourTreeV2::GetSnapShotByName( const std::string & iComponentName )
{
    for( auto comp : mComponentsSnapShots )
    {
        if( comp->Name() == iComponentName )
            return  comp;
    }

    return  0;
}

void
cBehaviourTreeV2::SetOnEnterFunction( std::function< void( ::nECS::cEntity* ) > iFunction )
{
    mOnStateEnter = iFunction;
}


void
cBehaviourTreeV2::SetOnUpdateFunction( std::function< void( ::nECS::cEntity*, unsigned int ) > iFunction )
{
    mOnStateUpdate = iFunction;
}


void
cBehaviourTreeV2::SetOnLeavingFunction( std::function< void( ::nECS::cEntity* ) > iFunction )
{
    mOnStateLeaving = iFunction;
}


void
cBehaviourTreeV2::DebugPRINT() const
{
    printf( "%s\n", mNodeID.c_str() );
}




} //nAI
