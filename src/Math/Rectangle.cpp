
#include "Math/Rectangle.h"

// ==============================================Contruction
cRectangle::cRectangle() :
    mX( 0 ),
    mY( 0 ),
    mW( 0 ),
    mH( 0 )
{
}

cRectangle::cRectangle( double iX, double iY, double iW, double iH ) :
    mX( iX ),
    mY( iY ),
    mW( iW ),
    mH( iH )
{
}


// ==============================================Access/Get
double
cRectangle::X() const
{
    return  mX;
}

void
cRectangle::X( double  iX )
{
    mX = iX;
}

double
cRectangle::Y() const
{
    return  mY;
}

void
cRectangle::Y( double  iY )
{
    mY = iY;
}

double
cRectangle::X2() const
{
    return  mX2;
}

void
cRectangle::X2( double  iX )
{
    if( iX < mX )
    {
        mX2 = mX;
        mX = iX;
    }
    else
    {
        mX2 = iX;
    }

    mW = mX2 - mX;
}

double
cRectangle::Y2() const
{
    return  mY2;
}

void
cRectangle::Y2( double  iY )
{
    if( iY < mY )
    {
        mY2 = mY;
        mY = iY;
    }
    else
    {
        mY2 = iY;
    }

    mH = mY2 - mY;
}

double
cRectangle::W() const
{
    return  mW;
}

void
cRectangle::W( double  iW )
{
    mW = iW;
    mX2 = mX + mW;
}

double
cRectangle::H() const
{
    return  mH;
}

void
cRectangle::H( double  iH )
{
    mH = iH;
    mY2 = mY + mH;
}



// ==============================================Computing
bool
cRectangle::ContainsPoint( double iX, double iY ) const
{
    if( iX < mX )
        return  false;
    if( iY < mY )
        return  false;
    if( iX > mX2)
        return  false;
    if( iY > mY2)
        return  false;

    return  true;
}

bool
cRectangle::ContainsRectangleEntirely( const cRectangle& iRectangle ) const
{
    if( iRectangle.mX < mX )
        return  false;
    if( iRectangle.mY < mY )
        return  false;
    if( iRectangle.mX2 > mX2 )
        return  false;
    if( iRectangle.mY2 > mY2 )
        return  false;

    return  true;
}
