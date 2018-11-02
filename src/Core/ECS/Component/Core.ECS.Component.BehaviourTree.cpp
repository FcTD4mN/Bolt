#include "Core.ECS.Component.BehaviourTree.h"


#include "Core.AI.BehaviourTree.h"


namespace nCore {
namespace nECS {
namespace nComponent {


cBehaviourTree::~cBehaviourTree()
{
}


cBehaviourTree::cBehaviourTree() :
    tSuperClass( "behaviourtree" ),
    mBehaviourTree( 0 )
{
}


cBehaviourTree::cBehaviourTree( ::nCore::nAI::cBehaviourTree* iBehaviourTree ) :
    tSuperClass( "behaviourtree" ),
    mBehaviourTree( iBehaviourTree )
{
}


void
cBehaviourTree::Build()
{
    // nothing
}


::nCore::nECS::nCore::cComponent *
cBehaviourTree::Clone() const
{
    return  new cBehaviourTree( *this );
}


} // namespace nComponent
} // namespace nECS
} // namespace nCore

