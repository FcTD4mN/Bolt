#pragma once


#include "Volumetric.SparseOctree.Types.h"
#include "Volumetric.SparseOctree.Data.h"


namespace  nVolumetric      {
namespace  nSparseOctree    {


class  cROMSConfig;


template< eLod2N LOD, typename Atomic >
class  cROMSChunk
{

public:
    // Construction / Destruction
    ~cROMSChunk();
    cROMSChunk( const  cROMSConfig*  iROMSConfig );
    cROMSChunk( const  cROMSChunk& ) = delete;

public:
    // Data Accessors
    const  Atomic&  Get( tIndex iX, tIndex iY, tIndex iZ )  const;
    void  Set( tIndex iX, tIndex iY, tIndex iZ, const  Atomic&  iValue );

private:
    // Private Member Data
    cData< LOD, Atomic >*  mData; // Owning
    const  cROMSConfig*  mROMSConfig;
};


}  // namespace  nSparseOctree
}  // namespace  nVolumetric


#include "Volumetric.SparseOctree.ROMSChunk.hpp"

