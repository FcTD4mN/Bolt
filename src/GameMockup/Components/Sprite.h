#pragma once

#include "ECS/Component.h"

#include <SFML/Graphics.hpp>

class cSprite :
    public cComponent
{
public:
    typedef  cComponent  tSuperClass;

public:
    virtual  ~cSprite();
    cSprite(); 

public:
    sf::Vector2f  mSprite;
};
