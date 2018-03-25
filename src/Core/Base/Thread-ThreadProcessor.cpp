#include "Thread-ThreadProcessor.h"

#include "Thread-Thread.h"

#include <thread>

// ==========================================================================
// ================================================= Construction/Destruction
// ==========================================================================


cThreadProcessor::~cThreadProcessor()
{
}


cThreadProcessor::cThreadProcessor()
{
}


cThreadProcessor*
cThreadProcessor::Instance()
{
    static cThreadProcessor* gThreadProcessor = 0;
    if( !gThreadProcessor )
    {
        gThreadProcessor = new cThreadProcessor();
        gThreadProcessor->Initialize();
    }

    return  gThreadProcessor;
}


void
cThreadProcessor::Initialize()
{
    unsigned int cpuCores = std::thread::hardware_concurrency();
    for( unsigned int i = 0; i < cpuCores; ++i )
    {
        mThreads.push_back( new cThread() );
        mThreads.back()->CreateAndLaunchThread();
    }
}


void
cThreadProcessor::Finalize()
{
    for( int i = 0; i < mThreads.size(); ++i )
    {
        cThread* thread = mThreads[ i ];

        thread->SetThreadFunction( 0, 0 );
        thread->Stop();

        std::unique_lock< std::mutex > lock( thread->IdleMutex() );
        thread->UnlockThread();
        lock.unlock();
        thread->CV().notify_one();
    }

    for( int i = 0; i < mThreads.size(); ++i )
    {
        mThreads[ i ]->Join();
    }

    for( int i = 0; i < mThreads.size(); ++i )
    {
        delete mThreads[ i ];
    }
}


// ==========================================================================
// ========================================================= Thread execution
// ==========================================================================


cThreadHandle
cThreadProcessor::AffectFunctionToThreadAndStart( std::function< void( int ) > iFunction, bool iBlockant )
{
    return  AffectFunctionToThreadAndStartAtIndex( iFunction, 0, iBlockant );
}


cThreadHandle
cThreadProcessor::AffectFunctionToThreadAndStartAtIndex( std::function<void( int )> iFunction, int iIndex, bool iBlockant )
{
    for( int i = 0; i < mThreads.size(); ++i )
    {
        if( mThreads[ i ]->State() == cThread::eThreadState::kIdle )
            return  SetThreadToWork( i, iFunction, iIndex );
    }

    // From here, all thread are busy, we can either be non blocant, and return
    // Or, we can block and wait for a thread
    if( iBlockant )
        return  SetThreadToWork( 0, iFunction, iIndex );

    return  cThreadHandle( 0 ); // No thread available
}


cThreadHandle
cThreadProcessor::SetThreadToWork( int iThreadIndex, std::function<void( int )> iFunction, int iIndex )
{
    cThread* thread = mThreads[ iThreadIndex ];
    std::unique_lock< std::mutex > lock( thread->IdleMutex() );

    thread->SetThreadFunction( iFunction, iIndex );

    thread->UnlockThread();
    lock.unlock();
    thread->CV().notify_one();

    return  cThreadHandle( thread );
}

