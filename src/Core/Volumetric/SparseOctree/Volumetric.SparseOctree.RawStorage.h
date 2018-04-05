#pragma once


#include "Volumetric.SparseOctree.Types.h"


namespace  nVolumetric      {
namespace  nSparseOctree    {


template< eLod2N LOD, typename Atomic >
class  cRawStorage
{

public:
    // Construction / Destruction
    virtual  ~cRawStorage();
    cRawStorage();
    cRawStorage( const  cRawStorage& ) = delete;

public:
    // Data Accessors
    virtual  const  Atomic&  Get( tIndex iX, tIndex iY, tIndex iZ )  const;
    virtual  void  Set( tIndex iX, tIndex iY, tIndex iZ, const  Atomic&  iValue );

private:
    // Private Member Data
    static  const  tSize  mSize = tSize( LOD );
    Atomic  mCore[mSize][mSize][mSize];
};


}  // namespace  nSparseOctree
}  // namespace  nVolumetric


#include "Volumetric.SparseOctree.RawStorage.tImp.hpp"

