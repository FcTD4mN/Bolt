#pragma once

#include "SFML/Graphics.hpp"

#define kPI 3.141592653589793238463




bool IsPointInTriangle( sf::Vector2f& pt, sf::Vector2f& v1, sf::Vector2f& v2, sf::Vector2f& v3 );
double  GetAngleBetweenVectors( sf::Vector2f& p1, sf::Vector2f& p2 );




template< typename T >
T
RoundToClosestIntegerFactor( T iNumericValue, int iInteger )
{
    T  castIntegerValue = static_cast< T >( iInteger );
    return  round( iNumericValue / castIntegerValue ) * castIntegerValue;
}

template< typename T >
T
FloorToClosestIntegerFactor( T iNumericValue, int iInteger )
{
    T  castIntegerValue = static_cast< T >( iInteger );
    return  floor( iNumericValue / castIntegerValue ) * castIntegerValue;
}



// Triangle computations
inline
float
Sign( sf::Vector2f& p1, sf::Vector2f& p2, sf::Vector2f& p3 )
{
    return ( p1.x - p3.x ) * ( p2.y - p3.y ) - ( p2.x - p3.x ) * ( p1.y - p3.y );
}


inline
double
DegToRad( double iAngle )
{
    return  iAngle * kPI / 180.0;
}


inline
double
RadToDeg( double iAngle )
{
    return  iAngle * 180.0/kPI;
}

//...