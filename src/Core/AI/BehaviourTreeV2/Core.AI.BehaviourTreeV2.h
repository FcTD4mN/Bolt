#pragma once

#include "Core.ECS.Core.Entity.h"

#include <string>
#include <functional>

namespace nECS { class cEntityHandle; }
namespace nECS { class cComponent; }


namespace nAI {

class cBehaviourTreeV2
{
public:
    struct cNodeConnexion
    {
        std::string             mConnexionName;
        cBehaviourTreeV2*       mNode;
        std::function< bool( ::nECS::cEntity* ) > mTransitionCondition;
    };

public:
    /** The destructor */
    ~cBehaviourTreeV2();

    /** The constructor */
    cBehaviourTreeV2( const std::string& iNodeID, ::nECS::cEntityHandle iHandle );

public:
    // Nodes/Tree management
    void                AddNode( ::nAI::cBehaviourTreeV2 * iNode, const std::string& iConnexionName );
    void                AddNodeConditionnal( ::nAI::cBehaviourTreeV2 * iNode, const std::string& iConnexionName, std::function< bool( ::nECS::cEntity* ) > iCondition );
    cBehaviourTreeV2*   TransitionTo( const std::string& iNodeID );
    void                ApplyNode();
    void                SyncNode();


public:
    cBehaviourTreeV2*   Update( unsigned int iDeltaTime );

public:
    // Components management
    void                    AddComponentSnapShot( const std::string& iComponentName );
    ::nECS::cComponent*     GetSnapShotByName( const std::string& iComponentName );

public:
    // Logic/Callbacks
    void  SetOnEnterFunction(   std::function< void( ::nECS::cEntity* ) > iFunction );
    void  SetOnUpdateFunction(  std::function< void( ::nECS::cEntity*, unsigned int ) > iFunction );
    void  SetOnLeavingFunction( std::function< void( ::nECS::cEntity* ) > iFunction );

public:
    void  DebugPRINT() const;

private:
    std::string                             mNodeID;

    ::nECS::cEntityHandle                   mEntityHandle; //TODO: go array :to allow using the same behaviour tree for multiple entities ( case of IAs );
    std::vector< cNodeConnexion >           mConnexions;
    std::vector< ::nECS::cComponent* >      mComponentsSnapShots;

    std::function< void( ::nECS::cEntity* ) >                 mOnStateEnter;
    std::function< void( ::nECS::cEntity*, unsigned int ) >   mOnStateUpdate;
    std::function< void( ::nECS::cEntity* ) >                 mOnStateLeaving;
};

}// namespace nAI

