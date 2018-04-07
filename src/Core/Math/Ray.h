#pragma once

#include "SFML/Graphics.hpp"

#include "Math/Edge.h"

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

} //nMath
