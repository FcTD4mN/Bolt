#include "Core.AI.BehaviourTree.h"
#include "Core.ECS.Component.BehaviourTree.h"


namespace nAI {


cBehaviourTree::~cBehaviourTree()
{
}


cBehaviourTree::cBehaviourTree() :
    cBehaviourNode()
{
}


void
cBehaviourTree::AddNode(::nAI::cBehaviourNode* iNode)
{
    if( NodeCount() >= 1 )
        RemoveAllNodes();

    tSuperClass::AddNode(iNode);
}


void
cBehaviourTree::InsertNode(int iIndex, ::nAI::cBehaviourNode* iNode)
{
    if (NodeCount() >= 1)
        RemoveAllNodes();

    tSuperClass::AddNode(iNode);
}


}// namespace nAI

