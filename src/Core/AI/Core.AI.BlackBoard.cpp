#include "Core.AI.BlackBoard.h"


namespace nCore {
namespace nAI {


cBlackBoard::~cBlackBoard()
{

}

cBlackBoard::cBlackBoard() :
    mVariables()
{

}

int
cBlackBoard::VariableCount()
{
    return  int( mVariables.size() );
}

void
cBlackBoard::AddVariable( ::nCore::nAI::cBlackBoardVariable*  iVariable )
{
    mVariables.push_back(iVariable);
}

void
cBlackBoard::RemoveVariable( int iIndex )
{
    mVariables.erase( mVariables.begin() + iIndex );
}

void
cBlackBoard::RemoveAllVariables()
{
    mVariables.clear();
}


}// namespace nAI
}// namespace nCore

