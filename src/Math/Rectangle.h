#pragma once

class cRectangle
{

public:
    // Contruction
    cRectangle();
    cRectangle( double iX, double iY, double iW, double iH );

public:
    // Access/Get
    double X() const;
    void X( double  iX );

    double Y() const;
    void Y( double  iY );

    double X2() const;
    void X2( double  iX );

    double Y2() const;
    void Y2( double  iY );

    double W() const;
    void W( double  iW );

    double H() const;
    void H( double  iH );

public:
    // Computing
    bool ContainsPoint( double iX, double iY ) const;
    bool ContainsRectangleEntirely( const cRectangle& iRectangle ) const;



private:
    double mX;
    double mY;
    double mX2;
    double mY2;
    double mW;
    double mH;

};

