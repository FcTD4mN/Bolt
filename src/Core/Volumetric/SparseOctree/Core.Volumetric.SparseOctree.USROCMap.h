#pragma once


#include <unordered_map>


#include "Core.Volumetric.SparseOctree.Types.h"
#include "Core.Volumetric.SparseOctree.Hashable3DKey.h"
#include "Core.Volumetric.SparseOctree.ROMSChunk.h"
#include "Core.Volumetric.SparseOctree.ROMSConfig.h"


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
    cHashable3DKey      KeyForIndices( tGlobalIndex iX, tGlobalIndex iY, tGlobalIndex iZ )  const;
    bool                ChunkExists( const  cHashable3DKey&  iKey )                                     const;
    cROMSChunk< LOD, Atomic >*  ChunkAtKey( const  cHashable3DKey&  iKey )                              const;

private:
    // Chunk Manipulation
    cROMSChunk< LOD, Atomic >*  MkChunk( const  cHashable3DKey&  iKey );
    void  RmChunk( const  cHashable3DKey&  iKey );

public:
    void  RenderOctDebug();

private:
    // Private Member Data
    cROMSConfig  mROMSConfig; // Owning
    std::unordered_map< tHashableKeySignature, cROMSChunk< LOD, Atomic >* >  mChunks; // Owning

};


}  // namespace  nSparseOctree
}  // namespace  nVolumetric


#include "Core.Volumetric.SparseOctree.USROCMap.tImp.hpp"

