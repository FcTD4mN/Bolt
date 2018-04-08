#pragma once


#include "Core.Math.Edge.h"


#include <SFML/Graphics.hpp>


namespace nMath {


class cRay
{
public:
    enum eRayType
    {
        kBasicRay,
        kFovSide
    };

public:
    // Contruction/Destruction
    ~cRay();
    cRay( const cEdgeF& iEdge, eRayType iRayType );

public:
    cEdgeF      mRay;
    eRayType    mRayType;

};


} // namespace nMath

