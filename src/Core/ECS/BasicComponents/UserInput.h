#pragma once

#include "ECS/Core/Component.h"

#include <SFML/Graphics.hpp>

class cUserInput :
    public cComponent
{
public:
    typedef  cComponent  tSuperClass;

public:
    virtual  ~cUserInput();
    cUserInput();
    cUserInput( const cUserInput& iUserInput );

public:
    // Copy
    virtual  cComponent* Clone();

public:
    std::vector< std::string > mActions;
};

