#pragma once

#include <unordered_map>

#include "Voxel/Basic/Types.h"
#include "Voxel/Basic/StaticLodChunkN.h"
#include "Voxel/Basic/Hashable3DKey.h"


namespace  nVoxel
{

class  cStaticLodChunk64Map
{

public:
    cStaticLodChunk64Map();
    cStaticLodChunk64Map( const  cStaticLodChunk64Map& ) = delete;

public:
    void  MkChunk( const  cHashable3DKey&  iKey );
    void  RmChunk( const  cHashable3DKey&  iKey );
    bool  ChunkExists( const  cHashable3DKey&  iKey );
    tStaticLodChunk64*  ChunkAtKey( const  cHashable3DKey&  iKey );
    cHashable3DKey  KeyForIndices( tDataIndex iX, tDataIndex iY, tDataIndex iZ );

public:
    tByte* operator()( tDataIndex iX, tDataIndex iY, tDataIndex iZ );
    void  SafeSetData( tDataIndex iX, tDataIndex iY, tDataIndex iZ, tByte iValue );

private:
    std::unordered_map< tHashedKeySignature, tStaticLodChunk64* > mChunks; // Owning
};


} // namespace  nVoxel