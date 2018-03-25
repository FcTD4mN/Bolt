#pragma once

#include <unordered_map>

#include "Volumetric/Static/Types.h"
#include "Volumetric/Static/StaticLodChunk16.h"
#include "Volumetric/Static/Hashable3DKey.h"


namespace  nVolumetric
{

class  cSparseStaticLodChunk16Map
{

public:
    // Construction / Destruction
    ~cSparseStaticLodChunk16Map();
    cSparseStaticLodChunk16Map();
    cSparseStaticLodChunk16Map( const  cSparseStaticLodChunk16Map& ) = delete;

public:
    // Sparse Volume Information
    cHashable3DKey      KeyForIndices( tGlobalDataIndex iX, tGlobalDataIndex iY, tGlobalDataIndex iZ )  const;
    bool                ChunkExists( const  cHashable3DKey&  iKey )                                     const;
    cStaticLodChunk16*  ChunkAtKey( const  cHashable3DKey&  iKey );

public:
    // Chunk cmd
    cStaticLodChunk16*  MkChunk( const  cHashable3DKey&  iKey );
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
    std::unordered_map< tHashableKeySignature, cStaticLodChunk16* > mChunks; // Owning
    int  mUseDebugColors;
};


} // namespace  nVolumetric

