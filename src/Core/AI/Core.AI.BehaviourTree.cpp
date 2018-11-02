#include "Core.AI.BehaviourTree.h"


#include "Core.ECS.Core.Component.h"


namespace nCore {
namespace nAI {


cBehaviourTree::~cBehaviourTree()
{
}


cBehaviourTree::cBehaviourTree( const  std::string&  iNodeID, ::nCore::nECS::nCore::cEntityHandle iHandle ) :
    mNodeID( iNodeID ),
    mEntityHandle( iHandle ),
    mOnStateEnter( 0 ),
    mOnStateUpdate( 0 ),
    mOnStateLeaving( 0 )
{
}


void
cBehaviourTree::AddNode( ::nCore::nAI::cBehaviourTree*  iNode, const  std::string&  iConnexionName )
{
    cNodeConnexion connexion;
    connexion.mConnexionName = iConnexionName;
    connexion.mNode = iNode;
    connexion.mTransitionCondition = 0;

    mConnexions.push_back( connexion );
}


void
cBehaviourTree::AddNodeConditionnal( ::nCore::nAI::cBehaviourTree* iNode, const  std::string&  iConnexionName, std::function<bool( ::nCore::nECS::nCore::cEntity* )> iCondition )
{
    cNodeConnexion connexion;
    connexion.mConnexionName = iConnexionName;
    connexion.mNode = iNode;
    connexion.mTransitionCondition = iCondition;

    mConnexions.push_back( connexion );
}


cBehaviourTree*
cBehaviourTree::TransitionTo( const  std::string&  iNodeID )
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
cBehaviourTree::ApplyNode()
{
    if( mNodeID == "idle" )
        int a = 1;

    //CHECK:
    DebugPRINT();

    if( !mEntityHandle.IsHandleValid() )
        SyncNode();

    if( mOnStateEnter )
        mOnStateEnter( mEntityHandle.GetEntity() );

    for( auto comp : mComponentsSnapShots )
        mEntityHandle.GetEntity()->SetComponent( comp->Clone() );
}


void
cBehaviourTree::SyncNode()
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


cBehaviourTree*
cBehaviourTree::Update( unsigned int iDeltaTime )
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
cBehaviourTree::AddComponentSnapShot( const  std::string&  iComponentName )
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


::nCore::nECS::nCore::cComponent*
cBehaviourTree::GetSnapShotByName( const  std::string&  iComponentName )
{
    for( auto comp : mComponentsSnapShots )
    {
        if( comp->Name() == iComponentName )
            return  comp;
    }

    return  0;
}

void
cBehaviourTree::SetOnEnterFunction( std::function< void( ::nCore::nECS::nCore::cEntity* ) > iFunction )
{
    mOnStateEnter = iFunction;
}


void
cBehaviourTree::SetOnUpdateFunction( std::function< void( ::nCore::nECS::nCore::cEntity*, unsigned int ) > iFunction )
{
    mOnStateUpdate = iFunction;
}


void
cBehaviourTree::SetOnLeavingFunction( std::function< void( ::nCore::nECS::nCore::cEntity* ) > iFunction )
{
    mOnStateLeaving = iFunction;
}


void
cBehaviourTree::DebugPRINT() const
{
    printf( "%s\n", mNodeID.c_str() );
}


} // namespace nAI
} // namespace nCore

