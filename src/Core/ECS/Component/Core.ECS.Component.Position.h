#pragma once

#include "Core.ECS.Core.Component.h"

#include <SFML/Graphics.hpp>
#include <tinyxml2.h>


namespace nECS {


class cPosition :
    public cComponentGeneric
{
public:
    typedef  cComponentGeneric  tSuperClass;

public:
    virtual  ~cPosition();
    cPosition();
    cPosition( float iX, float iY );
    cPosition( const sf::Vector2f& iVector );
    cPosition( const cPosition& iRHS );

public:
    // Copy
    virtual  cPosition* Clone() override;

public:
    // Access / Set
    double X();
    double Y();

    void X( double iX );
    void Y( double iY );

    sf::Vector2f AsVector2F();
};


} // namespace nECS

