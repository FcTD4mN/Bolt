#pragma once

#include "Voxel/Types.h"


namespace  nVoxel
{

template< tByte N >
class  cStaticChunk
{

public:
    cStaticChunk();
    cStaticChunk( tByte iVal );
    cStaticChunk( const cStaticChunk& ) = delete;

public:
    tByte   Size();
    void    Fill( tByte iVal );

public:
    const   tByte&  Data( tByte iX, tByte iY, tByte iZ )  const;
            tByte&  Data( tByte iX, tByte iY, tByte iZ );

public:
    cStaticChunk*  Neighbour( eChunkNeighbour  iNeighbour );

private:
    tByte mData[N][N][N];
    cStaticChunk*  mNeighbour[sgChunkMaxNeighbours];
};


template< tByte N >
cStaticChunk< N >::cStaticChunk()
{
}


template< tByte N >
inline cStaticChunk< N >::cStaticChunk( tByte iVal )
{
    Fill( iVal );
}


template<tByte N>
inline tByte cStaticChunk<N>::Size()
{
    return  N;
}


template<tByte N>
inline void cStaticChunk<N>::Fill(tByte iVal)
{
    IJK_ITERATION_BEGIN( N )
        mData[i][j][k] = iVal;
    IJK_ITERATION_END
}


template<tByte N>
const  tByte&
cStaticChunk< N >::Data( tByte iX, tByte iY, tByte iZ )  const
{
    return  mData[iX][iY][iZ];
}


template<tByte N>
tByte&
cStaticChunk< N >::Data( tByte iX, tByte iY, tByte iZ )
{
    return  mData[iX][iY][iZ];
}


template<tByte N>
cStaticChunk< N >*
cStaticChunk< N >::Neighbour( eChunkNeighbour  iNeighbour )
{
    return  mNeighbour[ iNeighbour ];
}



} // namespace  nVoxel