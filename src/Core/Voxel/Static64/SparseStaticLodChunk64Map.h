#pragma once

#include <unordered_map>

#include "Voxel/Static64/Utils.h"
#include "Voxel/Static64/StaticLodChunkN.h"
#include "Voxel/Static64/Hashable3DKey.h"


namespace  nVoxel
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
    tStaticLodChunk64*  ChunkAtKey( const  cHashable3DKey&  iKey );
    cHashable3DKey  KeyForIndices( tDataIndex iX, tDataIndex iY, tDataIndex iZ );
    void  UpdateChunkNeighbours( const  cHashable3DKey&  iKey );
    void  PurgeEmptyChunks();

public:
    const  tByte&  operator()( tDataIndex iX, tDataIndex iY, tDataIndex iZ );
    void  SafeSetData( tDataIndex iX, tDataIndex iY, tDataIndex iZ, tByte iValue );

private:
    std::unordered_map< tHashedKeySignature, tStaticLodChunk64* > mChunks; // Owning
};


} // namespace  nVoxel