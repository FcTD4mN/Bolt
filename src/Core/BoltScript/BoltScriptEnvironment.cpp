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
        gBoltScriptEnvironment = new cBoltScriptEnvironment( DefaultOutputRedirectionFunction );
        gBoltScriptEnvironment->RegisterFunction("output:native", ResetOutputRedirectionFunction);
        gBoltScriptEnvironment->RegisterFunction("python", [=](void) { PyRun_SimpleString( "print (sys.version)\r\n" ); });
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
    Env()->Print( ">>: Output switching to Native Console \r\n");
    Env()->SetOutputRedirectionFunction( DefaultOutputRedirectionFunction );
    Env()->Print( ">>: Output switched to Native Console \r\n");
}


// -------------------------------------------------------------------------------------
// --------------------------------------------------------- Public Processing Interface
// -------------------------------------------------------------------------------------


void
cBoltScriptEnvironment::ProcessRawString( const  std::string&  iStr )
{
    if( iStr == "" )
    {
        Print( iStr + "\r\n" );
        return;
    }

    Print( iStr + "\r\n" );

    try
    {
        mVoidFuncVoid[ iStr ]();
    }
    catch(const std::exception&)
    {
        PyRun_SimpleString( iStr.c_str() );
        //Print( "ERROR: Couldn't Process Raw String \r\n" );
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

