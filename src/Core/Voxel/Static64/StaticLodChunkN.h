#pragma once

#include "Voxel/Static64/Utils.h"


namespace  nVoxel
{

template< tByte N >
class  cStaticLodChunkN
{

public:
    cStaticLodChunkN();
    cStaticLodChunkN( tByte iVal );
    cStaticLodChunkN( const  cStaticLodChunkN& ) = delete;

public:
    tByte           Size();
    unsigned  int   Capacity();
    unsigned  int   OccupiedVolume();
    void            Fill( tByte iVal );
    bool            IsFull();
    bool            IsEmpty();

public:
    tByte  GetMaterial( tSafeDataIndex iX, tSafeDataIndex iY, tSafeDataIndex iZ )  const;
    void  SetMaterial( tSafeDataIndex iX, tSafeDataIndex iY, tSafeDataIndex iZ, tByte iValue );
    bool  IsSolid( tSafeDataIndex iX, tSafeDataIndex iY, tSafeDataIndex iZ );
    bool  HasSolidTopNeighbour( tByte iX, tByte iY, tByte iZ );
    bool  HasSolidBotNeighbour( tByte iX, tByte iY, tByte iZ );
    bool  HasSolidFrontNeighbour( tByte iX, tByte iY, tByte iZ );
    bool  HasSolidBackNeighbour( tByte iX, tByte iY, tByte iZ );
    bool  HasSolidLeftNeighbour( tByte iX, tByte iY, tByte iZ );
    bool  HasSolidRightNeighbour( tByte iX, tByte iY, tByte iZ );
    int  DataNeighbourCount( tByte iX, tByte iY, tByte iZ );

private:
    const  t2Byte&  GetData( tSafeDataIndex iX, tSafeDataIndex iY, tSafeDataIndex iZ )  const;
    void  SetData( tSafeDataIndex iX, tSafeDataIndex iY, tSafeDataIndex iZ, t2Byte iValue );
    const  t2Byte&  SafeExternGetData( tUnsafeDataIndex iX, tUnsafeDataIndex iY, tUnsafeDataIndex iZ );
    void  SafeExternSetData( tUnsafeDataIndex iX, tUnsafeDataIndex iY, tUnsafeDataIndex iZ, t2Byte iValue );
    t2Byte  SafeExternIsSolid( tUnsafeDataIndex iX, tUnsafeDataIndex iY, tUnsafeDataIndex iZ );
    cStaticLodChunkN*  ExternChunkFromCoordinates( tUnsafeDataIndex iX, tUnsafeDataIndex iY, tUnsafeDataIndex iZ );

public:
    cStaticLodChunkN*  GetNeighbour( eChunkNeighbour  iNeighbour );
    void  SetNeighbour( eChunkNeighbour  iNeighbour, cStaticLodChunkN* iAdress );

private:
    t2Byte  mData[N][N][N];
    cStaticLodChunkN*  mNeighbour[6];
    static  const  unsigned  int  mCapacity = N * N * N;
    unsigned  int  mOccupiedVolume;

};


template< tByte N >
cStaticLodChunkN< N >::cStaticLodChunkN() :
    mOccupiedVolume( 0 )
{
}


template< tByte N >
inline cStaticLodChunkN< N >::cStaticLodChunkN( tByte iVal ) :
    mOccupiedVolume( 0 )
{
    Fill( iVal );
}


template<tByte N>
inline tByte cStaticLodChunkN<N>::Size()
{
    return  N;
}


template<tByte N>
inline unsigned  int cStaticLodChunkN<N>::Capacity()
{
    return  mCapacity;
}

template<tByte N>
inline unsigned int cStaticLodChunkN<N>::OccupiedVolume()
{
    return  mOccupiedVolume;
}


template<tByte N>
inline void cStaticLodChunkN<N>::Fill(tByte iVal)
{
    IJK_ITERATION_BEGIN( N )
        mData[i][j][k] = iVal;
    IJK_ITERATION_END

    if( iVal == eBaseMaterials::kEmpty )
        mOccupiedVolume = 0;
    else
        mOccupiedVolume = mCapacity;
}

template<tByte N>
inline bool cStaticLodChunkN<N>::IsFull()
{
    return  mOccupiedVolume == mCapacity;
}

template<tByte N>
inline bool cStaticLodChunkN<N>::IsEmpty()
{
    return  mOccupiedVolume == 0;
}

template<tByte N>
inline  tByte cStaticLodChunkN<N>::GetMaterial(tSafeDataIndex iX,tSafeDataIndex iY,tSafeDataIndex iZ) const
{
    return  tByte( GetData(iX,iY,iZ) & sgFirstByteMask );
}

template<tByte N>
inline void cStaticLodChunkN<N>::SetMaterial(tSafeDataIndex iX,tSafeDataIndex iY,tSafeDataIndex iZ, tByte iValue)
{
    tByte oldValue = GetMaterial( iX, iY, iZ );
    mData[iX][iY][iZ] = iValue;

    tByte flag = tByte( bool( oldValue ) ) << 1 | tByte( bool( iValue ) );
    if( flag == 2 ) --mOccupiedVolume;
    if( flag == 1 ) ++mOccupiedVolume;

    if( flag == 1 || flag == 2 )
    {
        IsSolid( iX, iY, iZ );
    }
}

template<tByte N>
inline bool cStaticLodChunkN<N>::IsSolid(tSafeDataIndex iX,tSafeDataIndex iY,tSafeDataIndex iZ)
{
    return  mData[iX][iY][iZ] != eBaseMaterials::kEmpty;
}

template<tByte N>
inline bool cStaticLodChunkN<N>::HasSolidTopNeighbour(tByte iX,tByte iY,tByte iZ)
{
    bool val = false;
    if( iY == 0 )
    {
        if( mNeighbour[ eChunkNeighbour::kTop ] )
        {
            if( mNeighbour[ eChunkNeighbour::kTop ]->IsSolid( iX, N-1, iZ ) )
                val = true;
        }
    }
    else
    {
        if( IsSolid( iX, iY-1, iZ ) )
            val = true;
    }
    return  val;
}

template<tByte N>
inline bool cStaticLodChunkN<N>::HasSolidBotNeighbour(tByte iX,tByte iY,tByte iZ)
{
    bool val = false;
    if( iY == N-1 )
    {
        if( mNeighbour[ eChunkNeighbour::kBot ] )
        {
            if( mNeighbour[ eChunkNeighbour::kBot ]->IsSolid( iX, 0, iZ ) )
                val = true;
        }
    }
    else
    {
        if( IsSolid( iX, iY+1, iZ ) )
            val = true;
    }
    return  val;
}

template<tByte N>
inline bool cStaticLodChunkN<N>::HasSolidFrontNeighbour(tByte iX,tByte iY,tByte iZ)
{
    bool val = false;
    if( iZ == 0 )
    {
        if( mNeighbour[ eChunkNeighbour::kFront ] )
        {
            if( mNeighbour[ eChunkNeighbour::kFront ]->IsSolid( iX, iY, N-1 ) )
                val = true;
        }
    }
    else
    {
        if( IsSolid( iX, iY, iZ-1 ) )
            val = true;
    }
    return  val;
}

template<tByte N>
inline bool cStaticLodChunkN<N>::HasSolidBackNeighbour(tByte iX,tByte iY,tByte iZ)
{
    bool val = false;
    if( iZ == N-1 )
    {
        if( mNeighbour[ eChunkNeighbour::kBack ] )
        {
            if( mNeighbour[ eChunkNeighbour::kBack ]->IsSolid( iX, iY, 0 ) )
                val = true;
        }
    }
    else
    {
        if( IsSolid( iX, iY, iZ+1 ) )
            val = true;
    }
    return  val;
}

template<tByte N>
inline bool cStaticLodChunkN<N>::HasSolidLeftNeighbour(tByte iX,tByte iY,tByte iZ)
{
    bool val = false;
    if( iX == 0 )
    {
        if( mNeighbour[ eChunkNeighbour::kLeft ] )
        {
            if( mNeighbour[ eChunkNeighbour::kLeft ]->IsSolid( N-1, iY, iZ ) )
                val = true;
        }
    }
    else
    {
        if( IsSolid( iX-1, iY, iZ ) )
            val = true;
    }
    return  val;
}

template<tByte N>
inline bool cStaticLodChunkN<N>::HasSolidRightNeighbour(tByte iX,tByte iY,tByte iZ)
{
    bool val = false;
    if( iX == 0 )
    {
        if( mNeighbour[ eChunkNeighbour::kRight ] )
        {
            if( mNeighbour[ eChunkNeighbour::kRight ]->IsSolid( 0, iY, iZ ) )
                val = true;
        }
    }
    else
    {
        if( IsSolid( iX+1, iY, iZ ) )
            val = true;
    }
    return  val;
    return false;
}


template<tByte N>
inline int cStaticLodChunkN<N>::DataNeighbourCount(tByte iX,tByte iY,tByte iZ)
{
    return  int( HasSolidTopNeighbour( iX, iY, iZ ) ) +
            int( HasSolidBotNeighbour( iX, iY, iZ ) ) +
            int( HasSolidFrontNeighbour( iX, iY, iZ ) ) +
            int( HasSolidBackNeighbour( iX, iY, iZ ) ) +
            int( HasSolidLeftNeighbour( iX, iY, iZ ) ) +
            int( HasSolidRightNeighbour( iX, iY, iZ ) );
}

template<tByte N>
inline const t2Byte & cStaticLodChunkN<N>::GetData(tSafeDataIndex iX,tSafeDataIndex iY,tSafeDataIndex iZ) const
{
    return  mData[iX][iY][iZ];
}

template<tByte N>
inline void cStaticLodChunkN<N>::SetData(tSafeDataIndex iX,tSafeDataIndex iY,tSafeDataIndex iZ,t2Byte iValue)
{
    mData[iX][iY][iZ] = iValue;
}

template<tByte N>
inline const t2Byte & cStaticLodChunkN<N>::SafeExternGetData(tUnsafeDataIndex iX,tUnsafeDataIndex iY,tUnsafeDataIndex iZ)
{
    auto chunk = ExternChunkFromCoordinates( iX, iY, iZ );
    tSafeDataIndex safeX = iX % N;
    tSafeDataIndex safeY = iY % N;
    tSafeDataIndex safeZ = iZ % N;
    return  chunk->GetData( safeX, safeY, safeZ );
}

template<tByte N>
inline void cStaticLodChunkN<N>::SafeExternSetData(tUnsafeDataIndex iX,tUnsafeDataIndex iY,tUnsafeDataIndex iZ,t2Byte iValue)
{
    auto chunk = ExternChunkFromCoordinates( iX, iY, iZ );
    tSafeDataIndex safeX = iX % N;
    tSafeDataIndex safeY = iY % N;
    tSafeDataIndex safeZ = iZ % N;
    return  chunk->SetData( safeX, safeY, safeZ, iValue );
}

template<tByte N>
inline t2Byte cStaticLodChunkN<N>::SafeExternIsSolid(tUnsafeDataIndex iX,tUnsafeDataIndex iY,tUnsafeDataIndex iZ)
{
    auto chunk = ExternChunkFromCoordinates( iX, iY, iZ );
    tSafeDataIndex safeX = iX % N;
    tSafeDataIndex safeY = iY % N;
    tSafeDataIndex safeZ = iZ % N;
    return  chunk->IsSolid( safeX, safeY, safeZ );
}


template<tByte N>
inline cStaticLodChunkN< N >*
cStaticLodChunkN<N>::ExternChunkFromCoordinates(tUnsafeDataIndex iX,tUnsafeDataIndex iY,tUnsafeDataIndex iZ)
{
    if( ( iX & sgMaxSafeDataIndex ) &&
        ( iY & sgMaxSafeDataIndex ) &&
        ( iZ & sgMaxSafeDataIndex ) )
    {
        return  this;
    }
    else
    {
        if( iY < 0 )    return  mNeighbours[ eChunkNeighbour::kTop ];
        if( iY >= N )   return  mNeighbours[ eChunkNeighbour::kBot ];
        if( iZ < 0 )    return  mNeighbours[ eChunkNeighbour::kFront ];
        if( iZ >= N )   return  mNeighbours[ eChunkNeighbour::kBack ];
        if( iX < 0 )    return  mNeighbours[ eChunkNeighbour::kLeft ];
        if( iX >= N )   return  mNeighbours[ eChunkNeighbour::kRight ];
    }
}


template<tByte N>
cStaticLodChunkN< N >*
cStaticLodChunkN< N >::GetNeighbour( eChunkNeighbour  iNeighbour )
{
    return  mNeighbour[ iNeighbour ];
}

template<tByte N>
inline void cStaticLodChunkN<N>::SetNeighbour(eChunkNeighbour iNeighbour,cStaticLodChunkN * iAdress)
{
    mNeighbour[ iNeighbour ] = iAdress;
}



} // namespace  nVoxel