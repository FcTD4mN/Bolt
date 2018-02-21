#pragma once

#include "ECS/Component.h"

#include <SFML/Graphics.hpp>

class cSize :
    public cComponent
{
public:
    typedef  cComponent  tSuperClass;

public:
    virtual  ~cSize();
    cSize();
    cSize( float iW, float iH );
    cSize( const sf::Vector2f& iVector );

public:
    sf::Vector2f  mSize;
};
