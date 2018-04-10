#include "Core.Volumetric.SparseOctree.NodeROMSChunk.h"


#include "Core.Volumetric.SparseOctree.SparseData.h"


namespace  nVolumetric      {
namespace  nSparseOctree    {


//----------------------------------------------------------------------------------------------
//------------------------------------------------------------------- Construction / Destruction


template< eLod2N ParentLOD, eLod2N LOD, typename Atomic >
inline  cNodeROMSChunk< ParentLOD, LOD, Atomic >::~cNodeROMSChunk()
{
}


template< eLod2N ParentLOD, eLod2N LOD, typename Atomic >
inline  cNodeROMSChunk< ParentLOD, LOD, Atomic >::cNodeROMSChunk( cSparseData< ParentLOD, Atomic >* iParent, const  cROMSConfig*  iROMSConfig, eType iDataStartType, const  Atomic& iStartValue ) :
    cROMSChunk< LOD, Atomic >( iROMSConfig, iDataStartType, iStartValue ),
    mParent( iParent )
{
}


}  // namespace  nSparseOctree
}  // namespace  nVolumetric

