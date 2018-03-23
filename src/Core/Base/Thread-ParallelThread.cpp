#include "Thread-ParallelThread.h"


// ==========================================================================
// ================================================= Construction/Destruction
// ==========================================================================


cParallelThread::~cParallelThread()
{
}


cParallelThread::cParallelThread()
{
}


// ==========================================================================
// ========================================================= Thread execution
// ==========================================================================


void
cParallelThread::RunInRange( int iStart, int iEnd )
{
    for( int i = iStart; i < iEnd; ++i )
        Run( i );
}
