#include "Thread-Thread.h"

#include <iostream>

// ==========================================================================
// ================================================= Construction/Destruction
// ==========================================================================


cThread::~cThread()
{
}


cThread::cThread() :
    mID( 0 ),
    mThreadFunction( 0 ),
    mThreadFunctionIndex( -1 ),
    mState( kIdle ),
    mLocked( true ),
    mRunning( false )
{
}


// ==========================================================================
// ================================================================ Accessors
// ==========================================================================


void
cThread::SetThreadFunction( std::function<void( int )> iFunction, int iFuncIndex )
{
    mThreadFunction = iFunction;
    mThreadFunctionIndex = iFuncIndex;
}


std::mutex&
cThread::IdleMutex()
{
    return  mIdleMutex;
}


std::condition_variable&
cThread::CV()
{
    return  mCV;
}


void
cThread::UnlockThread()
{
    mLocked = false;
}


cThread::eThreadState
cThread::State() const
{
    return  mState;
}


unsigned int
cThread::ID() const
{
    return  mID;
}


// ==========================================================================
// ======================================================== Thread operations
// ==========================================================================


void
cThread::CreateAndLaunchThread()
{
    mRunning = true;
    mThread = std::thread( &cThread::RunningFunction, this );
}


void
cThread::Stop()
{
    mRunning = false;
}


void
cThread::Join()
{
    mThread.join();
}


void
cThread::WaitEndOfTask()
{
    std::unique_lock< std::mutex > locker( mIdleMutex );
    while( mState != kIdle )
        mCV.wait( locker ); // equivalent to mCV.wait( locker, [ &mLocked ]() { return  mState == kIdle; } );
}


// ==========================================================================
// =======================================================  Private functions
// ==========================================================================


void
cThread::RunningFunction()
{
    while( mRunning )
    {
        std::unique_lock< std::mutex > locker( mIdleMutex ); // This mutex is used to block the thread when not needed, by the thread manager

        while( mLocked )
            mCV.wait( locker ); // equivalent to mCV.wait( locker, [ &mLocked ]() { return  !mLocked; } );

        mState = kBusy;
        std::cout << " ThreadID : " << mThread.get_id() << std::endl;
        if( mThreadFunction )
            mThreadFunction( mThreadFunctionIndex );

        mState = kIdle;
        mID = ( mID + 1 ) % 9999; // So id never overflows, 9999 should be enough to kill any handle
        mLocked = true;

        locker.unlock();
        mCV.notify_all();
    }
}


// =========================================================================================================================
// =========================================================================================================================
// ============================  Thread Handle =============================================================================
// =========================================================================================================================
// =========================================================================================================================


// ==========================================================================
// ================================================= Construction/Destruction
// ==========================================================================


cThreadHandle::~cThreadHandle()
{
}


cThreadHandle::cThreadHandle( cThread* iThread ) :
    mThread( iThread ),
    mThreadID( -1 )
{
    if( iThread )
        mThreadID = iThread->ID();
}


bool
cThreadHandle::IsValid() const
{
    return  mThreadID == mThread->ID();
}


cThread*
cThreadHandle::GetThread()
{
    if( IsValid() )
        return  mThread;
    else
        return  0;
}
