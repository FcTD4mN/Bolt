#pragma once


#include <functional>
#include <vector>


namespace nBase {
namespace nThread {


class cThread;
class cThreadHandle;


class cThreadProcessor
{
public:
    // Construction/Destruction
    ~cThreadProcessor();
    cThreadProcessor();

public:
    static cThreadProcessor* Instance();

public:
    void Initialize();
    void Finalize();

public:
    unsigned int GetAvailableThreadCount() const;

public:
    // Thread execution
    cThreadHandle  AffectFunctionToThreadAndStart( std::function< void( int ) > iFunction, bool iBlockant );
    cThreadHandle  AffectFunctionToThreadAndStartAtIndex( std::function< void( int ) > iFunction,  int iIndex, bool iBlockant );

private:
    cThreadHandle SetThreadToWork( int iThreadIndex, std::function< void( int ) > iFunction, int iIndex );

protected:
    std::vector< cThread* >  mThreads;
    unsigned int            mTotalCoreCount;
};

} //nThread
} //nBase

