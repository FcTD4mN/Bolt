#pragma once


#include "Core.AI.BlackBoardVariable.h"


#include <vector>


namespace nCore {
namespace nAI {


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
    void AddVariable( ::nCore::nAI::cBlackBoardVariable*  iVariable );

    /** Removes the variable at iIndex in the service list */
    void RemoveVariable(int iIndex);

    /** Removes all the variables */
    void RemoveAllVariables();

private:
    std::vector< ::nCore::nAI::cBlackBoardVariable* > mVariables;

};


}// namespace nAI
}// namespace nCore

