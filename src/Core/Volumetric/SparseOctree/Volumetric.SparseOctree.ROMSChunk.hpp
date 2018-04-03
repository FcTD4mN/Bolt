#include "Volumetric.SparseOctree.ROMSChunk.h"


namespace  nVolumetric      {
namespace  nSparseOctree    {


template< eLod2N LOD, typename Atomic >
inline  cROMSChunk< LOD, Atomic >::~cROMSChunk()
{
}


template< eLod2N LOD, typename Atomic >
inline  cROMSChunk< LOD, Atomic >::cROMSChunk()
{
}


template< eLod2N LOD, typename Atomic >
inline  const  Atomic&
cROMSChunk<LOD,Atomic>::Get(tIndex iX,tIndex iY,tIndex iZ)  const
{
    return  mData->Get( iX, iY, iZ );
}


template< eLod2N LOD, typename Atomic >
inline  void
cROMSChunk<LOD,Atomic>::Set(tIndex iX,tIndex iY,tIndex iZ,const Atomic & iValue)
{
    mData->Set( iX, iY, iZ, iValue );
}


}  // namespace  nSparseOctree
}  // namespace  nVolumetric

