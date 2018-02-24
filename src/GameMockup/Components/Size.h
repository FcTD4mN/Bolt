#pragma once

#include "ECS/Component.h"

#include <SFML/Graphics.hpp>

#include "tinyxml2.h"

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
    // Input/Output
    virtual  void SaveXML( tinyxml2::XMLElement* iNode, tinyxml2::XMLDocument* iDocument );
    virtual  void LoadXML( tinyxml2::XMLElement* iNode );

public:
    sf::Vector2f  mSize;
};
