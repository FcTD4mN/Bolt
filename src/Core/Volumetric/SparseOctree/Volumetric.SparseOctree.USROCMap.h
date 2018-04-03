#pragma once


#include <unordered_map>


#include "Volumetric.SparseOctree.Types.h"
#include "Volumetric.SparseOctree.ROMSChunk.h"
#include "Volumetric.SparseOctree.ROMSConfig.h"


namespace  nVolumetric      {
namespace  nSparseOctree    {


template< eLod2N LOD, typename Atomic >
class  cUSROCMap
{

public:
    // Construction / Destruction
    virtual  ~cUSROCMap();
    cUSROCMap();
    cUSROCMap( const  cUSROCMap& ) = delete;

public:
    // Accessors
    const  Atomic&  Get( tGlobalIndex iX, tGlobalIndex iY, tGlobalIndex iZ )  const;
    void  Set( tGlobalIndex iX, tGlobalIndex iY, tGlobalIndex iZ, Atomic  iValue );

private:
    // Private Member Data
    cROMSConfig  mROMSConfig;
    std::unordered_map< tHashableKeySignature, cROMSChunk< LOD, Atomic >* >  mChunks; // Owning
};


}  // namespace  nSparseOctree
}  // namespace  nVolumetric


#include "Volumetric.SparseOctree.USROCMap.hpp"

