#include "Triangle.h"


#include "Math/Utils.h"


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------ Construction
// -------------------------------------------------------------------------------------


cTriangleF::~cTriangleF()
{
}


cTriangleF::cTriangleF() :
    mA( sf::Vector2f( 0.0F, 0.0F ) ),
    mB( sf::Vector2f( 0.0F, 0.0F ) ),
    mC( sf::Vector2f( 0.0F, 0.0F ) )
{
}


cTriangleF::cTriangleF( const sf::Vector2f& iA, const sf::Vector2f& iB, const sf::Vector2f& iC ) :
    mA( iA ),
    mB( iB ),
    mC( iC )
{
}


bool
cTriangleF::Contains( const sf::Vector2f& iPoint )
{
    bool b1, b2, b3;

    b1 = Sign( iPoint, mA, mB ) < 0.0f;
    b2 = Sign( iPoint, mB, mC ) < 0.0f;
    b3 = Sign( iPoint, mC, mA ) < 0.0f;

    return  ( ( b1 == b2 ) && ( b2 == b3 ) );
}

