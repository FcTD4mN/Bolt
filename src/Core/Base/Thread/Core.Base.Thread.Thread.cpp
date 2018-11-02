#include "Core.Base.Thread.Thread.h"


#include "Core.Math.Utils.h"


#include <iostream>
#include <chrono>
#include <string>
#include <ctime>


namespace nCore {
namespace nBase {
namespace nThread {

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


std::condition_variable&
cThread::CV()
{
    return  mCV;
}


std::mutex&
cThread::IdleMutex()
{
    return  mIdleMutex;
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


bool
cThread::Locked() const
{
    return  mLocked;
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
    if( mLocked )
        return;

    std::unique_lock< std::mutex > locker( mIdleMutex );
    while( !mLocked )
        mCV.wait( locker ); // equivalent to mCV.wait( locker, [ &mLocked ]() { return  mLocked; } );
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
        if( mThreadFunction )
            mThreadFunction( mThreadFunctionIndex );

        mID = ( mID + 1 ) % 9999; // So it never overflows, 9999 should be enough to kill any handle
        mLocked = true;

        locker.unlock();
        mCV.notify_all();

        mState = kIdle;
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
    if( !mThread )
        return  false;

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


} // nThread
} // nBase
} // nCore

