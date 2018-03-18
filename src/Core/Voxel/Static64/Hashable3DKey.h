#pragma once

#include "Voxel/Static64/Utils.h"


namespace  nVoxel
{


class  cHashable3DKey
{

public:
    cHashable3DKey( tKeyComponent iX, tKeyComponent iY, tKeyComponent iZ );

public:
    void  Set( tKeyComponent iX, tKeyComponent iY, tKeyComponent iZ );
    void  SetX( tKeyComponent iValue );
    void  SetY( tKeyComponent iValue );
    void  SetZ( tKeyComponent iValue );

    tKeyComponent  GetX()  const;
    tKeyComponent  GetY()  const;
    tKeyComponent  GetZ()  const;

    const  tHashedKeySignature&  HashedSignature()  const;

private:
    void  InvalidCache()  const;
    void  UpdateHashedSignatureCache()  const;

private:
    tKeyComponent  mX;
    tKeyComponent  mY;
    tKeyComponent  mZ;
    mutable  bool  mCacheValid;
    mutable  tHashedKeySignature  mCachedHashedSignature;
};



} // namespace  nVoxel