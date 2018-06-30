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

private:
	void BuildCallbacks();

public:
    // Copy
    virtual  cComponent* Clone() override;

public:
    // Access / Set
    double X();
    double Y();

    void X( double iX );
    void Y( double iY );

    sf::Vector2f AsVector2F();

	const sf::Vector2f& PreviousPosition() const;

private:
	sf::Vector2f mPreviousPosition;
};


} // namespace nECS

