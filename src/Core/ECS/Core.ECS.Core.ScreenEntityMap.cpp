#include "Core.ECS.Core.ScreenEntityMap.h"

#include "Core.Mapping.PhysicEntityGrid.h"


namespace nECS {

// ========================================================================================
// ================================================================ Contruction/Destruction
// ========================================================================================


nECS::cScreenEntityMap::~cScreenEntityMap()
{
}


nECS::cScreenEntityMap::cScreenEntityMap() :
    mEntityGrid( 0 )
{
}


// ========================================================================================
// =============================================================================== Instance
// ========================================================================================


cScreenEntityMap*
nECS::cScreenEntityMap::Instance()
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
    mEntityGrid = new ::nMapping::cEntityGrid( iWidth, iHeight, iCellSize );
}


void
cScreenEntityMap::Finalize()
{
}


} // nECS


