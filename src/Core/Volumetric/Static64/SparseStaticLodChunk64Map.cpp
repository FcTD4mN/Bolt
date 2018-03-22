#include "Volumetric/Static64/SparseStaticLodChunk64Map.h"


#include <GL/glew.h>
#include <gl/GLU.h>
#include "SFML/OpenGL.hpp"


namespace  nVolumetric
{


cSparseStaticLodChunk64Map::~cSparseStaticLodChunk64Map()
{
    PurgeAllChunks();
}


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

cStaticLodChunk64*
cSparseStaticLodChunk64Map::MkChunk( const  cHashable3DKey&  iKey )
{
    if( ChunkExists( iKey ) )
        return  ChunkAtKey( iKey );

    auto chunk = new cStaticLodChunk64(0);
    mChunks.emplace( iKey.HashedSignature(), chunk );
    UpdateChunkNeighbours( iKey );
    return  chunk;
}


void
cSparseStaticLodChunk64Map::RmChunk( const  cHashable3DKey&  iKey )
{
    if( !ChunkExists( iKey ) )
        return;

    auto it = mChunks.find( iKey.HashedSignature() );
    delete  it->second;
    mChunks.erase( it );
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
        chunk->SetNeighbour( eNF_Index::kIndexTop,     top );
        chunk->SetNeighbour( eNF_Index::kIndexBot,     bot );
        chunk->SetNeighbour( eNF_Index::kIndexFront,   front );
        chunk->SetNeighbour( eNF_Index::kIndexBack,    back );
        chunk->SetNeighbour( eNF_Index::kIndexLeft,    left );
        chunk->SetNeighbour( eNF_Index::kIndexRight,   right );
    }

    if( top )   top->SetNeighbour(      eNF_Index::kIndexBot,      chunk );
    if( bot )   bot->SetNeighbour(      eNF_Index::kIndexTop,      chunk );
    if( front ) front->SetNeighbour(    eNF_Index::kIndexBack,     chunk );
    if( back )  back->SetNeighbour(     eNF_Index::kIndexFront,    chunk );
    if( left )  left->SetNeighbour(     eNF_Index::kIndexRight,    chunk );
    if( right ) right->SetNeighbour(    eNF_Index::kIndexLeft,     chunk );
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


void
cSparseStaticLodChunk64Map::PurgeAllChunks()
{
    for ( auto it : mChunks )
    {
        auto hashedKey = it.first;
        auto chunk = it.second;
        RmChunk( cHashable3DKey( hashedKey ) );
    }
}


void
cSparseStaticLodChunk64Map::UpdateChunksVBOs()
{
    for ( auto it : mChunks )
    {
        auto hashedKey = it.first;
        auto chunk = it.second;
        chunk->UpdateVBOs();
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
    auto chunk = MkChunk( key );
    tByte dataX = tByte( tKeyComponent( iX ) - key.GetX() * 64 );
    tByte dataY = tByte( tKeyComponent( iY ) - key.GetY() * 64 );
    tByte dataZ = tByte( tKeyComponent( iZ ) - key.GetZ() * 64 );
    chunk->SetMaterial( dataX, dataY, dataZ, iValue );
}


//----------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------ Naive Rendering


void
cSparseStaticLodChunk64Map::DirectDraw()
{
    for ( auto it : mChunks )
    {
        auto hashedKey = it.first;
        auto chunk = it.second;
        cHashable3DKey key( hashedKey );

        glPushMatrix();
        glTranslatef( key.GetX() * 64.f, key.GetY() * 64.f, key.GetZ() * 64.f );
        chunk->DirectDraw();
        glPopMatrix();

    }
}


void
cSparseStaticLodChunk64Map::RenderVBOs()
{
    for ( auto it : mChunks )
    {
        auto hashedKey = it.first;
        auto chunk = it.second;
        cHashable3DKey key( hashedKey );

        glPushMatrix();
        glTranslatef( key.GetX() * 64.f, key.GetY() * 64.f, key.GetZ() * 64.f );
        chunk->DrawVBOs();
        glPopMatrix();

    }
}

} // namespace  nVolumetric

