#include "Core.AI.BlackBoardVariable.h"


namespace nCore {
namespace nAI {


cBlackBoardVariable::~cBlackBoardVariable()
{
}

cBlackBoardVariable::cBlackBoardVariable() :
    mName()
{
}

cBlackBoardVariable::cBlackBoardVariable( const  std::string&  iName ) :
    mName( iName )
{
}

const  std::string&
cBlackBoardVariable::Name()  const
{
    return  mName;
}

void
cBlackBoardVariable::Name( const  std::string&  iName )
{
    mName = iName;
}


}// namespace nAI
}// namespace nCore

