#include "Core.Volumetric.SparseOctree.USROCMap.h"


#include <GL/glew.h>
#include <gl/GLU.h>
#include <SFML/OpenGL.hpp>


namespace  nVolumetric      {
namespace  nSparseOctree    {


//----------------------------------------------------------------------------------------------
//------------------------------------------------------------------- Construction / Destruction


template< eLod2N LOD, typename Atomic >
inline  cUSROCMap< LOD, Atomic>::~cUSROCMap()
{
}


template< eLod2N LOD, typename Atomic >
inline  cUSROCMap< LOD, Atomic >::cUSROCMap() :
    mROMSConfig( cROMSConfig() ),
    mChunks()
{
}


//----------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------- Data Accessors


template< eLod2N LOD, typename Atomic >
inline  const  Atomic&
cUSROCMap<LOD,Atomic>::Get(tGlobalIndex iX,tGlobalIndex iY,tGlobalIndex iZ)  const
{
    cHashable3DKey  key = KeyForIndices( iX, iY, iZ );
    auto chunk = ChunkAtKey( key );
    tIndex  dataX = tIndex( tIndex( iX ) - key.GetX() * tSize( LOD ) );
    tIndex  dataY = tIndex( tIndex( iY ) - key.GetY() * tSize( LOD ) );
    tIndex  dataZ = tIndex( tIndex( iZ ) - key.GetZ() * tSize( LOD ) );
    return  chunk->Get( dataX, dataY, dataZ );
}


template<eLod2N LOD,typename Atomic>
inline  void
cUSROCMap<LOD,Atomic>::Set(tGlobalIndex iX,tGlobalIndex iY,tGlobalIndex iZ,Atomic iValue)
{
    cHashable3DKey  key = KeyForIndices( iX, iY, iZ );
    auto chunk = MkChunk( key );
    tIndex dataX = tIndex( tIndex( iX ) - key.GetX() * tSize( LOD ) );
    tIndex dataY = tIndex( tIndex( iY ) - key.GetY() * tSize( LOD ) );
    tIndex dataZ = tIndex( tIndex( iZ ) - key.GetZ() * tSize( LOD ) );
    chunk->Set( dataX, dataY, dataZ, iValue );
}


//----------------------------------------------------------------------------------------------
//-------------------------------------------------------------------- Sparse Volume Information


template<eLod2N LOD,typename Atomic>
inline cHashable3DKey cUSROCMap<LOD,Atomic>::KeyForIndices( tGlobalIndex iX, tGlobalIndex iY, tGlobalIndex iZ)  const
{
    double  size = double( LOD );
    tIndex keyX = tIndex( floor( iX / size ) );
    tIndex keyY = tIndex( floor( iY / size ) );
    tIndex keyZ = tIndex( floor( iZ / size ) );
    return  cHashable3DKey( keyX, keyY, keyZ );
}


template<eLod2N LOD,typename Atomic>
inline bool cUSROCMap<LOD,Atomic>::ChunkExists(const cHashable3DKey & iKey) const
{
    return  ( ! ( mChunks.find( iKey.HashedSignature() ) == mChunks.end() ) );
}


template<eLod2N LOD,typename Atomic>
inline cROMSChunk<LOD,Atomic>* cUSROCMap<LOD,Atomic>::ChunkAtKey(const cHashable3DKey & iKey) const
{
    auto it = mChunks.find( iKey.HashedSignature() );
    if( it != mChunks.end() )
        return  it->second;
    else
        return  NULL;
}


//----------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------- Chunk Manipulation


template<eLod2N LOD,typename Atomic>
inline cROMSChunk<LOD,Atomic>* cUSROCMap<LOD,Atomic>::MkChunk(const cHashable3DKey & iKey)
{
    if( ChunkExists( iKey ) )
        return  ChunkAtKey( iKey );

    cROMSChunk< LOD, Atomic >*  chunk = new  cROMSChunk< LOD, Atomic >( &mROMSConfig, eType::kEmpty, Atomic( 0 ) );
    mChunks.emplace( iKey.HashedSignature(), chunk );
    return  chunk;
}


template<eLod2N LOD,typename Atomic>
inline void cUSROCMap<LOD,Atomic>::RmChunk(const cHashable3DKey & iKey)
{
    if( !ChunkExists( iKey ) )
        return;

    auto it = mChunks.find( iKey.HashedSignature() );
    delete  it->second;
    mChunks.erase( it );
}


template< eLod2N LOD, typename Atomic >
inline  void  cUSROCMap< LOD, Atomic >::RenderOctDebug()
{
    for ( auto it : mChunks )
    {
        auto hashedKey = it.first;
        auto chunk = it.second;
        cHashable3DKey key( hashedKey );

        float sizef = float( LOD );

        glPushMatrix();
        glTranslatef( key.GetX() * sizef, key.GetY() * sizef, key.GetZ() * sizef );
        chunk->RenderOctDebug();
        glPopMatrix();

    }
}


}  // namespace  nSparseOctree
}  // namespace  nVolumetric

