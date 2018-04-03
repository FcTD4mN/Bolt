#include "Volumetric.SparseOctree.USROCMap.h"


namespace  nVolumetric      {
namespace  nSparseOctree    {


template< eLod2N LOD, typename Atomic >
inline  cUSROCMap< LOD, Atomic>::~cUSROCMap()
{
}


template< eLod2N LOD, typename Atomic >
inline  cUSROCMap< LOD, Atomic >::cUSROCMap() :
    mROMSConfig( cROMSConfig() ),
    mChunks()
{
}


template< eLod2N LOD, typename Atomic >
inline  const  Atomic&
cUSROCMap<LOD,Atomic>::Get(tGlobalIndex iX,tGlobalIndex iY,tGlobalIndex iZ)  const
{
    return  Atomic();
}


template<eLod2N LOD,typename Atomic>
inline  void
cUSROCMap<LOD,Atomic>::Set(tGlobalIndex iX,tGlobalIndex iY,tGlobalIndex iZ,Atomic iValue)
{
    // TODO
}


}  // namespace  nSparseOctree
}  // namespace  nVolumetric

