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
    cSparseStaticLodChunk64Map();
    cSparseStaticLodChunk64Map( const  cSparseStaticLodChunk64Map& ) = delete;

public:
    void  MkChunk( const  cHashable3DKey&  iKey );
    void  RmChunk( const  cHashable3DKey&  iKey );
    bool  ChunkExists( const  cHashable3DKey&  iKey );
    cStaticLodChunk64*  ChunkAtKey( const  cHashable3DKey&  iKey );
    cHashable3DKey  KeyForIndices( tGlobalDataIndex iX, tGlobalDataIndex iY, tGlobalDataIndex iZ );
    void  UpdateChunkNeighbours( const  cHashable3DKey&  iKey );
    void  PurgeEmptyChunks();

public:
    tByte  operator()( tGlobalDataIndex iX, tGlobalDataIndex iY, tGlobalDataIndex iZ );
    void  SafeSetMaterial( tGlobalDataIndex iX, tGlobalDataIndex iY, tGlobalDataIndex iZ, tByte iValue );

private:
    std::unordered_map< tHashableKeySignature, cStaticLodChunk64* > mChunks; // Owning
};


} // namespace  nBitvolume