#include "Thread-TriangleSpliterProcessor.h"

#include "Base/Utilities.h"
#include "Math/Utils.h"

#include <thread>

// ==========================================================================
// ================================================= Construction/Destruction
// ==========================================================================


cTriangleSplitterProcessor::~cTriangleSplitterProcessor()
{
}


cTriangleSplitterProcessor::cTriangleSplitterProcessor( std::vector< sf::VertexArray >* oSubTriangles, std::queue< eAssociatedTriangle >* iTrianglesToCompute, const std::vector< sf::VertexArray >* iAllPolygons ) :
    mOutSubTriangles( oSubTriangles ),
    mTrianglesToCompute( iTrianglesToCompute ),
    mAllPolygons( iAllPolygons ),
    mTerminate( false )
{
}


// ==========================================================================
// ========================================================= Thread execution
// ==========================================================================


void
cTriangleSplitterProcessor::ThreadMethod()
{
    std::vector< sf::VertexArray > subTriangles;

    while( !mTerminate )
    {
        mMutex.lock();
        if( mTrianglesToCompute->empty() )
        {
            mMutex.unlock();
            std::this_thread::sleep_for( std::chrono::milliseconds( 1 ) );
            continue;
        }

            eAssociatedTriangle assocTriangle = mTrianglesToCompute->front();
            mTrianglesToCompute->pop();
        mMutex.unlock();

        // Did any polygon generate a sub triangle ?
        bool subTrianglesWereGenerated = false;

        for( int i = 0; i < mAllPolygons->size(); ++i )
        {
            if( VectorContains( assocTriangle.mVisitedPolygonIndexes, i ) )
                continue;

            TriangleSubDivisionUsingPolygon( &subTriangles, assocTriangle.mTriangle, mAllPolygons->at( i ) );

            if( subTriangles.size() > 1 )
            {
                // Copying this vector way too much ...
                eAssociatedTriangle assocSubTriangle;
                std::vector< int > masterTrianglePolyTable = assocTriangle.mVisitedPolygonIndexes;
                masterTrianglePolyTable.push_back( i );

                assocSubTriangle.mVisitedPolygonIndexes = masterTrianglePolyTable;

                mMutex.lock();
                for( auto triangle : subTriangles )
                {
                    assocSubTriangle.mTriangle = triangle;
                    mTrianglesToCompute->push( assocSubTriangle );
                }
                mMutex.unlock();

                subTrianglesWereGenerated = true;
                break;
            }
        }
        if( !subTrianglesWereGenerated )
        {
            mMutex.lock();
            mOutSubTriangles->push_back( assocTriangle.mTriangle );
            mMutex.unlock();
        }
    }
}


void
cTriangleSplitterProcessor::Start()
{
    unsigned int coreCount = std::thread::hardware_concurrency();

    for( unsigned int i = 0; i < coreCount; ++i )
    {
        mThreads.push_back( std::thread( &cTriangleSplitterProcessor::ThreadMethod, this ) );
    }
}


void
cTriangleSplitterProcessor::Stop()
{
    mTerminate = true;

    for( int i = 0; i < mThreads.size(); ++i )
    {
        mThreads[ i ].join();
    }
}


void
cTriangleSplitterProcessor::WaitIteration()
{
    while( !mTrianglesToCompute->empty() )
        std::this_thread::sleep_for( std::chrono::milliseconds( 1 ) );
}

