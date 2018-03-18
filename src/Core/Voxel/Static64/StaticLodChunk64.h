#pragma once

#include "Voxel/Static64/Utils.h"


namespace  nVoxel
{


class  cStaticLodChunk64
{

public:
    // Construction / Destruction
    cStaticLodChunk64();
    cStaticLodChunk64( tByte iVal );
    cStaticLodChunk64( const  cStaticLodChunk64& ) = delete;

public:
    // Volume Information
    inline  tByte           Size()              const;
    inline  unsigned  int   Capacity()          const;
    inline  unsigned  int   OccupiedVolume()    const;
    inline  bool            IsFull()            const;
    inline  bool            IsEmpty()           const;

public:
    // Volume Manipulation
    void  Fill( tByte iVal );

public:
    // Material Accessors
    tByte  GetMaterial( tLocalDataIndex iX, tLocalDataIndex iY, tLocalDataIndex iZ )  const;
    void  SetMaterial( tLocalDataIndex iX, tLocalDataIndex iY, tLocalDataIndex iZ, tByte iValue );
    bool  IsSolid( tLocalDataIndex iX, tLocalDataIndex iY, tLocalDataIndex iZ )  const;

public:
    // Neighbour Accessors
    cStaticLodChunk64*  GetNeighbour( eChunkNeighbourIndex  iNeighbourIndex );
    void  SetNeighbour( eChunkNeighbourIndex  iNeighbourIndex, cStaticLodChunk64* iAdress );

private:
    // Data Manipulation
    const  t2Byte&  GetData( tLocalDataIndex iX, tLocalDataIndex iY, tLocalDataIndex iZ )  const;
    void  SetData( tLocalDataIndex iX, tLocalDataIndex iY, tLocalDataIndex iZ, t2Byte iValue );
    const  t2Byte&  SafeExternGetData( tGlobalDataIndex iX, tGlobalDataIndex iY, tGlobalDataIndex iZ );
    void  SafeExternSetData( tGlobalDataIndex iX, tGlobalDataIndex iY, tGlobalDataIndex iZ, t2Byte iValue );
    t2Byte  SafeExternIsSolid( tGlobalDataIndex iX, tGlobalDataIndex iY, tGlobalDataIndex iZ );
    cStaticLodChunk64*  ExternChunkFromCoordinates( tGlobalDataIndex iX, tGlobalDataIndex iY, tGlobalDataIndex iZ );

private:
    static  const  tByte  msSize = 64;
    static  const  unsigned  int  msCapacity = msSize * msSize * msSize; // size^3
    t2Byte  mData[msSize][msSize][msSize];
    cStaticLodChunk64*  mNeighbour[6] = { 0, 0, 0, 0, 0, 0 }; // six neighbours
    unsigned  int  mOccupiedVolume;

};


} // namespace  nVoxel