#pragma once

#include "Core.ECS.Core.Component.h"

#include <SFML/Graphics.hpp>
#include <tinyxml2.h>


namespace nCore {
namespace nECS {
namespace nComponent {


class cTransformation :
    public ::nCore::nECS::nCore::cComponentGeneric
{
public:
    typedef  ::nCore::nECS::nCore::cComponentGeneric  tSuperClass;

public:
    virtual  ~cTransformation();
    cTransformation();
    cTransformation( const sf::FloatRect& iRect, float iRotation );
    cTransformation( const sf::Vector2f& iPosition, const sf::Vector2f& iSize, float iRotation );
    cTransformation( const cTransformation& iRHS );

private:
    void BuildVariables( const sf::FloatRect& iRect, float iRotation );
    void BuildCallbacks();

public:
    // Copy
    virtual  ::nCore::nECS::nCore::cComponent* Clone() const override;

public:
    // Access / Set
    double X();
    double Y();

    void X( double iX );
    void Y( double iY );

    double W();
    double H();

    void W( double iW );
    void H( double iH );

    double Rotation();
    void   Rotation( double iRotation );

    sf::Vector2f PositionAsVector2F();
    sf::Vector2f SizeAsVector2F();

    sf::Vector2f    PreviousPosition() const;
    sf::Vector2f    PreviousSize() const;
    double          PreviousRotation() const;

public:
    // Input/Output
    virtual  void LoadXML( tinyxml2::XMLElement* iNode ) override;

private:
    sf::FloatRect   mPreviousRect;
    double          mPreviousRotation;
};


} // namespace nComponent
} // namespace nECS
} // namespace nCore

