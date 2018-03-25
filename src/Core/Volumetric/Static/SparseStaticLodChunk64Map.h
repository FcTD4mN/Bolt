#pragma once

#include <unordered_map>

#include "Volumetric/Static/Types.h"
#include "Volumetric/Static/StaticLodChunk64.h"
#include "Volumetric/Static/Hashable3DKey.h"


namespace  nVolumetric
{

class  cSparseStaticLodChunk64Map
{

public:
    // Construction / Destruction
    ~cSparseStaticLodChunk64Map();
    cSparseStaticLodChunk64Map();
    cSparseStaticLodChunk64Map( const  cSparseStaticLodChunk64Map& ) = delete;

public:
    // Sparse Volume Information
    cHashable3DKey      KeyForIndices( tGlobalDataIndex iX, tGlobalDataIndex iY, tGlobalDataIndex iZ )  const;
    bool                ChunkExists( const  cHashable3DKey&  iKey )                                     const;
    cStaticLodChunk64*  ChunkAtKey( const  cHashable3DKey&  iKey );

public:
    // Chunk cmd
    cStaticLodChunk64*  MkChunk( const  cHashable3DKey&  iKey );
    void  RmChunk( const  cHashable3DKey&  iKey );
    void  UpdateChunkNeighbours( const  cHashable3DKey&  iKey );
    void  PurgeEmptyChunks();
    void  PurgeAllChunks();

    void  UpdateChunksVBOs();

public:
    // Wrapping Inner Data Access
    tByte   operator()( tGlobalDataIndex iX, tGlobalDataIndex iY, tGlobalDataIndex iZ );
    void    SafeSetMaterial( tGlobalDataIndex iX, tGlobalDataIndex iY, tGlobalDataIndex iZ, tByte iValue );

public:
    // Naive Rendering
    void  RenderVBOs( GLuint iShaderProgramID );

private:
    // Private Data Members
    std::unordered_map< tHashableKeySignature, cStaticLodChunk64* > mChunks; // Owning
    int  mUseDebugColors;
};


} // namespace  nVolumetric

