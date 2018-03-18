#include "Voxel/Static64/SparseStaticLodChunk64Map.h"


#include "Math/Utils.h"

namespace  nVoxel
{

cSparseStaticLodChunk64Map::cSparseStaticLodChunk64Map() :
    mChunks()
{
}


void
cSparseStaticLodChunk64Map::MkChunk( const  cHashable3DKey&  iKey )
{
    if( ChunkExists( iKey ) )
        return;

    mChunks.emplace( iKey.HashedSignature(), &tStaticLodChunk64(0) );
    UpdateChunkNeighbours( iKey );
}


void
cSparseStaticLodChunk64Map::RmChunk( const  cHashable3DKey&  iKey )
{
    if( !ChunkExists( iKey ) )
        return;

    mChunks.erase( iKey.HashedSignature() );
    UpdateChunkNeighbours( iKey );
}


bool
cSparseStaticLodChunk64Map::ChunkExists( const  cHashable3DKey&  iKey )
{
    return  KEY_EXISTS( mChunks, iKey.HashedSignature() );
}


tStaticLodChunk64*
cSparseStaticLodChunk64Map::ChunkAtKey( const  cHashable3DKey&  iKey )
{
    auto it = mChunks.find( iKey.HashedSignature() );
    if( it != mChunks.end() )
        return  it->second;
    else
        return  NULL;
}


cHashable3DKey
cSparseStaticLodChunk64Map::KeyForIndices( tDataIndex iX, tDataIndex iY, tDataIndex iZ )
{
    tKeyComponent keyX = tKeyComponent( floor( double(iX) / 64. ) );
    tKeyComponent keyY = tKeyComponent( floor( double(iY) / 64. ) );
    tKeyComponent keyZ = tKeyComponent( floor( double(iZ) / 64. ) );
    return  cHashable3DKey( keyX, keyY, keyZ );
}


void
cSparseStaticLodChunk64Map::UpdateChunkNeighbours( const  cHashable3DKey&  iKey )
{
    auto chunk = ChunkAtKey( iKey );
    auto top = ChunkAtKey( iKey.Top() );
    auto bot = ChunkAtKey( iKey.Bot() );
    auto front  = ChunkAtKey( iKey.Front() );
    auto back = ChunkAtKey( iKey.Back() );
    auto left = ChunkAtKey( iKey.Left() );
    auto right = ChunkAtKey( iKey.Right() );

    if( chunk )
    {
        chunk->SetNeighbour( eChunkNeighbour::kTop, top );
        chunk->SetNeighbour( eChunkNeighbour::kBot, bot );
        chunk->SetNeighbour( eChunkNeighbour::kFront, front );
        chunk->SetNeighbour( eChunkNeighbour::kBack, back );
        chunk->SetNeighbour( eChunkNeighbour::kLeft, left );
        chunk->SetNeighbour( eChunkNeighbour::kRight, right );
    }

    if( top ) top->SetNeighbour( eChunkNeighbour::kBot, chunk );
    if( bot ) bot->SetNeighbour( eChunkNeighbour::kTop, chunk );
    if( front ) front->SetNeighbour( eChunkNeighbour::kBack, chunk );
    if( back ) back->SetNeighbour( eChunkNeighbour::kFront, chunk );
    if( left ) left->SetNeighbour( eChunkNeighbour::kRight, chunk );
    if( right ) right->SetNeighbour( eChunkNeighbour::kLeft, chunk );
}


const  tByte&
cSparseStaticLodChunk64Map::operator()( tDataIndex iX, tDataIndex iY, tDataIndex iZ )
{
    cHashable3DKey  key = KeyForIndices( iX, iY, iZ );
    tByte dataX = tByte( tKeyComponent( iX ) - key.GetX() * 64 );
    tByte dataY = tByte( tKeyComponent( iY ) - key.GetY() * 64 );
    tByte dataZ = tByte( tKeyComponent( iZ ) - key.GetZ() * 64 );
    auto chunk = ChunkAtKey( key );
    return  chunk->GetData( dataX, dataY, dataZ );
}


void
cSparseStaticLodChunk64Map::SafeSetData( tDataIndex iX, tDataIndex iY, tDataIndex iZ, tByte iValue )
{
    cHashable3DKey  key = KeyForIndices( iX, iY, iZ );
    MkChunk( key );
    tByte dataX = tByte( tKeyComponent( iX ) - key.GetX() * 64 );
    tByte dataY = tByte( tKeyComponent( iY ) - key.GetY() * 64 );
    tByte dataZ = tByte( tKeyComponent( iZ ) - key.GetZ() * 64 );
    auto chunk = ChunkAtKey( key );
    chunk->SetData( dataX, dataY, dataZ, iValue );
}


} // namespace  nVoxel