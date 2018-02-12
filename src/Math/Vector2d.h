#pragma once

class cVector2d
{

public:
    // Contruction
    cVector2d();
    cVector2d( double iX, double iY );

public:
    // Access/Get
    double X() const;
    void X( double  iX );

    double Y() const;
    void Y( double  iY );

public:
    // Computing
    cVector2d Normalized() const;
    cVector2d NormalCounterClockWise();
    double Length() const;
    double LengthSquared() const;

    void operator+( const cVector2d& iRhs );
    void operator-( const cVector2d& iRhs );
    void operator*( double iRhs );

private:
    double mX;
    double mY;
};

