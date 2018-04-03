#include "Volumetric.SparseOctree.Hashable3DKey.h"


namespace  nVolumetric      {
namespace  nSparseOctree    {


cHashable3DKey::cHashable3DKey( tIndex iX, tIndex iY, tIndex iZ ) :
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
cHashable3DKey::Set( tIndex iX, tIndex iY, tIndex iZ )
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

    mX = tIndex( (   ( mCachedHashedSignature & tHashableKeySignature( 0x0000FFFF00000000 ) ) >> 32 )    - sgSignedKeyComponentRangeShift );
    mY = tIndex( (   ( mCachedHashedSignature & tHashableKeySignature( 0x00000000FFFF0000 ) ) >> 16 )    - sgSignedKeyComponentRangeShift );
    mZ = tIndex( (     mCachedHashedSignature & tHashableKeySignature( 0x000000000000FFFF ) )            - sgSignedKeyComponentRangeShift );
}


void
cHashable3DKey::SetX( tIndex iValue )
{
    mX = iValue;
    InvalidCache();
}


void
cHashable3DKey::SetY( tIndex iValue )
{
    mX = iValue;
    InvalidCache();
}


void
cHashable3DKey::SetZ( tIndex iValue )
{
    mX = iValue;
    InvalidCache();
}


tIndex
cHashable3DKey::GetX()  const
{
    return  mX;
}


tIndex
cHashable3DKey::GetY()  const
{
    return  mY;
}


tIndex
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


} // namespace  nSparseOctree
} // namespace  nVolumetric

