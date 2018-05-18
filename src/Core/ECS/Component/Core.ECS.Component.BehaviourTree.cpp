#include "Core.ECS.Component.BehaviourTree.h"

#include "Core.AI.BehaviourTreeV2.h"

namespace nECS
{


cBehaviourTree::~cBehaviourTree()
{
}


cBehaviourTree::cBehaviourTree() :
    tSuperClass( "behaviourtree" ),
    mBehaviourTree( 0 )
{
}


cBehaviourTree::cBehaviourTree( ::nAI::cBehaviourTreeV2* iBehaviourTree ) :
    tSuperClass( "behaviourtree" ),
    mBehaviourTree( iBehaviourTree )
{
}


void
cBehaviourTree::Build()
{
    // nothing
}


cComponent *
cBehaviourTree::Clone()
{
    return  new cBehaviourTree( *this );
}


}
