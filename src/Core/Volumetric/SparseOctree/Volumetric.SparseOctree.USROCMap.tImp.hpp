#include "Volumetric.SparseOctree.USROCMap.h"


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
    tIndex  dataX = tIndex( tKeyComponent( iX ) - key.GetX() * tSize( LOD ) );
    tIndex  dataY = tIndex( tKeyComponent( iY ) - key.GetY() * tSize( LOD ) );
    tIndex  dataZ = tIndex( tKeyComponent( iZ ) - key.GetZ() * tSize( LOD ) );
    return  chunk->Get( dataX, dataY, dataZ );
}


template<eLod2N LOD,typename Atomic>
inline  void
cUSROCMap<LOD,Atomic>::Set(tGlobalIndex iX,tGlobalIndex iY,tGlobalIndex iZ,Atomic iValue)
{
    cHashable3DKey  key = KeyForIndices( iX, iY, iZ );
    auto chunk = MkChunk( key );
    tIndex dataX = tIndex( tKeyComponent( iX ) - key.GetX() * tSize( LOD ) );
    tIndex dataY = tIndex( tKeyComponent( iY ) - key.GetY() * tSize( LOD ) );
    tIndex dataZ = tIndex( tKeyComponent( iZ ) - key.GetZ() * tSize( LOD ) );
    chunk->Set( dataX, dataY, dataZ, iValue );
}


//----------------------------------------------------------------------------------------------
//-------------------------------------------------------------------- Sparse Volume Information


template<eLod2N LOD,typename Atomic>
inline cHashable3DKey cUSROCMap<LOD,Atomic>::KeyForIndices(tGlobalDataIndex iX,tGlobalDataIndex iY,tGlobalDataIndex iZ) const
{
    double  size = double( LOD );
    tKeyComponent keyX = tKeyComponent( floor( iX / size ) );
    tKeyComponent keyY = tKeyComponent( floor( iY / size ) );
    tKeyComponent keyZ = tKeyComponent( floor( iZ / size ) );
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

    auto chunk = new  cROMSChunk< LOD, Atomic >( &ROMSConfig() );
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


}  // namespace  nSparseOctree
}  // namespace  nVolumetric

