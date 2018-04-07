#pragma once

#include "ECS/Core/Component.h"

#include <SFML/Graphics.hpp>

#include "tinyxml2.h"

namespace nECS {

class cSize :
    public ::nECS::cComponent
{
public:
    typedef  ::nECS::cComponent  tSuperClass;

public:
    virtual  ~cSize();
    cSize();
    cSize( float iW, float iH );
    cSize( const sf::Vector2f& iVector );
    cSize( const cSize& iSize );

public:
    // Copy
    virtual  ::nECS::cComponent* Clone();

public:
    // Input/Output
    virtual  void SaveXML( tinyxml2::XMLElement* iNode, tinyxml2::XMLDocument* iDocument );
    virtual  void LoadXML( tinyxml2::XMLElement* iNode );

public:
    sf::Vector2f  mSize;
};

} //nECS
