#include "Ray.h"


#include "Math/Utils.h"

namespace nMath {

// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------ Construction
// -------------------------------------------------------------------------------------


cRay::~cRay()
{
}


cRay::cRay( const cEdgeF& iEdge, eRayType iRayType ) :
    mRay( iEdge ),
    mRayType( iRayType )
{
}

} //nMath
