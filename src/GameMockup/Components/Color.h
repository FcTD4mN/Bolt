#pragma once

#include "ECS/Component.h"

#include <SFML/Graphics.hpp>

#include "tinyxml2.h"

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
    // Input/Output
    virtual  void SaveXML( tinyxml2::XMLElement* iNode, tinyxml2::XMLDocument* iDocument );
    virtual  void LoadXML( tinyxml2::XMLElement* iNode );

public:
    sf::Color mColor;
};

