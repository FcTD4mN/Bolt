#pragma once

#include "ECS/Component.h"

#include <SFML/Graphics.hpp>

class cPosition :
    public cComponent
{
public:
    typedef  cComponent  tSuperClass;

public:
    virtual  ~cPosition();
    cPosition();
    cPosition( float iX, float iY );
    cPosition( const sf::Vector2f& iVector );

public:
    sf::Vector2f  mPosition;
};
