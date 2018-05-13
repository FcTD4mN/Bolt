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
        std::function< bool() > mTransitionCondition;
    };

public:
    /** The destructor */
    ~cBehaviourTreeV2();

    /** The constructor */
    cBehaviourTreeV2( const std::string& iNodeID, ::nECS::cEntityHandle& iHandle );

public:
    // Nodes/Tree management
    void                AddNode( ::nAI::cBehaviourTreeV2 * iNode, const std::string& iConnexionName );
    void                AddNodeConditionnal( ::nAI::cBehaviourTreeV2 * iNode, const std::string& iConnexionName, std::function< bool() > iCondition );
    cBehaviourTreeV2*   TransitionTo( const std::string& iNodeID );
    void                ApplyNode();
    void                SyncNode();


public:
    cBehaviourTreeV2*   Update( unsigned int iDeltaTime );

public:
    // Components management
    void  AddComponentSnapShot( const std::string& iComponentName );

public:
    // Logic/Callbacks
    void  SetOnEnterFunction( std::function< void() > iFunction );
    void  SetOnUpdateFunction( std::function< void( unsigned int ) > iFunction );
    void  SetOnLeavingFunction( std::function< void() > iFunction );

private:
    std::string                         mNodeID;

    ::nECS::cEntityHandle               mEntityHandle;
    std::vector< cNodeConnexion >       mConnexions;
    std::vector< ::nECS::cComponent* >  mComponentsSnapShots;

    std::function< void() >             mOnStateEnter;
    std::function< void( unsigned int ) >             mOnStateUpdate;
    std::function< void() >             mOnStateLeaving;
};

}// namespace nAI

