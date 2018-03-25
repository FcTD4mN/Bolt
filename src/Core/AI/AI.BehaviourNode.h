#pragma once

#include "AI.BehaviourService.h"
#include <vector>

namespace nAI {

/*
	BehaviourNode is the base of the BahaviourTree, it can contain nodes but also services
	services executes at their own timing, while the node is active, and before any node is executed
*/

class cBehaviourNode
{
public:
	/** The destructor */
	~cBehaviourNode();

	/** The constructor */
	cBehaviourNode();

public:
	/** Returns the Node Count */
	int NodeCount();

	/** Adds a Node at the end of the node list */
	virtual void AddNode( ::nAI::cBehaviourNode* iNode );

	/** Inserts a Node at iIndex in the node list */
	virtual void InsertNode( int iIndex, ::nAI::cBehaviourNode* iNode );

	/** Removes the node at iIndex in the node list */
	virtual void RemoveNode(int iIndex);

	/** Removes all the nodes */
	virtual void RemoveAllNodes();

public:
	/** Returns the Service Count */
	int ServiceCount();

	/** Adds a Service at the end of the service list */
	virtual void AddService(::nAI::cBehaviourService* iService);

	/** Inserts a service at iIndex in the service list */
	virtual void InsertService(int iIndex, ::nAI::cBehaviourService* iService);

	/** Removes the service at iIndex in the service list */
	virtual void RemoveService(int iIndex);
	
	/** Removes all the services */
	virtual void RemoveAllServices();

public:
	/** Executes the node ( the services and then the node itself ) */
	tErrorCode Execute(double iDeltaTime, cBlackBoard* ioBlackBoard);

protected:
	/** Executes only the node itself, not the services */
	virtual tErrorCode ExecuteNode(double iDeltaTime, cBlackBoard* ioBlackBoard) = 0;

private:
	/** Executes the services only not the node */
	tErrorCode ExecuteServices(double iDeltaTime, cBlackBoard* ioBlackBoard);

private:
	std::vector< cBehaviourNode* > mNodes;
	std::vector< cBehaviourService* > mServices;
};

}// namespace nAI