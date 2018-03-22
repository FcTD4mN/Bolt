#pragma once

#include "SFML/Graphics.hpp"

#include "Math/Edge.h"
#include "Math/Ray.h"

/** Constant : PI in float format. */
#define kPIF (3.1415926535897932384626F)

/** Constant : some small epsilon in float format. */
#define kEpsilonF (1E-5F)

/** Constant : some small epsilon in float format to handle float representing pixels */
#define kEpsilonPixelF 1.0F


static sf::Vector2f gYAxisVector( 0.0F, 1.0F );
static sf::Vector2f gXAxisVector( 1.0F, 0.0F );
static sf::Vector2f gNULLVector( 0.0F, 0.0F );



// Geometry
bool            IsPointInTriangle( sf::Vector2f& pt, sf::Vector2f& v1, sf::Vector2f& v2, sf::Vector2f& v3 );
double          GetAngleBetweenVectors( const sf::Vector2f& p1, const sf::Vector2f& p2 );
double          GetAngleBetweenVectors2( const sf::Vector2f& p1, const sf::Vector2f& p2 );
sf::Vector2f    CenterOfGravity( const  sf::VertexArray& iPolygon );
sf::VertexArray PolygonPolygonInterectionList( const  sf::VertexArray& iPolygonA, const  sf::VertexArray& iPolygonB );
sf::VertexArray ClipPolygonPolygon( const  sf::VertexArray& iPolygonA, const  sf::VertexArray& iPolygonB );
bool            CCWWindedPolygonContainsPoint( const  sf::VertexArray& iPolygon, const sf::Vector2f& iPoint );
void            ExtractEdgesFromPolygon( std::vector< cEdgeF >* oEdges, const  sf::VertexArray& iPolygon );
sf::FloatRect   GetTriangleSetBBox( const std::vector < sf::VertexArray >& iTriangleSet );
void            GetPolygonExtremesByAngle( sf::Vector2f* oMinVertex, sf::Vector2f* oMaxVertex, const sf::VertexArray& iPolygon );
sf::VertexArray GetPointsFromPolygonInBetweenVectorsCCW( const  sf::VertexArray& iPolygon, const sf::Vector2f& iFirstPoint, const sf::Vector2f& iSecondPoint );

// TriangleSubDivisionUsingPolygon
void  TriangleSubDivisionUsingPolygon( std::vector< sf::VertexArray >* oSubTrianglesOutput, const sf::VertexArray& iTriangle, const sf::VertexArray& iPolygon );
void  TriangleSubDivisionUsingPolygonMultiThreadCall( std::vector< sf::VertexArray >* oSubTrianglesOutput, const sf::VertexArray* iTriangle, const sf::VertexArray* iPolygon );

// Sorts
sf::VertexArray CCWWindingSort( const sf::VertexArray& iPolygon );
sf::VertexArray SortVertexesByX( const sf::VertexArray& iPolygon );
sf::VertexArray SortVertexesByY( const sf::VertexArray& iPolygon );
sf::VertexArray SortVertexesByAngle( const sf::VertexArray& iPolygon );

// Contains
bool            VertexArrayContainsVertex( const  sf::VertexArray& iArray, const sf::Vector2f& iVector );
bool            VertexesAreNeighboorInPolygon( const  sf::VertexArray& iPolygon, const sf::Vector2f& iVectorA, const sf::Vector2f& iVectorB );

void            TransformPolygonUsingTransformation( sf::VertexArray* oPolygon, const sf::Transform& iTransformation );
bool            AddElementToVertexArrayUnique( sf::Vector2f& iElement, sf::VertexArray* oVArray, int* oIndexOfExisting );

// ===================================================
// ===================================================


// Adds an element to a vector only if it is not already in
template< typename T >
bool
AddElementToVectorUnique( T& iElement, std::vector< T >* oVector, int* oIndexOfExisting )
{
    *oIndexOfExisting = -1;
    for( auto elm : *oVector )
    {
        *oIndexOfExisting += 1;
        if( elm == iElement )
            return  false;
    }

    (*oVector).push_back( iElement );

    return  true;
}

template<> bool AddElementToVectorUnique( sf::Vector2f& iElement, std::vector< sf::Vector2f >* oVector, int* oIndexOfExisting );
template<> bool AddElementToVectorUnique( cEdgeF& iElement, std::vector< cEdgeF >* oVector, int* oIndexOfExisting );
template<> bool AddElementToVectorUnique( cRay& iElement, std::vector< cRay >* oVector, int* oIndexOfExisting );


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
    float precision = kEpsilonF;
    if( iVector1 == iVector2 )
        return  true;

    bool x10 = abs(iVector1.x) < precision;
    bool y10 = abs(iVector1.y) < precision;
    bool x20 = abs(iVector2.x) < precision;
    bool y20 = abs(iVector2.y) < precision;
    if( x10 && x20 ) return  true;
    if( y10 && y20 ) return  true;

    if( x10 != x20 ) return  false;
    if( y10 != y20 ) return  false;

    return  abs(( iVector1.x / iVector2.x ) - ( iVector1.y / iVector2.y )) < precision;
}

inline
bool
CollinearUsingAngles( const sf::Vector2f& iVector1, const sf::Vector2f& iVector2 )
{
    if( iVector1 == iVector2 )
        return  true;

    double angleA = GetAngleBetweenVectors( iVector1, gXAxisVector );
    double angleB = GetAngleBetweenVectors( iVector2, gXAxisVector );

    return  abs( angleA - angleB ) < kEpsilonF;
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


// FloatCOmparison utilities
inline
bool
IsVectorEqualToVector( const sf::Vector2f& iVectorA, const sf::Vector2f& iVectorB )
{
    sf::Vector2f sub = iVectorA - iVectorB;
    if( abs( sub.x ) < kEpsilonF && abs( sub.y ) < kEpsilonF )
        return  true;

    return  false;
}

inline
sf::Vector2f
RoundVector( const sf::Vector2f& iVector )
{
    return  sf::Vector2f( round( iVector.x ), round( iVector.y ) );
}

//...