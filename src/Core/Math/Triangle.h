#pragma once

#include "SFML/Graphics.hpp"

class cTriangleF
{

public:
    // Contruction/Destruction
    ~cTriangleF();
    cTriangleF();
    cTriangleF( const sf::Vector2f& iA, const sf::Vector2f& iB, const sf::Vector2f& iC );

public:
    bool Contains( const sf::Vector2f& iPoint );

public:
    sf::Vector2f mA;
    sf::Vector2f mB;
    sf::Vector2f mC;
};

