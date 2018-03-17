#pragma once

#include "Voxel/Basic/Types.h"


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
    tByte   Size();
    void    Fill( tByte iVal );

public:
    const   tByte&  Data( tByte iX, tByte iY, tByte iZ )  const;
            tByte&  Data( tByte iX, tByte iY, tByte iZ );

public:
    cStaticLodChunkN*  Neighbour( eChunkNeighbour  iNeighbour );

private:
    tByte mData[N][N][N];
    cStaticLodChunkN*  mNeighbour[sgChunkMaxNeighbours];
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
inline void cStaticLodChunkN<N>::Fill(tByte iVal)
{
    IJK_ITERATION_BEGIN( N )
        mData[i][j][k] = iVal;
    IJK_ITERATION_END
}


template<tByte N>
const  tByte&
cStaticLodChunkN< N >::Data( tByte iX, tByte iY, tByte iZ )  const
{
    return  mData[iX][iY][iZ];
}


template<tByte N>
tByte&
cStaticLodChunkN< N >::Data( tByte iX, tByte iY, tByte iZ )
{
    return  mData[iX][iY][iZ];
}


template<tByte N>
cStaticLodChunkN< N >*
cStaticLodChunkN< N >::Neighbour( eChunkNeighbour  iNeighbour )
{
    return  mNeighbour[ iNeighbour ];
}



} // namespace  nVoxel