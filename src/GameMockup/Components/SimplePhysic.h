#pragma once

#include "ECS/Component.h"

#include <SFML/Graphics.hpp>

class cSimplePhysic :
    public cComponent
{
public:
    typedef  cComponent  tSuperClass;

public:
    virtual  ~cSimplePhysic();
    cSimplePhysic();
    cSimplePhysic( float iX, float iY, float iW, float iH );
    cSimplePhysic( const cSimplePhysic& iSimplePhysic );

public:
    // Copy
    virtual  cComponent* Clone();

public:
    // Input/Output
    virtual  void SaveXML( tinyxml2::XMLElement* iNode, tinyxml2::XMLDocument* iDocument );
    virtual  void LoadXML( tinyxml2::XMLElement* iNode );

public:
    sf::Vector2f        mVelocity;
    sf::Rect< float >   mHitBox;
};

