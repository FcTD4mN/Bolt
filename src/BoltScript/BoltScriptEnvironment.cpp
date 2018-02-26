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
// ------------------------------------------------------------ Singleton GTRUX accessor
// -------------------------------------------------------------------------------------


// static
cBoltScriptEnvironment*
cBoltScriptEnvironment::BoltScriptEnvironment()
{
    static cBoltScriptEnvironment* gBoltScriptEnvironment = 0;

    if( !gBoltScriptEnvironment )
    {
        std::function< void( const  std::string& )> f = [=]( const  std::string& iStr ) {
            cBoltScriptEnvironment::DefaultOutputRedirectionFunction( iStr );
        };
        gBoltScriptEnvironment = new cBoltScriptEnvironment( f );
    }

    return  gBoltScriptEnvironment;
}



//static
void
cBoltScriptEnvironment::DefaultOutputRedirectionFunction( const  std::string&  iStr )
{
    printf( iStr.c_str() );
}

// -------------------------------------------------------------------------------------
// --------------------------------------------------------- Public Processing Interface
// -------------------------------------------------------------------------------------


void
cBoltScriptEnvironment::ProcessRawString( const  std::string&  iStr )
{
    Print( iStr );

    if( iStr == "BOLT" )
    {
        Print( "xxx  xxxx x    xxxxx" );
        Print( "x x  x  x x      x  " );
        Print( "xxxx x  x x      x  " );
        Print( "x  x x  x x      x  " );
        Print( "xxxx xxxx xxxx   x  " );
    }
}


void
cBoltScriptEnvironment::Print( const  std::string&  iStr )
{
    mOutputRedirectionFunction( iStr );
}


void
cBoltScriptEnvironment::SetOutputRedirectionFunction( std::function<void( const  std::string& )> iOutputRedirectionFunction )
{
    mOutputRedirectionFunction = iOutputRedirectionFunction;
}


}  // namespace  nBoltScript

