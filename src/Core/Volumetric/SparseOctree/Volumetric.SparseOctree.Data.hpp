#include "Volumetric.SparseOctree.Data.h"


namespace  nVolumetric      {
namespace  nSparseOctree    {


template< eLod2N LOD, typename Atomic >
inline  eLod2N  cData< LOD, Atomic >::LOD()  const
{
    return  LOD;
}


template< eLod2N LOD, typename Atomic >
inline  tSize  cData< LOD, Atomic >::Size()  const
{
    return  tSize( LOD() );
}


template< eLod2N LOD, typename Atomic >
inline  tVolume  cData< LOD, Atomic >::Capacity()  const
{
    return  mCapacity;
}


}  // namespace  nSparseOctree
}  // namespace  nVolumetric

