#include "Volumetric.SparseOctree.RawStorage.h"


namespace  nVolumetric      {
namespace  nSparseOctree    {


//----------------------------------------------------------------------------------------------
//------------------------------------------------------------------- Construction / Destruction


template< eLod2N LOD, typename Atomic >
inline  cRawStorage< LOD, Atomic >::~cRawStorage()
{
}


template< eLod2N LOD, typename Atomic >
inline  cRawStorage< LOD, Atomic >::cRawStorage()
{
}

//----------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------- Data Accessors


template< eLod2N LOD, typename Atomic >
inline  const  Atomic&  cRawStorage< LOD, Atomic >::Get( tIndex iX, tIndex iY, tIndex iZ )  const
{
    assert( iX > 0 && iX < mSize );
    assert( iY > 0 && iY < mSize );
    assert( iZ > 0 && iZ < mSize );
    return  mCore[ iX ][ iY ][ iZ ];
}

template< eLod2N LOD, typename Atomic >
inline  void  cRawStorage< LOD, Atomic >::Set( tIndex iX, tIndex iY, tIndex iZ, const  Atomic&  iValue )
{
    assert( iX > 0 && iX < mSize );
    assert( iY > 0 && iY < mSize );
    assert( iZ > 0 && iZ < mSize );
    mCore[ iX ][ iY ][ iZ ] = iValue;
}


}  // namespace  nSparseOctree
}  // namespace  nVolumetric

