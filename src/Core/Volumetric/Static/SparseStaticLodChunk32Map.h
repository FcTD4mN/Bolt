#pragma once

#include <unordered_map>

#include "Volumetric/Static/Types.h"
#include "Volumetric/Static/StaticLodChunk32.h"
#include "Volumetric/Static/Hashable3DKey.h"


namespace  nVolumetric
{

class  cSparseStaticLodChunk32Map
{

public:
    // Construction / Destruction
    ~cSparseStaticLodChunk32Map();
    cSparseStaticLodChunk32Map();
    cSparseStaticLodChunk32Map( const  cSparseStaticLodChunk32Map& ) = delete;

public:
    // Sparse Volume Information
    cHashable3DKey      KeyForIndices( tGlobalDataIndex iX, tGlobalDataIndex iY, tGlobalDataIndex iZ )  const;
    bool                ChunkExists( const  cHashable3DKey&  iKey )                                     const;
    cStaticLodChunk32*  ChunkAtKey( const  cHashable3DKey&  iKey );

public:
    // Chunk cmd
    cStaticLodChunk32*  MkChunk( const  cHashable3DKey&  iKey );
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
    std::unordered_map< tHashableKeySignature, cStaticLodChunk32* > mChunks; // Owning
    int  mUseDebugColors;
};


} // namespace  nVolumetric

