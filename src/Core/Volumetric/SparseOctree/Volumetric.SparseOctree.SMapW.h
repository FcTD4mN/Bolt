#pragma once


#include "Volumetric.SparseOctree.ROMSConfig.h"


namespace  nVolumetric      {
namespace  nSparseOctree    {


template< eLod2N LOD, typename Atomic >
class  cUSROCMap;


template< typename Atomic >
class  cSMapW
{

public:
    // Construction / Destruction
    virtual  ~cSMapW();
    cSMapW();
    cSMapW( const  cSMapW& ) = delete;

public:
    // Accessors
    const  Atomic&  Get( tGlobalIndex iX, tGlobalIndex iY, tGlobalIndex iZ )  const;
    void  Set( tGlobalIndex iX, tGlobalIndex iY, tGlobalIndex iZ, Atomic  iValue );

private:
    // Private Member Data
    cROMSConfig  mROMSConfig;
    cSMapW*  mMap;
};


}  // namespace  nSparseOctree
}  // namespace  nVolumetric


#include "Volumetric.SparseOctree.SMapW.hpp"

