#pragma once


#include <functional>
#include <mutex>
#include <thread>


namespace nBase {
namespace nThread {


class cThread
{
public:
    enum eThreadState
    {
        kIdle,
        kBusy
    };

public:
    // Construction/Destruction
    ~cThread();
    cThread();

public:
    // Accessors
    void            SetThreadFunction( std::function< void( int ) > iFunction, int iFuncIndex );

    std::mutex&     IdleMutex();
    std::condition_variable& CV();
    void            UnlockThread();

    unsigned int    ID() const;
    eThreadState    State() const;

    bool            Locked() const;


public:
    // Thread operations
    void CreateAndLaunchThread();
    void Stop();
    void Join();
    void WaitEndOfTask();

private:
    // Private functions
    void RunningFunction();

protected:
    std::thread             mThread;
    unsigned int            mID;

    std::mutex              mIdleMutex;
    std::condition_variable mCV;

    std::function< void( int ) >    mThreadFunction;
    int                             mThreadFunctionIndex;

    eThreadState            mState;
    bool                    mLocked;
    bool                    mRunning;

};


//=======================================================================================
//=======================================================================================
//=======================================================================================


class cThreadHandle
{
public:
    ~cThreadHandle();
    cThreadHandle( cThread* iThread );

public:
    bool IsValid() const;
    cThread* GetThread();

private:
    cThread * mThread;
    unsigned int mThreadID;

};


} // nThread
} // nBase

