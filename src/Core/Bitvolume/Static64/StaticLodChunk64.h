#pragma once

#include "Bitvolume/Static64/Types.h"
#include "Bitvolume/Static64/Data.h"


namespace  nBitvolume
{


class  cStaticLodChunk64
{

public:
enum  eChunkNeighbourIndex : tByte
{
    kTop    = 0,
    kBot    = 1,
    kFront  = 2,
    kBack   = 3,
    kLeft   = 4,
    kRight  = 5,
};

public:
    // Construction / Destruction
    cStaticLodChunk64();
    cStaticLodChunk64( tByte iVal );
    cStaticLodChunk64( const  cStaticLodChunk64& ) = delete;

public:
    // Volume Information
    tByte           Size()              const;
    unsigned  int   Capacity()          const;
    unsigned  int   OccupiedVolume()    const;
    bool            IsFull()            const;
    bool            IsEmpty()           const;

public:
    // Volume Manipulation
    void  Fill( tByte iVal );

public:
    // Material Accessors
    bool    IsSolid( tLocalDataIndex iX, tLocalDataIndex iY, tLocalDataIndex iZ )       const;
    tByte   GetMaterial( tLocalDataIndex iX, tLocalDataIndex iY, tLocalDataIndex iZ )   const;
    void    SetMaterial( tLocalDataIndex iX, tLocalDataIndex iY, tLocalDataIndex iZ, tByte iValue );

public:
    // Neighbour Accessors
    cStaticLodChunk64*  GetNeighbour( eChunkNeighbourIndex  iNeighbourIndex )  const;
    void                SetNeighbour( eChunkNeighbourIndex  iNeighbourIndex, cStaticLodChunk64* iAdress );

private:
    // Data Manipulation
    const  t2Byte&  GetData( tLocalDataIndex iX, tLocalDataIndex iY, tLocalDataIndex iZ )  const;
    void            SetData( tLocalDataIndex iX, tLocalDataIndex iY, tLocalDataIndex iZ, t2Byte iValue );
    cData*          DataHandle( tLocalDataIndex iX, tLocalDataIndex iY, tLocalDataIndex iZ );
    void            UpdateDataNeighbours( tLocalDataIndex iX, tLocalDataIndex iY, tLocalDataIndex iZ );

    cData*  GetSafeExternDataHandle( tGlobalDataIndex iX, tGlobalDataIndex iY, tGlobalDataIndex iZ );
    cStaticLodChunk64*  GetSafeExternChunkHandle( tGlobalDataIndex iX, tGlobalDataIndex iY, tGlobalDataIndex iZ );

private:
    // Private Data Members
    static  const  tByte            msSize = 64;
    static  const  unsigned  int    msCapacity = msSize * msSize * msSize; // size^3
    unsigned  int                   mOccupiedVolume;
    cStaticLodChunk64*              mNeighbour[6] = { 0, 0, 0, 0, 0, 0 }; // six neighbours
    cData                           mData[msSize][msSize][msSize];

};


} // namespace  nBitvolume