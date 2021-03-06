﻿#include "Core.Base.Thread.ThreadProcessor.h"


#include "Core.Base.Thread.Thread.h"


#include <thread>


// ==========================================================================
// ================================================= Construction/Destruction
// ==========================================================================


namespace nCore {
namespace nBase {
namespace nThread {


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
    mTotalCoreCount = std::thread::hardware_concurrency();
    if( mTotalCoreCount > 1 )
    {
        for( unsigned int i = 0; i < mTotalCoreCount; ++i )
        {
            mThreads.push_back( new ::nCore::nBase::nThread::cThread() );
            mThreads.back()->CreateAndLaunchThread();
        }
    }
}


void
cThreadProcessor::Finalize()
{
    for( int i = 0; i < mThreads.size(); ++i )
    {
        ::nCore::nBase::nThread::cThread* thread = mThreads[ i ];

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


unsigned int
cThreadProcessor::GetAvailableThreadCount() const
{
    unsigned int count = 0;
    for( int i = 0; i < mThreads.size(); ++i )
    {
        if( mThreads[ i ]->Locked() )
            ++count;
    }

    return  count;
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
    if( mTotalCoreCount == 1 )
    {
        iFunction( iIndex );
        return  cThreadHandle( 0 ); // No thread available
    }

    for( int i = 0; i < mThreads.size(); ++i )
    {
        if( mThreads[ i ]->Locked() )
            return  _SetThreadToWork( i, iFunction, iIndex );
    }

    // From here, all thread are busy, we can either be non blocant, and return
    // Or, we can block and wait for a thread
    while( iBlockant )
    {
        for( int i = 0; i < mThreads.size(); ++i )
        {
            if( mThreads[ i ]->Locked() )
                return  _SetThreadToWork( i, iFunction, iIndex );
        }
    }

    return  cThreadHandle( 0 ); // No thread available
}


cThreadHandle
cThreadProcessor::_SetThreadToWork( int iThreadIndex, std::function<void( int )> iFunction, int iIndex )
{
    cThread* thread = mThreads[ iThreadIndex ];
    std::unique_lock< std::mutex > lock( thread->IdleMutex() );

    thread->SetThreadFunction( iFunction, iIndex );

    thread->UnlockThread();
    lock.unlock();
    thread->CV().notify_one();

    return  cThreadHandle( thread );
}


} // nThread
} // nBase
} // nCore

