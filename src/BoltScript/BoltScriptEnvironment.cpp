#include "BoltScriptEnvironment.h"


namespace  nBoltScript
{


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------ Construction/Destruction
// -------------------------------------------------------------------------------------


cBoltScriptEnvironment::~cBoltScriptEnvironment()
{
}


cBoltScriptEnvironment::cBoltScriptEnvironment( std::function< void( const  std::string& ) > iOutputRedirectionFunction ) :
    mOutputRedirectionFunction( iOutputRedirectionFunction )
{
}


// -------------------------------------------------------------------------------------
// --------------------------------------------------------- Public Processing Interface
// -------------------------------------------------------------------------------------


void
cBoltScriptEnvironment::ProcessRawString( const  std::string&  iStr )
{
    mOutputRedirectionFunction( iStr );
}


}  // namespace  nBoltScript

