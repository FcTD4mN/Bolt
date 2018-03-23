#pragma once

#include <vector>

class cParallelThread;

class cBasicThreadProcessor
{
public:
    // Construction/Destruction
    ~cBasicThreadProcessor();
    cBasicThreadProcessor();

public:
    // Thread execution
    void RunInRange( int iStart, int iEnd );

protected:
    std::vector< cParallelThread >  mThreads;
};

