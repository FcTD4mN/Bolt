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
    mOutputRedirectionFunction( iOutputRedirectionFunction ),
    mVoidFuncVoid()
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
        gBoltScriptEnvironment->RegisterFunction( "default", ResetOutputRedirectionFunction );
    }

    return  gBoltScriptEnvironment;
}



//static
void
cBoltScriptEnvironment::DefaultOutputRedirectionFunction( const  std::string&  iStr )
{
    printf( iStr.c_str() );
}

//static
void
cBoltScriptEnvironment::ResetOutputRedirectionFunction()
{
    std::function< void( const  std::string& )> f = [=]( const  std::string& iStr ) {
            cBoltScriptEnvironment::DefaultOutputRedirectionFunction( iStr );
    };
    cBoltScriptEnvironment::BoltScriptEnvironment()->SetOutputRedirectionFunction( f );
}

// -------------------------------------------------------------------------------------
// --------------------------------------------------------- Public Processing Interface
// -------------------------------------------------------------------------------------


void
cBoltScriptEnvironment::ProcessRawString( const  std::string&  iStr )
{
    try
    {
        mVoidFuncVoid[ iStr ]();
    }
    catch(const std::exception&)
    {
        Print( "Couldn't Process Raw String \r\n" );
    }

    Print( iStr + "\r\n" );
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


// -------------------------------------------------------------------------------------
// ----------------------------------------------------------- Public Register Interface
// -------------------------------------------------------------------------------------


void
cBoltScriptEnvironment::RegisterFunction( const  std::string&  iStr, std::function< void( void ) > iFPtr )
{
    mVoidFuncVoid[ iStr ] = iFPtr;
}


// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------

// Wrapping accessor
cBoltScriptEnvironment*
Env()
{
    return  cBoltScriptEnvironment::BoltScriptEnvironment();
}


}  // namespace  nBoltScript

