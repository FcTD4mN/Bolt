#pragma once


#include "Core.Volumetric.SparseOctree.Types.h"


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
    Atomic  mCore[ tSize( LOD ) ][ tSize( LOD ) ][ tSize( LOD ) ];
};


}  // namespace  nSparseOctree
}  // namespace  nVolumetric


#include "Core.Volumetric.SparseOctree.RawStorage.tImp.hpp"

