#include "Voxel/Basic/StaticLodChunk64Map.h"


#include "Math/Utils.h"

namespace  nVoxel
{

cStaticLodChunk64Map::cStaticLodChunk64Map() :
    mChunks()
{
}


void
cStaticLodChunk64Map::MkChunk( const  cHashable3DKey&  iKey )
{
    if( ChunkExists( iKey ) )
        return;

    mChunks.emplace( iKey.HashedSignature() );
}


void
cStaticLodChunk64Map::RmChunk( const  cHashable3DKey&  iKey )
{
    if( !ChunkExists( iKey ) )
        return;

    mChunks.erase( iKey.HashedSignature() );
}


bool
cStaticLodChunk64Map::ChunkExists( const  cHashable3DKey&  iKey )
{
    return  KEY_EXISTS( mChunks, iKey.HashedSignature() );
}


tStaticLodChunk64*
cStaticLodChunk64Map::ChunkAtKey( const  cHashable3DKey&  iKey )
{
    auto it = mChunks.find( iKey.HashedSignature() );
    if( it != mChunks.end() )
        return  it->second;
    else
        return  NULL;
}


cHashable3DKey
cStaticLodChunk64Map::KeyForIndices( tDataIndex iX, tDataIndex iY, tDataIndex iZ )
{
    tKeyComponent keyX = tKeyComponent( floor( double(iX) / 64. ) );
    tKeyComponent keyY = tKeyComponent( floor( double(iY) / 64. ) );
    tKeyComponent keyZ = tKeyComponent( floor( double(iZ) / 64. ) );
    return  cHashable3DKey( keyX, keyY, keyZ );
}


tByte*
cStaticLodChunk64Map::operator()( tDataIndex iX, tDataIndex iY, tDataIndex iZ )
{
    cHashable3DKey  key = KeyForIndices( iX, iY, iZ );
    tKeyComponent dataX = iX - key.GetX() * 64;
    tKeyComponent dataY = iY - key.GetY() * 64;
    tKeyComponent dataZ = iZ - key.GetZ() * 64;
    auto chunk = ChunkAtKey( key );
    return  (*chunk)( dataX, dataY, dataZ );
}


void
cStaticLodChunk64Map::SafeSetData( tDataIndex iX, tDataIndex iY, tDataIndex iZ, tByte iValue )
{
    cHashable3DKey  key = KeyForIndices( iX, iY, iZ );
    MkChunk( key );

    tKeyComponent dataX = iX - key.GetX() * 64;
    tKeyComponent dataY = iY - key.GetY() * 64;
    tKeyComponent dataZ = iZ - key.GetZ() * 64;
    auto chunk = ChunkAtKey( key );
    *(*chunk)( dataX, dataY, dataZ ) = iValue;
}


} // namespace  nVoxel