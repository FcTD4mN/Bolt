#pragma once

#include "Volumetric/Static/Types.h"


namespace  nVolumetric
{


class  cHashable3DKey
{

public:
    cHashable3DKey( tKeyComponent iX, tKeyComponent iY, tKeyComponent iZ );
    cHashable3DKey( tHashableKeySignature iHashedSignature );

public:
    void  Set( tKeyComponent iX, tKeyComponent iY, tKeyComponent iZ );
    void  Set( tHashableKeySignature iHashedSignature );
    void  SetX( tKeyComponent iValue );
    void  SetY( tKeyComponent iValue );
    void  SetZ( tKeyComponent iValue );

    tKeyComponent  GetX()  const;
    tKeyComponent  GetY()  const;
    tKeyComponent  GetZ()  const;

    const  tHashableKeySignature&  HashedSignature()  const;

    cHashable3DKey  Top()  const;
    cHashable3DKey  Bot()  const;
    cHashable3DKey  Front()  const;
    cHashable3DKey  Back()  const;
    cHashable3DKey  Left()  const;
    cHashable3DKey  Right()  const;

private:
    void  InvalidCache()  const;
    void  UpdateHashedSignatureCache()  const;

private:
    // Private Data Members
    tKeyComponent  mX;
    tKeyComponent  mY;
    tKeyComponent  mZ;
    mutable  bool  mCacheValid;
    mutable  tHashableKeySignature  mCachedHashedSignature;
};



} // namespace  nVolumetric

