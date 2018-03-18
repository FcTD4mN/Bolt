#include "Voxel/Static64/Hashable3DKey.h"

namespace  nVoxel
{

cHashable3DKey::cHashable3DKey( tKeyComponent iX, tKeyComponent iY, tKeyComponent iZ ) :
    mX( iX ),
    mY( iY ),
    mZ( iZ ),
    mCacheValid( false ),
    mCachedHashedSignature( 0 )
{
}


void
cHashable3DKey::Set( tKeyComponent iX, tKeyComponent iY, tKeyComponent iZ )
{
    mX = iX;
    mY = iY;
    mZ = iZ;
    InvalidCache();
}


void
cHashable3DKey::SetX( tKeyComponent iValue )
{
    mX = iValue;
    InvalidCache();
}


void
cHashable3DKey::SetY( tKeyComponent iValue )
{
    mX = iValue;
    InvalidCache();
}


void
cHashable3DKey::SetZ( tKeyComponent iValue )
{
    mX = iValue;
    InvalidCache();
}


tKeyComponent
cHashable3DKey::GetX()  const
{
    return  mX;
}


tKeyComponent
cHashable3DKey::GetY()  const
{
    return  mY;
}


tKeyComponent
cHashable3DKey::GetZ()  const
{
    return  mZ;
}


const  tHashedKeySignature&
cHashable3DKey::HashedSignature()  const
{
    UpdateHashedSignatureCache();
    return  mCachedHashedSignature;
}


cHashable3DKey
cHashable3DKey::Top()  const
{
    return  cHashable3DKey( mX, mY-1, mZ );
}


cHashable3DKey
cHashable3DKey::Bot()  const
{
    return  cHashable3DKey( mX, mY+1, mZ );
}


cHashable3DKey
cHashable3DKey::Front()  const
{
    return  cHashable3DKey( mX, mY, mZ-1 );
}



cHashable3DKey
cHashable3DKey::Back()  const
{
    return  cHashable3DKey( mX, mY, mZ+1 );
}



cHashable3DKey
cHashable3DKey::Left()  const
{
    return  cHashable3DKey( mX-1, mY, mZ );
}



cHashable3DKey
cHashable3DKey::Right()  const
{
    return  cHashable3DKey( mX+1, mY, mZ );
}


void
cHashable3DKey::InvalidCache()  const
{
    mCacheValid = false;
}


void
cHashable3DKey::UpdateHashedSignatureCache()  const
{
    if( mCacheValid )
        return;

    mCachedHashedSignature = tHashedKeySignature( mX ) << 32 |
                             tHashedKeySignature( mY ) << 16 |
                             tHashedKeySignature( mZ );

    mCacheValid = true;
}


} // namespace  nVoxel