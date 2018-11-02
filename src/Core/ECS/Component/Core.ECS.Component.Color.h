#pragma once


#include "Core.ECS.Core.Component.h"


#include <SFML/Graphics.hpp>
#include <tinyxml2.h>


namespace nCore {
namespace nECS {
namespace nComponent {


class cColor :
    public ::nCore::nECS::nCore::cComponentGeneric
{
public:
    typedef  cComponentGeneric  tSuperClass;

public:
    virtual  ~cColor();
    cColor();
    cColor( int iR, int iG, int iB, int iA = 255 );
    cColor( const sf::Color& iColor);
    cColor( const cColor& iRHS );

    void Build( int iR, int iG, int iB, int iA = 255 );

public:
    // Copy
    virtual  cComponent* Clone() const override;

public:
    // Access / Set
    int R();
    int G();
    int B();
    int A();

    void R( int iR );
    void G( int iG );
    void B( int iB );
    void A( int iA );

    sf::Color AsSFCOlor();
};


} // namespace nComponent
} // namespace nECS
} // namespace nCore

