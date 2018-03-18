#include "Bitvolume/Static64/StaticLodChunk64.h"


namespace  nBitvolume
{

//----------------------------------------------------------------------------------------------
//------------------------------------------------------------------- Construction / Destruction


cStaticLodChunk64::cStaticLodChunk64() :
    mOccupiedVolume( 0 )
{
}


 cStaticLodChunk64::cStaticLodChunk64( tByte iVal ) :
    mOccupiedVolume( 0 )
{
    Fill( iVal );
}


//----------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------- Volume Information


tByte cStaticLodChunk64::Size()  const
{
    return  msSize;
}


unsigned  int 
cStaticLodChunk64::Capacity()  const
{
    return  msCapacity;
}


unsigned  int
cStaticLodChunk64::OccupiedVolume()  const
{
    return  mOccupiedVolume;
}


bool
cStaticLodChunk64::IsFull()  const
{
    return  mOccupiedVolume == msCapacity;
}


bool
cStaticLodChunk64::IsEmpty()  const
{
    return  mOccupiedVolume == 0;
}


//----------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------- Volume Manipulation


void
cStaticLodChunk64::Fill(tByte iVal)
{
    IJK_ITERATION_BEGIN( msSize )
        mData[i][j][k] = iVal;
    IJK_ITERATION_END

    if( iVal == sgEmptyMaterial )
        mOccupiedVolume = 0;
    else
        mOccupiedVolume = msCapacity;
}


//----------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------- Material Accessors


tByte
cStaticLodChunk64::GetMaterial( tLocalDataIndex iX, tLocalDataIndex iY, tLocalDataIndex iZ )  const
{
    return  tByte( GetData(iX,iY,iZ) & sgFirstByteMask );
}


void
 cStaticLodChunk64::SetMaterial( tLocalDataIndex iX, tLocalDataIndex iY, tLocalDataIndex iZ, tByte iValue )
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


bool
 cStaticLodChunk64::IsSolid( tLocalDataIndex iX, tLocalDataIndex iY, tLocalDataIndex iZ )  const
{
    return  mData[iX][iY][iZ].GetMaterialField() != sgEmptyMaterial;
}


//----------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------- Neighbour Accessors



cStaticLodChunk64*
cStaticLodChunk64::GetNeighbour( eChunkNeighbourIndex  iNeighbour )  const
{
    return  mNeighbour[ iNeighbour ];
}


void cStaticLodChunk64::SetNeighbour( eChunkNeighbourIndex iNeighbour, cStaticLodChunk64* iAdress )
{
    mNeighbour[ iNeighbour ] = iAdress;
}


//----------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------- Data Manipulation


const  t2Byte&
cStaticLodChunk64::GetData( tLocalDataIndex iX, tLocalDataIndex iY, tLocalDataIndex iZ )  const
{
    return  mData[iX][iY][iZ].GetDataField();
}


void
cStaticLodChunk64::SetData( tLocalDataIndex iX, tLocalDataIndex iY, tLocalDataIndex iZ, t2Byte iValue )
{
    mData[iX][iY][iZ] = iValue;
}


const  t2Byte&
cStaticLodChunk64::SafeExternGetData( tGlobalDataIndex iX, tGlobalDataIndex iY, tGlobalDataIndex iZ)
{
    auto chunk = ExternChunkFromCoordinates( iX, iY, iZ );
    tLocalDataIndex safeX = iX % msSize;
    tLocalDataIndex safeY = iY % msSize;
    tLocalDataIndex safeZ = iZ % msSize;
    return  chunk->GetData( safeX, safeY, safeZ );
}


void
cStaticLodChunk64::SafeExternSetData( tGlobalDataIndex iX, tGlobalDataIndex iY, tGlobalDataIndex iZ, t2Byte iValue )
{
    auto chunk = ExternChunkFromCoordinates( iX, iY, iZ );
    tLocalDataIndex safeX = iX % msSize;
    tLocalDataIndex safeY = iY % msSize;
    tLocalDataIndex safeZ = iZ % msSize;
    return  chunk->SetData( safeX, safeY, safeZ, iValue );
}


t2Byte
cStaticLodChunk64::SafeExternIsSolid( tGlobalDataIndex iX, tGlobalDataIndex iY, tGlobalDataIndex iZ )
{
    auto chunk = ExternChunkFromCoordinates( iX, iY, iZ );
    tLocalDataIndex safeX = iX % msSize;
    tLocalDataIndex safeY = iY % msSize;
    tLocalDataIndex safeZ = iZ % msSize;
    return  chunk->IsSolid( safeX, safeY, safeZ );
}



 cStaticLodChunk64*
cStaticLodChunk64::ExternChunkFromCoordinates( tGlobalDataIndex iX, tGlobalDataIndex iY, tGlobalDataIndex iZ )
{
    if( ( iX & sgMaxLocalDataIndex ) &&
        ( iY & sgMaxLocalDataIndex ) &&
        ( iZ & sgMaxLocalDataIndex ) )
    {
        return  this;
    }
    else
    {
        if( iY < 0 )        return  mNeighbour[ eChunkNeighbourIndex::kTop ];
        if( iY >= msSize )  return  mNeighbour[ eChunkNeighbourIndex::kBot ];
        if( iZ < 0 )        return  mNeighbour[ eChunkNeighbourIndex::kFront ];
        if( iZ >= msSize )  return  mNeighbour[ eChunkNeighbourIndex::kBack ];
        if( iX < 0 )        return  mNeighbour[ eChunkNeighbourIndex::kLeft ];
        if( iX >= msSize )  return  mNeighbour[ eChunkNeighbourIndex::kRight ];
    }

    return  NULL;
}

} // namespace  nBitvolume