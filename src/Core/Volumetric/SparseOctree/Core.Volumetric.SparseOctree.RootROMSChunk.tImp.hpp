#include "Core.Volumetric.SparseOctree.RootROMSChunk.h"


#include "Core.Volumetric.SparseOctree.USROCMap.h"


namespace  nVolumetric      {
namespace  nSparseOctree    {


//----------------------------------------------------------------------------------------------
//------------------------------------------------------------------- Construction / Destruction


template< eLod2N LOD, eLod2N Micro, typename Atomic >
inline  cRootROMSChunk< LOD, Micro, Atomic >::~cRootROMSChunk()
{
}


template< eLod2N LOD, eLod2N Micro, typename Atomic >
inline  cRootROMSChunk< LOD, Micro, Atomic >::cRootROMSChunk( cUSROCMap< LOD, Micro, Atomic >* iParent, const  cROMSConfig*  iROMSConfig, eType iDataStartType, const  Atomic& iStartValue ) :
    cROMSChunk< LOD, Atomic >( iROMSConfig, iDataStartType, iStartValue ),
    mParent( iParent )
{
}


}  // namespace  nSparseOctree
}  // namespace  nVolumetric

