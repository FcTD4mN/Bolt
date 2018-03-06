#pragma once

#include "ECS/Core/Component.h"

#include <SFML/Graphics.hpp>

#include "tinyxml2.h"

class cDirection :
    public cComponent
{
public:
    typedef  cComponent  tSuperClass;

public:
    virtual  ~cDirection();
    cDirection();
    cDirection( const sf::Vector2f& iDirection );
    cDirection( const cDirection& iColor );

public:
    // Copy
    virtual  cComponent* Clone();

public:
    // Input/Output
    virtual  void SaveXML( tinyxml2::XMLElement* iNode, tinyxml2::XMLDocument* iDocument );
    virtual  void LoadXML( tinyxml2::XMLElement* iNode );

public:
    sf::Vector2f mDirection;
};

