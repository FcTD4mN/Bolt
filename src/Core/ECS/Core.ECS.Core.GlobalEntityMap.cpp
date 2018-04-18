#include "Core.ECS.Core.GlobalEntityMap.h"

#include "Core.Mapping.PhysicEntityGrid.h"


namespace nECS {

// ========================================================================================
// ================================================================ Contruction/Destruction
// ========================================================================================


nECS::cGlobalEntityMap::~cGlobalEntityMap()
{
}


nECS::cGlobalEntityMap::cGlobalEntityMap() :
    mEntityGrid( 0 )
{
}


// ========================================================================================
// =============================================================================== Instance
// ========================================================================================


cGlobalEntityMap*
nECS::cGlobalEntityMap::Instance()
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
    mEntityGrid = new ::nMapping::cPositionSizeGrid( iWidth, iHeight, iCellSize );
}


void
cGlobalEntityMap::Finalize()
{
}


} // nECS


