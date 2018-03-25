#pragma once

#include "AI.BehaviourNode.h"
#include "AI.BlackBoard.h"

namespace nAI {

/*
	BehaviourTree is a BehaviourNode, so we can include behaviourtrees in other behaviourtrees
*/

class cBehaviourTree :
	public ::nAI::cBehaviourNode
{
public:
	/** The destructor */
	~cBehaviourTree();

	/** The constructor */
	cBehaviourTree();

public:
	/** Connects iNode to the Root Node, only one node can be connected to the root node */
	virtual void AddNode( ::nAI::cBehaviourNode* iNode ) override;

	/** Connects iNode to the Root Node, only one node can be connected to the root node */
	virtual void InsertNode( int iIndex, ::nAI::cBehaviourNode* iNode ) override;

private:
	//cBlackBoard mBlackBoard;
};

}// namespace nAI