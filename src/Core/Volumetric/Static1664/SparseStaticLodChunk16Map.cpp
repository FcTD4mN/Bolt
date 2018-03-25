#include "Volumetric/Static1664/SparseStaticLodChunk16Map.h"


#include <GL/glew.h>
#include <gl/GLU.h>
#include "SFML/OpenGL.hpp"


namespace  nVolumetric
{


cSparseStaticLodChunk16Map::~cSparseStaticLodChunk16Map()
{
    PurgeAllChunks();
}


cSparseStaticLodChunk16Map::cSparseStaticLodChunk16Map() :
    mChunks()
{
}


//----------------------------------------------------------------------------------------------
//-------------------------------------------------------------------- Sparse Volume Information


cHashable3DKey
cSparseStaticLodChunk16Map::KeyForIndices( tGlobalDataIndex iX, tGlobalDataIndex iY, tGlobalDataIndex iZ )  const
{
    tKeyComponent keyX = tKeyComponent( floor( double(iX) / 16. ) );
    tKeyComponent keyY = tKeyComponent( floor( double(iY) / 16. ) );
    tKeyComponent keyZ = tKeyComponent( floor( double(iZ) / 16. ) );
    return  cHashable3DKey( keyX, keyY, keyZ );
}


bool
cSparseStaticLodChunk16Map::ChunkExists( const  cHashable3DKey&  iKey )  const
{
    return  ( ! ( mChunks.find( iKey.HashedSignature() ) == mChunks.end() ) );
}


cStaticLodChunk16*
cSparseStaticLodChunk16Map::ChunkAtKey( const  cHashable3DKey&  iKey )
{
    auto it = mChunks.find( iKey.HashedSignature() );
    if( it != mChunks.end() )
        return  it->second;
    else
        return  NULL;
}


//----------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------ Chunk cmd

cStaticLodChunk16*
cSparseStaticLodChunk16Map::MkChunk( const  cHashable3DKey&  iKey )
{
    if( ChunkExists( iKey ) )
        return  ChunkAtKey( iKey );

    auto chunk = new cStaticLodChunk16(0);
    mChunks.emplace( iKey.HashedSignature(), chunk );
    UpdateChunkNeighbours( iKey );
    return  chunk;
}


void
cSparseStaticLodChunk16Map::RmChunk( const  cHashable3DKey&  iKey )
{
    if( !ChunkExists( iKey ) )
        return;

    auto it = mChunks.find( iKey.HashedSignature() );
    delete  it->second;
    mChunks.erase( it );
    UpdateChunkNeighbours( iKey );
}


void
cSparseStaticLodChunk16Map::UpdateChunkNeighbours( const  cHashable3DKey&  iKey )
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
cSparseStaticLodChunk16Map::PurgeEmptyChunks()
{
    for ( auto it : mChunks )
    {
        auto hashedKey = it.first;
        auto chunk = it.second;
        if( chunk->IsEmpty() ) RmChunk( cHashable3DKey( hashedKey ) );
    }
}


void
cSparseStaticLodChunk16Map::PurgeAllChunks()
{
    std::vector< cHashable3DKey > toRemove;
    toRemove.reserve( mChunks.size() );

    for ( auto it : mChunks )
    {
        auto hashedKey = it.first;
        auto chunk = it.second;
        toRemove.push_back( cHashable3DKey( hashedKey ) );
    }

    for( int i = 0; i < toRemove.size(); ++i )
    {
        RmChunk( toRemove[i] );
    }
}


void
cSparseStaticLodChunk16Map::UpdateChunksVBOs()
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
cSparseStaticLodChunk16Map::operator()( tGlobalDataIndex iX, tGlobalDataIndex iY, tGlobalDataIndex iZ )
{
    cHashable3DKey  key = KeyForIndices( iX, iY, iZ );
    tByte dataX = tByte( tKeyComponent( iX ) - key.GetX() * 16 );
    tByte dataY = tByte( tKeyComponent( iY ) - key.GetY() * 16 );
    tByte dataZ = tByte( tKeyComponent( iZ ) - key.GetZ() * 16 );
    auto chunk = ChunkAtKey( key );
    return  chunk->GetMaterial( dataX, dataY, dataZ );
}


void
cSparseStaticLodChunk16Map::SafeSetMaterial( tGlobalDataIndex iX, tGlobalDataIndex iY, tGlobalDataIndex iZ, tByte iValue )
{
    cHashable3DKey  key = KeyForIndices( iX, iY, iZ );
    auto chunk = MkChunk( key );
    tByte dataX = tByte( tKeyComponent( iX ) - key.GetX() * 16 );
    tByte dataY = tByte( tKeyComponent( iY ) - key.GetY() * 16 );
    tByte dataZ = tByte( tKeyComponent( iZ ) - key.GetZ() * 16 );
    chunk->SetMaterial( dataX, dataY, dataZ, iValue );
}


//----------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------ Naive Rendering


void
cSparseStaticLodChunk16Map::RenderVBOs( GLuint iShaderProgramID )
{
    for ( auto it : mChunks )
    {
        auto hashedKey = it.first;
        auto chunk = it.second;
        cHashable3DKey key( hashedKey );

        glPushMatrix();
        glTranslatef( key.GetX() * 16.f, key.GetY() * 16.f, key.GetZ() * 16.f );
        chunk->DrawVBOs( iShaderProgramID );
        glPopMatrix();

    }
}

} // namespace  nVolumetric

