#pragma once

#include "SFML/Graphics.hpp"

#include <mutex>
#include <queue>
#include <thread>
#include <vector>

class cTriangleSplitterProcessor
{
public:
    struct eAssociatedTriangle
    {
        sf::VertexArray     mTriangle;
        std::vector< int >  mVisitedPolygonIndexes;
    };

public:
    // Construction/Destruction
    ~cTriangleSplitterProcessor();
    cTriangleSplitterProcessor( std::vector< sf::VertexArray >* oSubTriangles, std::queue< eAssociatedTriangle >* iTrianglesToCompute, const std::vector< sf::VertexArray >* iAllPolygons );

public:
    // Thread execution
    void ThreadMethod();
    void Start();
    void Stop();
    void WaitIteration();

protected:
    std::vector< std::thread >              mThreads;
    std::mutex                              mMutex;

    std::vector< sf::VertexArray >*         mOutSubTriangles;
    std::queue< eAssociatedTriangle >*      mTrianglesToCompute;
    const std::vector< sf::VertexArray >*   mAllPolygons;

    bool  mTerminate;
};

