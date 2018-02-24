#pragma once

#include "ECS/Component.h"

#include <SFML/Graphics.hpp>

class cUserInput :
    public cComponent
{
public:
    typedef  cComponent  tSuperClass;

public:
    virtual  ~cUserInput();
    cUserInput();

public:
    // Input/Output
    virtual  void SaveXML( tinyxml2::XMLElement* iNode, tinyxml2::XMLDocument* iDocument );
    virtual  void LoadXML( const tinyxml2::XMLElement* iNode );

public:
    std::vector< std::string > mActions;
};

