#include "Bitvolume/Static64/SparseStaticLodChunk64Map.h"


#include "Math/Utils.h"

namespace  nBitvolume
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

    mChunks.emplace( iKey.HashedSignature(), &cStaticLodChunk64(0) );
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


cStaticLodChunk64*
cSparseStaticLodChunk64Map::ChunkAtKey( const  cHashable3DKey&  iKey )
{
    auto it = mChunks.find( iKey.HashedSignature() );
    if( it != mChunks.end() )
        return  it->second;
    else
        return  NULL;
}


cHashable3DKey
cSparseStaticLodChunk64Map::KeyForIndices( tGlobalDataIndex iX, tGlobalDataIndex iY, tGlobalDataIndex iZ )
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
        chunk->SetNeighbour( eChunkNeighbourIndex::kTop, top );
        chunk->SetNeighbour( eChunkNeighbourIndex::kBot, bot );
        chunk->SetNeighbour( eChunkNeighbourIndex::kFront, front );
        chunk->SetNeighbour( eChunkNeighbourIndex::kBack, back );
        chunk->SetNeighbour( eChunkNeighbourIndex::kLeft, left );
        chunk->SetNeighbour( eChunkNeighbourIndex::kRight, right );
    }

    if( top )   top->SetNeighbour(      eChunkNeighbourIndex::kBot, chunk );
    if( bot )   bot->SetNeighbour(      eChunkNeighbourIndex::kTop, chunk );
    if( front ) front->SetNeighbour(    eChunkNeighbourIndex::kBack, chunk );
    if( back )  back->SetNeighbour(     eChunkNeighbourIndex::kFront, chunk );
    if( left )  left->SetNeighbour(     eChunkNeighbourIndex::kRight, chunk );
    if( right ) right->SetNeighbour(    eChunkNeighbourIndex::kLeft, chunk );
}


void
cSparseStaticLodChunk64Map::PurgeEmptyChunks()
{
    for ( auto it : mChunks )
    {
        auto hashedKey = it.first;
        auto chunk = it.second;
        if( chunk->IsEmpty() ) RmChunk( cHashable3DKey( hashedKey ) );
    }
}


tByte
cSparseStaticLodChunk64Map::operator()( tGlobalDataIndex iX, tGlobalDataIndex iY, tGlobalDataIndex iZ )
{
    cHashable3DKey  key = KeyForIndices( iX, iY, iZ );
    tByte dataX = tByte( tKeyComponent( iX ) - key.GetX() * 64 );
    tByte dataY = tByte( tKeyComponent( iY ) - key.GetY() * 64 );
    tByte dataZ = tByte( tKeyComponent( iZ ) - key.GetZ() * 64 );
    auto chunk = ChunkAtKey( key );
    return  chunk->GetMaterial( dataX, dataY, dataZ );
}


void
cSparseStaticLodChunk64Map::SafeSetMaterial( tGlobalDataIndex iX, tGlobalDataIndex iY, tGlobalDataIndex iZ, tByte iValue )
{
    cHashable3DKey  key = KeyForIndices( iX, iY, iZ );
    MkChunk( key );
    tByte dataX = tByte( tKeyComponent( iX ) - key.GetX() * 64 );
    tByte dataY = tByte( tKeyComponent( iY ) - key.GetY() * 64 );
    tByte dataZ = tByte( tKeyComponent( iZ ) - key.GetZ() * 64 );
    auto chunk = ChunkAtKey( key );
    chunk->SetMaterial( dataX, dataY, dataZ, iValue );
}


} // namespace  nBitvolume