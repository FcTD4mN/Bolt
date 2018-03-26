
#include "AI.BlackBoard.h"

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
	return  mVariables.size();
}

void
cBlackBoard::AddVariable(::nAI::cBlackBoardVariable* iVariable)
{
	mVariables.push_back(iVariable);
}

void
cBlackBoard::RemoveVariable(int iIndex)
{
	mVariables.erase(mVariables.begin() + iIndex);
}

void
cBlackBoard::RemoveAllVariables()
{
	mVariables.clear();
}

}// namespace nAI