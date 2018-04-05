#pragma once


#include <unordered_map>


#include "Volumetric.SparseOctree.Types.h"
#include "Volumetric.SparseOctree.ROMSChunk.h"
#include "Volumetric.SparseOctree.ROMSConfig.h"


namespace  nVolumetric      {
namespace  nSparseOctree    {


template< eLod2N LOD, typename Atomic >
class  cUSROCMap final
{

public:
    // Construction / Destruction
    ~cUSROCMap();
    cUSROCMap();
    cUSROCMap( const  cUSROCMap& ) = delete;

public:
    // Accessors
    const  Atomic&  Get( tGlobalIndex iX, tGlobalIndex iY, tGlobalIndex iZ )  const;
    void  Set( tGlobalIndex iX, tGlobalIndex iY, tGlobalIndex iZ, Atomic  iValue );


private:
    // Sparse Volume Information
    cHashable3DKey      KeyForIndices( tGlobalDataIndex iX, tGlobalDataIndex iY, tGlobalDataIndex iZ )  const;
    bool                ChunkExists( const  cHashable3DKey&  iKey )                                     const;
    cROMSChunk< LOD, Atomic >*  ChunkAtKey( const  cHashable3DKey&  iKey )                              const;

private:
    // Chunk Manipulation
    cROMSChunk< LOD, Atomic >*  MkChunk( const  cHashable3DKey&  iKey );
    void  RmChunk( const  cHashable3DKey&  iKey );

private:
    // Private Member Data
    cROMSConfig  mROMSConfig; // Owning
    std::unordered_map< tHashableKeySignature, cROMSChunk< LOD, Atomic >* >  mChunks; // Owning
};


}  // namespace  nSparseOctree
}  // namespace  nVolumetric


#include "Volumetric.SparseOctree.USROCMap.tImp.hpp"

