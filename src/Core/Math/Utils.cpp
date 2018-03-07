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

//...