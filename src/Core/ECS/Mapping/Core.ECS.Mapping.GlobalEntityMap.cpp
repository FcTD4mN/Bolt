#include "Core.ECS.Mapping.GlobalEntityMap.h"


#include "Core.Mapping.PhysicEntityGrid.h"


namespace nCore {
namespace nECS {
namespace nMapping {


// ========================================================================================
// ================================================================ Contruction/Destruction
// ========================================================================================


cGlobalEntityMap::~cGlobalEntityMap()
{
}


cGlobalEntityMap::cGlobalEntityMap() :
    mEntityGrid( 0 )
{
}


// ========================================================================================
// =============================================================================== Instance
// ========================================================================================


cGlobalEntityMap*
cGlobalEntityMap::Instance()
{
    static cGlobalEntityMap* gGlobalEMap = 0;
    if( !gGlobalEMap )
        gGlobalEMap = new cGlobalEntityMap();

    return  gGlobalEMap;
}


// ========================================================================================
// ========================================================================== Init/Finalize
// ========================================================================================


void
cGlobalEntityMap::Initialize( int iWidth, int iHeight, int iCellSize )
{
    mEntityGrid = new ::nCore::nMapping::cPositionSizeGrid( iWidth, iHeight, iCellSize );
}


void
cGlobalEntityMap::Finalize()
{
}


} // namespace nMapping
} // namespace nECS
} // namespace nCore

