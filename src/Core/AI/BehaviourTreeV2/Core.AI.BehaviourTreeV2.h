#pragma once

#include "Core.ECS.Core.Entity.h"

#include <string>

namespace nECS { class cEntityHandle; }
namespace nECS { class cComponent; }


namespace nAI {

class cBehaviourTreeV2
{

public:
    /** The destructor */
    ~cBehaviourTreeV2();

    /** The constructor */
    cBehaviourTreeV2( const std::string& iNodeID, ::nECS::cEntityHandle& iHandle );

public:
    // Nodes/Tree management
    void                AddNode( ::nAI::cBehaviourTreeV2* iNode );
    cBehaviourTreeV2*   TransitionTo( const std::string& iNodeID );
    void                ApplyNode();
    void                SyncNode();

public:
    // Components management
    void  AddComponentSnapShot( const std::string& iComponentName );

private:
    std::string                         mNodeID;

    ::nECS::cEntityHandle               mEntityHandle;
    std::vector< cBehaviourTreeV2* >    mConnectedNodes;
    std::vector< ::nECS::cComponent* >  mComponentsSnapShots;
};

}// namespace nAI

