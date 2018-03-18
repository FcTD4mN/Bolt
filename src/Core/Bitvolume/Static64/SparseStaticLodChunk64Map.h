#pragma once

#include <unordered_map>

#include "Bitvolume/Static64/Utils.h"
#include "Bitvolume/Static64/StaticLodChunk64.h"
#include "Bitvolume/Static64/Hashable3DKey.h"


namespace  nBitvolume
{

class  cSparseStaticLodChunk64Map
{

public:
    // Construction / Destruction
    cSparseStaticLodChunk64Map();
    cSparseStaticLodChunk64Map( const  cSparseStaticLodChunk64Map& ) = delete;

public:
    // Sparse Volume Information
    cHashable3DKey      KeyForIndices( tGlobalDataIndex iX, tGlobalDataIndex iY, tGlobalDataIndex iZ )  const;
    bool                ChunkExists( const  cHashable3DKey&  iKey )                                     const;
    cStaticLodChunk64*  ChunkAtKey( const  cHashable3DKey&  iKey );

public:
    // Chunk cmd
    void  MkChunk( const  cHashable3DKey&  iKey );
    void  RmChunk( const  cHashable3DKey&  iKey );
    void  UpdateChunkNeighbours( const  cHashable3DKey&  iKey );
    void  PurgeEmptyChunks();

public:
    // Wrapping Inner Data Access
    tByte   operator()( tGlobalDataIndex iX, tGlobalDataIndex iY, tGlobalDataIndex iZ );
    void    SafeSetMaterial( tGlobalDataIndex iX, tGlobalDataIndex iY, tGlobalDataIndex iZ, tByte iValue );

private:
    // Private Data Members
    std::unordered_map< tHashableKeySignature, cStaticLodChunk64* > mChunks; // Owning
};


} // namespace  nBitvolume