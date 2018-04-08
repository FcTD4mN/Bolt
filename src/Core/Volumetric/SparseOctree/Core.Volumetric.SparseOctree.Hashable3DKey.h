#pragma once


#include "Core.Volumetric.SparseOctree.Types.h"


namespace  nVolumetric      {
namespace  nSparseOctree    {


class  cHashable3DKey
{

public:
    cHashable3DKey( tIndex iX, tIndex iY, tIndex iZ );
    cHashable3DKey( tHashableKeySignature iHashedSignature );

public:
    void  Set( tIndex iX, tIndex iY, tIndex iZ );
    void  Set( tHashableKeySignature iHashedSignature );
    void  SetX( tIndex iValue );
    void  SetY( tIndex iValue );
    void  SetZ( tIndex iValue );

    tIndex  GetX()  const;
    tIndex  GetY()  const;
    tIndex  GetZ()  const;

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
    tIndex  mX;
    tIndex  mY;
    tIndex  mZ;
    mutable  bool  mCacheValid;
    mutable  tHashableKeySignature  mCachedHashedSignature;
};


} // namespace  nSparseOctree
} // namespace  nVolumetric

