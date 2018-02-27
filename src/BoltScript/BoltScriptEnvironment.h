#pragma once

#include <string>
#include <functional>
#include <unordered_map>


namespace  nBoltScript
{


class  cBoltScriptEnvironment
{
private:
    typedef  void ( *tOutputRedirectionFunction )( const  std::string& );
    typedef  void ( *tAnyFPtr )( ... );

public:
    // Construction/Destruction
    ~cBoltScriptEnvironment();
    cBoltScriptEnvironment( std::function<void( const  std::string& )> iOutputRedirectionFunction );
    cBoltScriptEnvironment( const  cBoltScriptEnvironment& ) = delete; // Not Allowed

public:
    // Singleton GTRUX accessor
    static cBoltScriptEnvironment* BoltScriptEnvironment();
    static void  DefaultOutputRedirectionFunction( const  std::string&  iStr );
    static void  ResetOutputRedirectionFunction();

public:
    // Public Processing Interface
    void  ProcessRawString( const  std::string&  iStr );
    void  Print( const  std::string&  iStr );
    void  SetOutputRedirectionFunction( std::function<void( const  std::string& )> iOutputRedirectionFunction );

public:
    // Public Register Interface
    void  RegisterFunction( const  std::string&  iStr, std::function< void( void ) > iFPtr );

private:
    // Data Members
    std::function<void( const  std::string& )>  mOutputRedirectionFunction;
    std::unordered_map< std::string, std::function< void( void ) > > mVoidFuncVoid;
};


// Wrapping accessor
cBoltScriptEnvironment*  Env();


}  // namespace  nBoltScript

