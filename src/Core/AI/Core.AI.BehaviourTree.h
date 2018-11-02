#pragma once


#include "Core.ECS.Core.Entity.h"


#include <string>
#include <functional>


namespace nECS { class cEntityHandle; }
namespace nCore  { namespace nECS { namespace nCore { class cComponent; } } }


namespace nCore {
namespace nAI {


class  cBehaviourTree
{
public:
    struct cNodeConnexion
    {
        std::string   mConnexionName;
        cBehaviourTree*  mNode;
        std::function< bool( ::nCore::nECS::nCore::cEntity* ) >  mTransitionCondition;
    };

public:
    /** The destructor */
    ~cBehaviourTree();

    /** The constructor */
    cBehaviourTree( const  std::string&  iNodeID, ::nCore::nECS::nCore::cEntityHandle iHandle );

public:
    // Nodes/Tree management
    void                AddNode( ::nCore::nAI::cBehaviourTree*  iNode, const  std::string&  iConnexionName );
    void                AddNodeConditionnal( ::nCore::nAI::cBehaviourTree*  iNode, const  std::string&  iConnexionName, std::function< bool( ::nCore::nECS::nCore::cEntity* ) > iCondition );
    cBehaviourTree*     TransitionTo( const  std::string&  iNodeID );
    void                ApplyNode();
    void                SyncNode();


public:
    cBehaviourTree*   Update( unsigned int iDeltaTime );

public:
    // Components management
    void                    AddComponentSnapShot( const  std::string&  iComponentName );
    ::nCore::nECS::nCore::cComponent*     GetSnapShotByName( const  std::string&  iComponentName );

public:
    // Logic/Callbacks
    void  SetOnEnterFunction(   std::function< void( ::nCore::nECS::nCore::cEntity* ) > iFunction );
    void  SetOnUpdateFunction(  std::function< void( ::nCore::nECS::nCore::cEntity*, unsigned int ) > iFunction );
    void  SetOnLeavingFunction( std::function< void( ::nCore::nECS::nCore::cEntity* ) > iFunction );

public:
    void  DebugPRINT() const;

private:
    std::string                             mNodeID;

    ::nCore::nECS::nCore::cEntityHandle                   mEntityHandle; //TODO: go array :to allow using the same behaviour tree for multiple entities ( case of IAs );
    std::vector< cNodeConnexion >           mConnexions;
    std::vector< ::nCore::nECS::nCore::cComponent* >      mComponentsSnapShots;

    std::function< void( ::nCore::nECS::nCore::cEntity* ) >                 mOnStateEnter;
    std::function< void( ::nCore::nECS::nCore::cEntity*, unsigned int ) >   mOnStateUpdate;
    std::function< void( ::nCore::nECS::nCore::cEntity* ) >                 mOnStateLeaving;
};


} // namespace nAI
} // namespace nCore

