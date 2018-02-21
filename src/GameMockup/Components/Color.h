#pragma once

#include "ECS/Component.h"

#include <SFML/Graphics.hpp>

class cColor :
    public cComponent
{
public:
    typedef  cComponent  tSuperClass;

public:
    virtual  ~cColor();
    cColor();
    cColor( int iR, int iG, int iB, int iA = 255 );
    cColor( sf::Color );

public:
    sf::Color mColor;
};

