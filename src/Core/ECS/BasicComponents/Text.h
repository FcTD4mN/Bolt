#pragma once

#include "ECS/Core/Component.h"

#include <SFML/Graphics.hpp>

#include "tinyxml2.h"

class cText :
    public cComponent
{
public:
    typedef  cComponent  tSuperClass;

public:
    virtual  ~cText();
    cText();
    cText( const std::string& iText );
    cText( const cText& iColor );

public:
    // Copy
    virtual  cComponent* Clone();

public:
    // Input/Output
    virtual  void SaveXML( tinyxml2::XMLElement* iNode, tinyxml2::XMLDocument* iDocument );
    virtual  void LoadXML( tinyxml2::XMLElement* iNode );

public:
    std::string mText;
};

