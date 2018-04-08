#pragma once


#include "Core.ECS.Core.System.h"

#include "Core.Math.Edge.h"


#include <SFML/Graphics.hpp>


#include <atomic>
#include <mutex>
#include <queue>
#include <thread>


namespace nBase { namespace nThread { class cThreadHandle; } }


namespace nECS {


class cSightSystem :
    public cSystem
{
public:
    typedef  cSystem  tSuperClass;

public:
    struct eAssociatedTriangle
    {
        sf::VertexArray     mTriangle;
        std::vector< int >  mVisitedPolygonIndexes;
    };

public:
    virtual  ~cSightSystem();
    cSightSystem();


    // Overrides
public:
    // Init/Finalize
    virtual  void  Initialize() override;
    virtual  void  Finalize() override;

public:
    // Update/Draw
    virtual  void  Draw( sf::RenderTarget* iRenderTarget ) override;
    virtual  void  Update( unsigned int iDeltaTime ) override;

public:
    // Entity
    virtual  void  IncomingEntity( cEntity* iEntity ) override;
    virtual  void  EntityLost( cEntity* iEntity ) override;

private:
    std::vector< cEntity* >         mPointsOfInterest;
    std::vector< cEntity* >         mWatchers;

    sf::FloatRect                   mFOVBBox;
    std::vector< sf::VertexArray >  mTriangles;


    // MultiThread variables
    std::vector< sf::VertexArray >*     mOutputTriangles;
    std::queue< eAssociatedTriangle >*  mTriangleQueue;
    std::vector< sf::VertexArray >      mAllPolygonsInFOV;
    std::vector< ::nBase::nThread::cThreadHandle >  mThreadHandles;
    std::mutex                          mMutex;
    std::condition_variable             mSynchronizeCV;
    std::atomic_int                     mWorkingThreadCount;
    std::atomic_bool                    mFinished;

    // The watcher referential is like this :

    //        /
    //       /
    //      /
    //     /
    //    /
    //   /
    //   \
    //    \
    //     \
    //      \
    //       \
    //        \

    // This ref allows distance sorting : X axis
    //            right to left sorting : angles

    // Angles doesn't even require adjustements, as in this config, they will be sortable as is ( bissectrice being the Y axis, being the angle 0.0 )
    // It means any angle to the "left" of the watcher's bissectrice will be positive, and to the "right" negative.
    // Also, the smaller the angle, the more it is on the right ( -PI/2 is more on the right than 0.0, itself more than PI  etc)


    std::vector< std::vector< sf::VertexArray > >  mFOVDrawer;
};


} // namespace ECS


