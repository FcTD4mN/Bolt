#pragma once


#include <unordered_map>


#include "Core.Volumetric.SparseOctree.Types.h"
#include "Core.Volumetric.SparseOctree.Hashable3DKey.h"
#include "Core.Volumetric.SparseOctree.RootROMSChunk.h"
#include "Core.Volumetric.SparseOctree.ROMSConfig.h"


namespace  nVolumetric      {
namespace  nSparseOctree    {


template< eLod2N Macro, eLod2N VBO, eLod2N Micro, typename Atomic >
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
    bool                ChunkExists( const  cHashable3DKey&  iKey )  const;
    cROMSChunk< Macro, Atomic >*  ChunkAtKey( const  cHashable3DKey&  iKey )  const;

private:
    // Chunk Manipulation
    cROMSChunk< Macro, Atomic >*  MkChunk( const  cHashable3DKey&  iKey );
    void  RmChunk( const  cHashable3DKey&  iKey );

public:
    // VBO Related
    void  BuildVBODebug();

public:
    // Render
    void  RenderOctDebug();

private:
    // Private Member Data
    const  cROMSConfig  mROMSConfig; // Owning
    std::unordered_map< tHashableKeySignature, cRootROMSChunk< Macro, VBO, Micro, Atomic >* >  mChunks; // Owning

};


}  // namespace  nSparseOctree
}  // namespace  nVolumetric


#include "Core.Volumetric.SparseOctree.USROCMap.tImp.hpp"

