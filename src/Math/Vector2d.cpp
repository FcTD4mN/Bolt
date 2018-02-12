#include "Math/Vector2d.h"

#include <math.h>

// ==============================================Contruction
cVector2d::cVector2d() :
    mX( 0 ),
    mY ( 0 )
{
}


cVector2d::cVector2d( double iX, double iY ) :
    mX( iX ),
    mY( iY )
{
}


// ==============================================Access/Get
double
cVector2d::X() const
{
    return  mX;
}


void
cVector2d::X( double  iX )
{
    mX = iX;
}


double
cVector2d::Y() const
{
    return  mY;
}


void
cVector2d::Y( double  iY )
{
    mY = iY;
}


// ==============================================Computing
cVector2d
cVector2d::Normalized() const
{
    cVector2d normalizedVector( mX, mY );
    double length = Length();
    normalizedVector.X( mX / length );
    normalizedVector.Y( mY / length );

    return  normalizedVector;
}


cVector2d
cVector2d::NormalCounterClockWise()
{
    double x = -mY;
    double y = mX;
    return  cVector2d( x, y );
}

double
cVector2d::Length() const
{
    return  sqrt( mX * mX + mY * mY );
}

double
cVector2d::LengthSquared() const
{
    return  mX * mX + mY * mY;
}


void
cVector2d::operator+( const cVector2d& iRhs )
{
    mX += iRhs.mX;
    mY += iRhs.mY;
}

void
cVector2d::operator-( const cVector2d& iRhs )
{
    mX -= iRhs.mX;
    mY -= iRhs.mY;
}

void
cVector2d::operator*( double iRhs )
{
    mX *= iRhs;
    mY *= iRhs;
}


