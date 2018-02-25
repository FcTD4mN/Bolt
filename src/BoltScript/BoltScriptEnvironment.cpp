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

    if( iStr == "BOLT" )
    {
        mOutputRedirectionFunction( "xxx  xxxx x    xxxxx" );
        mOutputRedirectionFunction( "x x  x  x x      x  " );
        mOutputRedirectionFunction( "xxxx x  x x      x  " );
        mOutputRedirectionFunction( "x  x x  x x      x  " );
        mOutputRedirectionFunction( "xxxx xxxx xxxx   x  " );
    }
}


}  // namespace  nBoltScript

