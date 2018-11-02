#include "Core.ECS.Mapping.ScreenEntityMap.h"


#include "Core.Mapping.PhysicEntityGrid.h"


namespace nCore {
namespace nECS {
namespace nMapping {


// ========================================================================================
// ================================================================ Contruction/Destruction
// ========================================================================================


cScreenEntityMap::~cScreenEntityMap()
{
}


cScreenEntityMap::cScreenEntityMap() :
    mEntityGrid( 0 )
{
}


// ========================================================================================
// =============================================================================== Instance
// ========================================================================================


cScreenEntityMap*
cScreenEntityMap::Instance()
{
    static cScreenEntityMap* gScreenEntityMap = 0;
    if( !gScreenEntityMap )
        gScreenEntityMap = new cScreenEntityMap();

    return  gScreenEntityMap;
}


// ========================================================================================
// ========================================================================== Init/Finalize
// ========================================================================================


void
cScreenEntityMap::Initialize( int iWidth, int iHeight, int iCellSize )
{
    mEntityGrid = new ::nCore::nMapping::cPhysicEntityGrid( iWidth, iHeight, iCellSize );
}


void
cScreenEntityMap::Finalize()
{
}


} // namespace nMapping
} // namespace nECS
} // namespace nCore

