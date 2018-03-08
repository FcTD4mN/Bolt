#include "Math/Utils.h"

bool IsPointInTriangle( sf::Vector2f& pt, sf::Vector2f& v1, sf::Vector2f& v2, sf::Vector2f& v3 )
{
    bool b1, b2, b3;

    b1 = Sign( pt, v1, v2 ) < 0.0f;
    b2 = Sign( pt, v2, v3 ) < 0.0f;
    b3 = Sign( pt, v3, v1 ) < 0.0f;

    return ( ( b1 == b2 ) && ( b2 == b3 ) );
}


double
GetAngleBetweenVectors( sf::Vector2f& p1, sf::Vector2f& p2 )
{
    float dotProduct = p1.x * p2.x + p1.y * p2.y;
    float magnetudeP1 = sqrt( p1.x * p1.x + p1.y *p1.y );
    float magnetudeP2 = sqrt( p2.x * p2.x + p2.y *p2.y );
    return  acos( dotProduct / ( magnetudeP1 * magnetudeP2 ) ) * 180 / kPI;

}


std::vector< sf::Vector2f >
GetUnionFromTriangles( sf::Vector2f & iT1A, sf::Vector2f & iT1B, sf::Vector2f & iT1C, sf::Vector2f & iT2A, sf::Vector2f & iT2B, sf::Vector2f & iT2C )
{
    std::vector< sf::Vector2f > output;
    output.push_back( iT1A );
    output.push_back( iT1B );
    output.push_back( iT1C );

    //for( Edge clipEdge in clipPolygon ) do
    //    List inputList = outputList;
    //outputList.clear();
    //Point S = inputList.last;
    //for( Point E in inputList ) do
    //    if( E inside clipEdge ) then
    //        if( S not inside clipEdge ) then
    //            outputList.add( ComputeIntersection( S, E, clipEdge ) );
    //end if
    //    outputList.add( E );
    //else if( S inside clipEdge ) then
    //    outputList.add( ComputeIntersection( S, E, clipEdge ) );
    //end if
    //    S = E;
    //done
    //    done

    return  output;
}

//...