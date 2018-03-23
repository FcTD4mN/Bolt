#pragma once

#include <thread>

class cParallelThread
{
public:
    // Construction/Destruction
    ~cParallelThread();
    cParallelThread();

public:
    // Thread execution
    virtual  void Run( int iIndex ) = 0;
    void RunInRange( int iStart, int iEnd );

protected:
    std::thread mThread;
};

