#pragma once


#include "Core.ECS.Core.Component.h"


#include <SFML/Graphics.hpp>
#include <tinyxml2.h>


namespace nECS {


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
    cPosition( const cPosition& iPosition );

public:
    // Copy
    virtual  cComponent* Clone();

public:
    // Input/Output
    virtual  void SaveXML( tinyxml2::XMLElement* iNode, tinyxml2::XMLDocument* iDocument );
    virtual  void LoadXML( tinyxml2::XMLElement* iNode );

public:
    sf::Vector2f  mPosition;

};


class cGPosition :
    public cComponentGeneric
{
public:
    typedef  cComponentGeneric  tSuperClass;

public:
    virtual  ~cGPosition();
    cGPosition();
    cGPosition( float iX, float iY );
    cGPosition( const sf::Vector2f& iVector );
    cGPosition( const cGPosition& iPosition );

public:
    // Copy
    virtual  cComponentGeneric* Clone();

};


} // namespace nECS

