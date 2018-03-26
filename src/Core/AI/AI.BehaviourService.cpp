
#include "AI.BehaviourNode.h"

namespace nAI {


cBehaviourService::~cBehaviourService()
{
}


cBehaviourService::cBehaviourService(double iTimer, std::function< void(cBlackBoard*) > iFunction) :
	mTimer( iTimer ),
	mFunction( iFunction ),
	mLastTime()
{
}


void
cBehaviourService::Execute(cBlackBoard* ioBlackBoard)
{
	std::chrono::high_resolution_clock::time_point currenttime = std::chrono::high_resolution_clock::now();

	if (mLastTime.time_since_epoch().count() + mTimer < currenttime.time_since_epoch().count())
	{
		mFunction(ioBlackBoard);
		mLastTime = currenttime;
	}
}

}// namespace nAI