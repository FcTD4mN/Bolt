#pragma once

#include "SFML/Graphics.hpp"

#include "Math/Edge.h"

/** Constant : PI in float format. */
#define kPIF (3.1415926535897932384626F)

/** Constant : some small epsilon in float format. */
#define kEpsilonF (1E-5F)


static sf::Vector2f gYAxisVector( 0.0F, 1.0F );
static sf::Vector2f gXAxisVector( 1.0F, 0.0F );
static sf::Vector2f gNULLVector( 0.0F, 0.0F );



bool            IsPointInTriangle( sf::Vector2f& pt, sf::Vector2f& v1, sf::Vector2f& v2, sf::Vector2f& v3 );
double          GetAngleBetweenVectors( const sf::Vector2f& p1, const sf::Vector2f& p2 );
sf::Vector2f    CenterOfGravity( const  sf::VertexArray& iPolygon );
sf::VertexArray CCWWindingSort( const sf::VertexArray& iPolygon );
sf::VertexArray PolygonPolygonInterectionList( const  sf::VertexArray& iPolygonA, const  sf::VertexArray& iPolygonB );
sf::VertexArray ClipPolygonPolygon( const  sf::VertexArray& iPolygonA, const  sf::VertexArray& iPolygonB );
bool            CCWWindedPolygonContainsPoint( const  sf::VertexArray& iPolygon, const sf::Vector2f& iPoint );
void            ExtractEdgesFromPolygon( std::vector< cEdgeF >* oEdges, const  sf::VertexArray& iPolygon );
sf::FloatRect   GetTriangleSetBBox( const std::vector < sf::VertexArray >& iTriangleSet );
sf::VertexArray SortVertexesByX( const sf::VertexArray& iPolygon );
void            TransformPolygonUsingTransformation( sf::VertexArray* oPolygon, const sf::Transform& iTransformation );

// ===================================================
// ===================================================


inline
float
DotProduct( const sf::Vector2f& iVector1, const sf::Vector2f& iVector2 )
{
    return  iVector1.x * iVector2.x + iVector1.y * iVector2.y;
}


// ===================================================
// ===================================================


inline
float
Magnitude( const sf::Vector2f& iVector )
{
    return  sqrt( iVector.x * iVector.x + iVector.y *iVector.y );
}


inline
void
Normalize( sf::Vector2f* oVector1 )
{
    *oVector1 = *oVector1 / Magnitude( *oVector1 );
}


inline
sf::Vector2f
Normale( const  sf::Vector2f& iVector1 )
{
    return  iVector1 / Magnitude( iVector1 );
}


inline
bool
Collinear( const sf::Vector2f& iVector1, const sf::Vector2f& iVector2 )
{
    if( iVector1 == iVector2 )
        return  true;

    bool x10 = iVector1.x == 0;
    bool y10 = iVector1.y == 0;
    bool x20 = iVector2.x == 0;
    bool y20 = iVector2.y == 0;
    if( x10 && x20 ) return  true;
    if( y10 && y20 ) return  true;

    if( x10 != x20 ) return  false;
    if( y10 != y20 ) return  false;

    return  abs(( iVector1.x / iVector2.x ) - ( iVector1.y / iVector2.y )) < kEpsilonF;
}


inline
sf::Vector2f
Orthogonal( const sf::Vector2f& iVector )
{
    sf::Vector2f ortho = iVector;
    ortho.x = -iVector.y;
    ortho.y = iVector.x;

    return  ortho;
}


// ===================================================
// ===================================================


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
Sign( const sf::Vector2f& p1, const sf::Vector2f& p2, const sf::Vector2f& p3 )
{
    return ( p1.x - p3.x ) * ( p2.y - p3.y ) - ( p2.x - p3.x ) * ( p1.y - p3.y );
}


inline
double
DegToRad( double iAngle )
{
    return  iAngle * kPIF / 180.0;
}


inline
double
RadToDeg( double iAngle )
{
    return  iAngle * 180.0/kPIF;
}

//...