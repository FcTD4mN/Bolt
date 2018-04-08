#pragma once


#include "Core.ECS.Core.Component.h"


#include <SFML/Graphics.hpp>


namespace nECS {


class cSimplePhysic :
    public cComponent
{
public:
    typedef  cComponent  tSuperClass;

public:
    enum eType
    {
        kStatic = 0,
        kDynamic
    };

public:
    virtual  ~cSimplePhysic();
    cSimplePhysic();
    cSimplePhysic( float iX, float iY, float iW, float iH, eType iType );
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
    eType               mType;
};


} // namespace nECS

