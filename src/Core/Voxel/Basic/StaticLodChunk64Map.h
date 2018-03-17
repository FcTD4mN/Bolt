#pragma once

#include <unordered_map>

#include "Voxel/Basic/Types.h"
#include "Voxel/Basic/StaticLodChunkN.h"


namespace  nVoxel
{

class  cStaticLodChunk64Map
{

public:
    cStaticLodChunk64Map();
    cStaticLodChunk64Map( const  cStaticLodChunk64Map& ) = delete;

private:
    std::unordered_map< tHashableKeySignature, tStaticLodChunk64* > mData;
};


} // namespace  nVoxel