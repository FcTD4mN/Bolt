#pragma once


#include "Core.ECS.Core.World.h"


#include <SFML/Window.hpp>


#include <iostream>


namespace  nBenchmark
{
    void VectorVsHMapvsMapBenchmark( int iSize, long long* oVecResult, long long* oHMapResult, long long* oMapResult );
    void RunVectorVsHMapvsMapBenchmark();



    void EntityStressTest();
    void DrawStressTest( sf::RenderTarget* iRender );


}  // namespace  nBenchmark

