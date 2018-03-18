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
    void            Fill( tByte iVal );

public:
    tByte* operator()( tByte iX, tByte iY, tByte iZ );

public:
    cStaticLodChunkN*  Neighbour( eChunkNeighbour  iNeighbour );

private:
    tByte mData[N][N][N];
    cStaticLodChunkN*  mNeighbour[6];
    static  const  int  mCapacity = N * N * N;
};


template< tByte N >
cStaticLodChunkN< N >::cStaticLodChunkN()
{
}


template< tByte N >
inline cStaticLodChunkN< N >::cStaticLodChunkN( tByte iVal )
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
inline void cStaticLodChunkN<N>::Fill(tByte iVal)
{
    IJK_ITERATION_BEGIN( N )
        mData[i][j][k] = iVal;
    IJK_ITERATION_END
}


template<tByte N>
inline tByte* cStaticLodChunkN<N>::operator()( tByte iX,tByte iY,tByte iZ )
{
    return  &mData[iX][iY][iZ];
}



template<tByte N>
cStaticLodChunkN< N >*
cStaticLodChunkN< N >::Neighbour( eChunkNeighbour  iNeighbour )
{
    return  mNeighbour[ iNeighbour ];
}



} // namespace  nVoxel