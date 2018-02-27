#pragma once

#include <iostream>
#include "ECS/World.h"

namespace  nBenchmark
{
	void VectorVsHMapvsMapBenchmark( int iSize, long long* oVecResult, long long* oHMapResult, long long* oMapResult );
	void RunVectorVsHMapvsMapBenchmark();



    void EntityStressTest();


}  // namespace  nBenchmark

