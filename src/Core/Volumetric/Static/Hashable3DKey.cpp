#include "Volumetric/Static/Hashable3DKey.h"

namespace  nVolumetric
{

cHashable3DKey::cHashable3DKey( tKeyComponent iX, tKeyComponent iY, tKeyComponent iZ ) :
    mX( iX ),
    mY( iY ),
    mZ( iZ ),
    mCacheValid( false ),
    mCachedHashedSignature( 0 )
{
}


cHashable3DKey::cHashable3DKey( tHashableKeySignature iHashedSignature ) :
    mX( 0 ),
    mY( 0 ),
    mZ( 0 ),
    mCacheValid( true ),
    mCachedHashedSignature( iHashedSignature )
{
    Set( iHashedSignature );
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
cHashable3DKey::Set( tHashableKeySignature iHashedSignature )
{
    mCachedHashedSignature = iHashedSignature;
    mCacheValid = true;

    mX = tKeyComponent( (   ( mCachedHashedSignature & tHashableKeySignature( 0x0000FFFF00000000 ) ) >> 32 )    - sgSignedKeyComponentRangeShift );
    mY = tKeyComponent( (   ( mCachedHashedSignature & tHashableKeySignature( 0x00000000FFFF0000 ) ) >> 16 )    - sgSignedKeyComponentRangeShift );
    mZ = tKeyComponent( (     mCachedHashedSignature & tHashableKeySignature( 0x000000000000FFFF ) )            - sgSignedKeyComponentRangeShift );
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


const  tHashableKeySignature&
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

    mCachedHashedSignature = tHashableKeySignature( tHashableKeySignature( mX ) + sgSignedKeyComponentRangeShift ) << 32 |
                             tHashableKeySignature( tHashableKeySignature( mY ) + sgSignedKeyComponentRangeShift ) << 16 |
                             tHashableKeySignature( tHashableKeySignature( mZ ) + sgSignedKeyComponentRangeShift );

    mCacheValid = true;
}


} // namespace  nVolumetric

