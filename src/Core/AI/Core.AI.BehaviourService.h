#pragma once

#include "Core.AI.BlackBoard.h"
#include <functional>
#include <chrono>

namespace nAI {

/*
    BehaviourService is a linked to a behaviour node and executed while the node is active before any children node is called
*/

class cBehaviourService
{
public:
    /** The destructor */
    ~cBehaviourService();

    /** The constructor */
    cBehaviourService( double iTimer, std::function< void(cBlackBoard*) > iFunction );

public:
    /** Executes the function taking the timer in account */
    void Execute( cBlackBoard* ioBlackBoard );

private:
    double mTimer; // sec between each function tick ( 0 means always tick the function )
    std::function< void(cBlackBoard*) > mFunction;

    std::chrono::high_resolution_clock::time_point mLastTime;
};

}// namespace nAI

