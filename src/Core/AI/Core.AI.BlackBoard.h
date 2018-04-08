#pragma once


#include "Core.AI.BlackBoardVariable.h"


#include <vector>


namespace nAI {


/*
    BehaviourTree is a BehaviourNode, so we can include behaviourtrees in other behaviourtrees
*/

class cBlackBoard
{
public:
    /** The destructor */
    ~cBlackBoard();

    /** The constructor */
    cBlackBoard();

public:
    /** Returns the Variables Count */
    int VariableCount();

    /** Adds a variable at the end of the variable list */
    void AddVariable(::nAI::cBlackBoardVariable* iVariable);

    /** Removes the variable at iIndex in the service list */
    void RemoveVariable(int iIndex);

    /** Removes all the variables */
    void RemoveAllVariables();

private:
    std::vector< cBlackBoardVariable* > mVariables;

};


}// namespace nAI

