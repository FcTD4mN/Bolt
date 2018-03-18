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
    for( tLocalDataIndex  i = 0; i < msSize; ++i )
    {
        for( tLocalDataIndex  j = 0; j < msSize; ++j )
        {
            for( tLocalDataIndex  k = 0; k < msSize; ++k )
            {
                mData[i][j][k] = iVal;
            }
        }
    }

    if( iVal == sgEmptyMaterial )
        mOccupiedVolume = 0;
    else
        mOccupiedVolume = msCapacity;
}


//----------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------- Material Accessors


bool
 cStaticLodChunk64::IsSolid( tLocalDataIndex iX, tLocalDataIndex iY, tLocalDataIndex iZ )  const
{
    return  mData[iX][iY][iZ].IsSolid();
}


tByte
cStaticLodChunk64::GetMaterial( tLocalDataIndex iX, tLocalDataIndex iY, tLocalDataIndex iZ )  const
{
    return  mData[iX][iY][iZ].GetMaterialField();
}


void
 cStaticLodChunk64::SetMaterial( tLocalDataIndex iX, tLocalDataIndex iY, tLocalDataIndex iZ, tByte iValue )
{
    tByte oldMat = GetMaterial( iX, iY, iZ );
    mData[iX][iY][iZ].SetMaterialField( iValue );

    tByte flag = tByte( bool( oldMat ) ) << 1 | tByte( bool( iValue ) );
    // Bitfield manipulation:
    // 11   old solid - new solid   - 3 - no change
    // 10   old solid - new empty   - 2 - decrease occupied volume
    // 01   old empty - new solid   - 1 - increase occupied volume
    // 00   old empty - new empty   - 0 - no change
    if( flag == 2 ) --mOccupiedVolume;
    if( flag == 1 ) ++mOccupiedVolume;

    if( flag == 1 || flag == 2 )    // Update neighbours in case of change
    {
        UpdateDataNeighbours( iX, iY, iZ );
    }
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
    mData[iX][iY][iZ].SetDataField( iValue );
}


cData*
cStaticLodChunk64::DataHandle( tLocalDataIndex iX, tLocalDataIndex iY, tLocalDataIndex iZ )
{
    return  &mData[iX][iY][iZ];
}


void
cStaticLodChunk64::UpdateDataNeighbours( tLocalDataIndex iX, tLocalDataIndex iY, tLocalDataIndex iZ )
{
    cData* currentHandle    = DataHandle( iX, iY, iZ );
    bool  currentIsSolid = currentHandle->IsSolid();
    cData* topDataHandle    = GetSafeExternDataHandle( iX,     iY-1,   iZ      );
    cData* botDataHandle    = GetSafeExternDataHandle( iX,     iY+1,   iZ      );
    cData* frontDataHandle  = GetSafeExternDataHandle( iX,     iY,     iZ-1    );
    cData* backDataHandle   = GetSafeExternDataHandle( iX,     iY,     iZ+1    );
    cData* leftDataHandle   = GetSafeExternDataHandle( iX-1,   iY,     iZ      );
    cData* rightDataHandle  = GetSafeExternDataHandle( iX+1,   iY,     iZ      );

    if( topDataHandle )
    {
        currentHandle->SetNeighbour( cData::eDataNeighbourFlag::kTop, topDataHandle->IsSolid() );
        topDataHandle->SetNeighbour( cData::eDataNeighbourFlag::kBot, currentIsSolid );
    }

    if( botDataHandle )
    {
        currentHandle->SetNeighbour( cData::eDataNeighbourFlag::kBot, botDataHandle->IsSolid() );
        botDataHandle->SetNeighbour( cData::eDataNeighbourFlag::kTop, currentIsSolid );
    }

    if( frontDataHandle )
    {
        currentHandle->SetNeighbour( cData::eDataNeighbourFlag::kFront, frontDataHandle->IsSolid() );
        frontDataHandle->SetNeighbour( cData::eDataNeighbourFlag::kBack, currentIsSolid );
    }

    if( backDataHandle )
    {
        currentHandle->SetNeighbour( cData::eDataNeighbourFlag::kBack, backDataHandle->IsSolid() );
        backDataHandle->SetNeighbour( cData::eDataNeighbourFlag::kFront, currentIsSolid );
    }

    if( leftDataHandle )
    {
        currentHandle->SetNeighbour( cData::eDataNeighbourFlag::kLeft, leftDataHandle->IsSolid() );
        leftDataHandle->SetNeighbour( cData::eDataNeighbourFlag::kRight, currentIsSolid );
    }

    if( rightDataHandle )
    {
        currentHandle->SetNeighbour( cData::eDataNeighbourFlag::kRight, rightDataHandle->IsSolid() );
        rightDataHandle->SetNeighbour( cData::eDataNeighbourFlag::kLeft, currentIsSolid );
    }
}



cData*
cStaticLodChunk64::GetSafeExternDataHandle( tGlobalDataIndex iX, tGlobalDataIndex iY, tGlobalDataIndex iZ )
{
    auto chunk = GetSafeExternChunkHandle( iX, iY, iZ );
    if( !chunk )
        return  NULL;

    tLocalDataIndex safeX = iX % msSize;
    tLocalDataIndex safeY = iY % msSize;
    tLocalDataIndex safeZ = iZ % msSize;
    return  chunk->DataHandle( safeX, safeY, safeZ );
}


 cStaticLodChunk64*
cStaticLodChunk64::GetSafeExternChunkHandle( tGlobalDataIndex iX, tGlobalDataIndex iY, tGlobalDataIndex iZ )
{
    if( ( iX >= 0 && iX < msSize ) &&
        ( iY >= 0 && iY < msSize ) &&
        ( iZ >= 0 && iZ < msSize ) )
    {
        return  this;
    }
    else
    {
        if( iY == -1 )      return  mNeighbour[ eChunkNeighbourIndex::kTop ];
        if( iY == msSize )  return  mNeighbour[ eChunkNeighbourIndex::kBot ];
        if( iZ == -1 )      return  mNeighbour[ eChunkNeighbourIndex::kFront ];
        if( iZ == msSize )  return  mNeighbour[ eChunkNeighbourIndex::kBack ];
        if( iX == -1 )      return  mNeighbour[ eChunkNeighbourIndex::kLeft ];
        if( iX == msSize )  return  mNeighbour[ eChunkNeighbourIndex::kRight ];
    }

    return  NULL;
}

} // namespace  nBitvolume