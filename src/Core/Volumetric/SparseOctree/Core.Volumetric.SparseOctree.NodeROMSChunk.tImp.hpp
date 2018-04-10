#include "Core.Volumetric.SparseOctree.NodeROMSChunk.h"


namespace  nVolumetric      {
namespace  nSparseOctree    {


//----------------------------------------------------------------------------------------------
//------------------------------------------------------------------- Construction / Destruction


template< eLod2N LOD, typename Atomic >
inline  cNodeROMSChunk< LOD, Atomic >::~cNodeROMSChunk()
{
}


template< eLod2N LOD, typename Atomic >
inline  cNodeROMSChunk< LOD, Atomic >::cNodeROMSChunk( const  cROMSConfig*  iROMSConfig, eType iDataStartType, const  Atomic& iStartValue ) :
    cROMSChunk< LOD, Atomic >( iROMSConfig, iDataStartType, iStartValue )
{
}


}  // namespace  nSparseOctree
}  // namespace  nVolumetric

