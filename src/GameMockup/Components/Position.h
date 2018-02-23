#pragma once

#include "ECS/Component.h"

#include <SFML/Graphics.hpp>

#include "tinyxml2.h"

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
    // Input/Output
    virtual  void SaveXML( tinyxml2::XMLElement* iNode, tinyxml2::XMLDocument* iDocument );
    virtual  void LoadXML( const tinyxml2::XMLElement* iNode );

public:
    sf::Vector2f  mPosition;
};
