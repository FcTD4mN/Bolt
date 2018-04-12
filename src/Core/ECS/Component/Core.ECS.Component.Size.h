#pragma once

#include "Core.ECS.Core.Component.h"

#include <SFML/Graphics.hpp>
#include <tinyxml2.h>


namespace nECS {


class cSize :
    public cComponentGeneric
{
public:
    typedef  cComponentGeneric  tSuperClass;

public:
    virtual  ~cSize();
    cSize();
    cSize( float iW, float iH );
    cSize( const sf::Vector2f& iVector );
    cSize( const cSize& iRHS );

    void Build( float iW, float iH );

public:
    // Copy
    virtual  cSize* Clone() override;

public:
    // Access / Set
    double W();
    double H();

    void W( double iW );
    void H( double iH );

    sf::Vector2f AsVector2F();
    void SetUsingVector( const sf::Vector2f& iVector );
};


} // namespace nECS

