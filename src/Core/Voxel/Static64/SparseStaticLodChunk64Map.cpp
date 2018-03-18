#include "Voxel/Static64/SparseStaticLodChunk64Map.h"


#include "Math/Utils.h"

namespace  nVoxel
{

cSparseStaticLodChunkN::cSparseStaticLodChunkN() :
    mChunks()
{
}


void
cSparseStaticLodChunkN::MkChunk( const  cHashable3DKey&  iKey )
{
    if( ChunkExists( iKey ) )
        return;

    mChunks.emplace( iKey.HashedSignature(), &tStaticLodChunk64(0) );
}


void
cSparseStaticLodChunkN::RmChunk( const  cHashable3DKey&  iKey )
{
    if( !ChunkExists( iKey ) )
        return;

    mChunks.erase( iKey.HashedSignature() );
}


bool
cSparseStaticLodChunkN::ChunkExists( const  cHashable3DKey&  iKey )
{
    return  KEY_EXISTS( mChunks, iKey.HashedSignature() );
}


tStaticLodChunk64*
cSparseStaticLodChunkN::ChunkAtKey( const  cHashable3DKey&  iKey )
{
    auto it = mChunks.find( iKey.HashedSignature() );
    if( it != mChunks.end() )
        return  it->second;
    else
        return  NULL;
}


cHashable3DKey
cSparseStaticLodChunkN::KeyForIndices( tDataIndex iX, tDataIndex iY, tDataIndex iZ )
{
    tKeyComponent keyX = tKeyComponent( floor( double(iX) / 64. ) );
    tKeyComponent keyY = tKeyComponent( floor( double(iY) / 64. ) );
    tKeyComponent keyZ = tKeyComponent( floor( double(iZ) / 64. ) );
    return  cHashable3DKey( keyX, keyY, keyZ );
}


tByte*
cSparseStaticLodChunkN::operator()( tDataIndex iX, tDataIndex iY, tDataIndex iZ )
{
    cHashable3DKey  key = KeyForIndices( iX, iY, iZ );
    tByte dataX = tByte( tKeyComponent( iX ) - key.GetX() * 64 );
    tByte dataY = tByte( tKeyComponent( iY ) - key.GetY() * 64 );
    tByte dataZ = tByte( tKeyComponent( iZ ) - key.GetZ() * 64 );
    auto chunk = ChunkAtKey( key );
    return  (*chunk)( dataX, dataY, dataZ );
}


void
cSparseStaticLodChunkN::SafeSetData( tDataIndex iX, tDataIndex iY, tDataIndex iZ, tByte iValue )
{
    cHashable3DKey  key = KeyForIndices( iX, iY, iZ );
    MkChunk( key );
    tByte dataX = tByte( tKeyComponent( iX ) - key.GetX() * 64 );
    tByte dataY = tByte( tKeyComponent( iY ) - key.GetY() * 64 );
    tByte dataZ = tByte( tKeyComponent( iZ ) - key.GetZ() * 64 );
    auto chunk = ChunkAtKey( key );
    *(*chunk)( dataX, dataY, dataZ ) = iValue;
}


} // namespace  nVoxel