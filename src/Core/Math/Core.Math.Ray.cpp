#include "Core.Math.Ray.h"


#include "Core.Math.Utils.h"


namespace nCore {
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


} // namespace nMath
} // namespace nCore

