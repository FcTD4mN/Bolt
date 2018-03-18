#include "Bitvolume/Static64/SparseStaticLodChunk64Map.h"


#include "Math/Utils.h"

namespace  nBitvolume
{

cSparseStaticLodChunk64Map::cSparseStaticLodChunk64Map() :
    mChunks()
{
}


//----------------------------------------------------------------------------------------------
//-------------------------------------------------------------------- Sparse Volume Information


cHashable3DKey
cSparseStaticLodChunk64Map::KeyForIndices( tGlobalDataIndex iX, tGlobalDataIndex iY, tGlobalDataIndex iZ )  const
{
    tKeyComponent keyX = tKeyComponent( floor( double(iX) / 64. ) );
    tKeyComponent keyY = tKeyComponent( floor( double(iY) / 64. ) );
    tKeyComponent keyZ = tKeyComponent( floor( double(iZ) / 64. ) );
    return  cHashable3DKey( keyX, keyY, keyZ );
}


bool
cSparseStaticLodChunk64Map::ChunkExists( const  cHashable3DKey&  iKey )  const
{
    return  ( ! ( mChunks.find( iKey.HashedSignature() ) == mChunks.end() ) );
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


//----------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------ Chunk cmd

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


void
cSparseStaticLodChunk64Map::UpdateChunkNeighbours( const  cHashable3DKey&  iKey )
{
    auto chunk  = ChunkAtKey( iKey );           // can be NULL
    auto top    = ChunkAtKey( iKey.Top() );     // can be NULL
    auto bot    = ChunkAtKey( iKey.Bot() );     // can be NULL
    auto front  = ChunkAtKey( iKey.Front() );   // can be NULL
    auto back   = ChunkAtKey( iKey.Back() );    // can be NULL
    auto left   = ChunkAtKey( iKey.Left() );    // can be NULL
    auto right  = ChunkAtKey( iKey.Right() );   // can be NULL

    if( chunk )
    {
        chunk->SetNeighbour( cStaticLodChunk64::eChunkNeighbourIndex::kTop,     top );
        chunk->SetNeighbour( cStaticLodChunk64::eChunkNeighbourIndex::kBot,     bot );
        chunk->SetNeighbour( cStaticLodChunk64::eChunkNeighbourIndex::kFront,   front );
        chunk->SetNeighbour( cStaticLodChunk64::eChunkNeighbourIndex::kBack,    back );
        chunk->SetNeighbour( cStaticLodChunk64::eChunkNeighbourIndex::kLeft,    left );
        chunk->SetNeighbour( cStaticLodChunk64::eChunkNeighbourIndex::kRight,   right );
    }

    if( top )   top->SetNeighbour(      cStaticLodChunk64::eChunkNeighbourIndex::kBot,      chunk );
    if( bot )   bot->SetNeighbour(      cStaticLodChunk64::eChunkNeighbourIndex::kTop,      chunk );
    if( front ) front->SetNeighbour(    cStaticLodChunk64::eChunkNeighbourIndex::kBack,     chunk );
    if( back )  back->SetNeighbour(     cStaticLodChunk64::eChunkNeighbourIndex::kFront,    chunk );
    if( left )  left->SetNeighbour(     cStaticLodChunk64::eChunkNeighbourIndex::kRight,    chunk );
    if( right ) right->SetNeighbour(    cStaticLodChunk64::eChunkNeighbourIndex::kLeft,     chunk );
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


//----------------------------------------------------------------------------------------------
//------------------------------------------------------------------- Wrapping Inner Data Access


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