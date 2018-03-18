#pragma once

#include "SFML/Graphics.hpp"


class cEdgeF
{

public:
    // Contruction/Destruction
    ~cEdgeF();
    cEdgeF();

public:
    static cEdgeF MakePointDirection( const sf::Vector2f& iPoint, const sf::Vector2f& iDirection );
    static cEdgeF MakePointPoint( const sf::Vector2f& iPoint, const sf::Vector2f& iPoint2 );

public:
    bool  Intersect( float* oParameterA, float* oParameterB, const cEdgeF& iEdge ) const;
    static bool  Intersect( float* oParameterA, float* oParameterB, const cEdgeF& iEdgeA, const cEdgeF& iEdgeB );

public:
    sf::Vector2f mPoint;
    sf::Vector2f mDirection;
};

