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
    const  tByte&  GetData( tByte iX, tByte iY, tByte iZ )  const;
    void  SetData( tByte iX, tByte iY, tByte iZ, tByte iValue );
    bool  IsSolid( tByte iX, tByte iY, tByte iZ );
    bool  HasSolidTopNeighbour( tByte iX, tByte iY, tByte iZ );
    bool  HasSolidBotNeighbour( tByte iX, tByte iY, tByte iZ );
    bool  HasSolidFrontNeighbour( tByte iX, tByte iY, tByte iZ );
    bool  HasSolidBackNeighbour( tByte iX, tByte iY, tByte iZ );
    bool  HasSolidLeftNeighbour( tByte iX, tByte iY, tByte iZ );
    bool  HasSolidRightNeighbour( tByte iX, tByte iY, tByte iZ );
    int  DataNeighbourCount( tByte iX, tByte iY, tByte iZ );

public:
    cStaticLodChunkN*  GetNeighbour( eChunkNeighbour  iNeighbour );
    void  SetNeighbour( eChunkNeighbour  iNeighbour, cStaticLodChunkN* iAdress );

private:
    tByte mData[N][N][N];
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

    if( iVal == 0 )
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
inline const tByte & cStaticLodChunkN<N>::GetData(tByte iX,tByte iY,tByte iZ) const
{
    return  mData[iX][iY][iZ];
}

template<tByte N>
inline void cStaticLodChunkN<N>::SetData(tByte iX,tByte iY,tByte iZ, tByte iValue)
{
    tByte oldValue = mData[iX][iY][iZ];
    mData[iX][iY][iZ] = iValue;

    tByte flag = tByte( bool( oldValue ) ) << 1 | tByte( bool( iValue ) );
    if( flag == 2 ) --mOccupiedVolume;
    if( flag == 1 ) ++mOccupiedVolume;
}

template<tByte N>
inline bool cStaticLodChunkN<N>::IsSolid(tByte iX,tByte iY,tByte iZ)
{
    return  bool( mData[iX][iY][iZ] );
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