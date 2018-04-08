#include "Core.AI.BehaviourNode.h"


namespace nAI {


cBehaviourNode::~cBehaviourNode()
{
}


cBehaviourNode::cBehaviourNode() :
    mNodes(),
    mServices()
{
}


int
cBehaviourNode::NodeCount()
{
    return  int( mNodes.size() );
}


void
cBehaviourNode::AddNode(::nAI::cBehaviourNode* iNode)
{
    mNodes.push_back(iNode);
}


void
cBehaviourNode::InsertNode(int iIndex, ::nAI::cBehaviourNode* iNode)
{
    mNodes.insert( mNodes.begin() + iIndex, iNode);
}


void
cBehaviourNode::RemoveNode(int iIndex)
{
    mNodes.erase( mNodes.begin() + iIndex );
}


void
cBehaviourNode::RemoveAllNodes()
{
    mNodes.clear();
}


int
cBehaviourNode::ServiceCount()
{
    return  int( mServices.size() );
}


void
cBehaviourNode::AddService(::nAI::cBehaviourService* iService)
{
    mServices.push_back(iService);
}


void
cBehaviourNode::InsertService(int iIndex, ::nAI::cBehaviourService* iService)
{
    mServices.insert(mServices.begin() + iIndex, iService);
}


void
cBehaviourNode::RemoveService(int iIndex)
{
    mServices.erase(mServices.begin() + iIndex);
}


void
cBehaviourNode::RemoveAllServices()
{
    mServices.clear();
}


}// namespace nAI

