#include "Volumetric.SparseOctree.SMapW.h"


namespace  nVolumetric      {
namespace  nSparseOctree    {


template< typename Atomic >
inline  cSMapW< Atomic >::~cSMapW()
{
}


template< typename Atomic >
inline  cSMapW< Atomic >::cSMapW() :
    mROMSConfig( cROMSConfig() ),
{
    map = new  cUSROCMap< mROMSConfig.MacroscopicLODGranularity(), Atomic >();
}


template< typename Atomic >
inline  const  Atomic&
cSMapW<Atomic>::Get(tGlobalIndex iX,tGlobalIndex iY,tGlobalIndex iZ)  const
{
    return  mMap->Get( iX, iY, iZ );
}

template<typename Atomic>
inline void cSMapW<Atomic>::Set(tGlobalIndex iX,tGlobalIndex iY,tGlobalIndex iZ,Atomic iValue)
{
    mMap->Set( ix, iY, iZ, iValue );
}


}  // namespace  nSparseOctree
}  // namespace  nVolumetric

