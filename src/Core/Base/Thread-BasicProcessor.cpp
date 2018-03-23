#include "Thread-BasicProcessor.h"

#include "Thread-ParallelThread.h"

#include <thread>

// ==========================================================================
// ================================================= Construction/Destruction
// ==========================================================================


cBasicThreadProcessor::~cBasicThreadProcessor()
{
}


cBasicThreadProcessor::cBasicThreadProcessor()
{
}


// ==========================================================================
// ========================================================= Thread execution
// ==========================================================================


void
cBasicThreadProcessor::RunInRange( int iStart, int iEnd )
{
    int totalCount = iEnd - iStart;
    unsigned int coreCount = std::thread::hardware_concurrency();

    int rangePerThread = totalCount / coreCount;
    int leftOver = totalCount % coreCount;

    for( int i = 0; i < totalCount; ++i )
    {
        if( unsigned int(i) >= coreCount )
            break;
    }
}
