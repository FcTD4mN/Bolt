#pragma once

#include "ECS/Component.h"

#include <SFML/Graphics.hpp>

class cUserInput :
    public cComponent
{
public:
    typedef  cComponent  tSuperClass;

public:
    virtual  ~cUserInput();
    cUserInput();

public:
    std::vector< std::string > mActions;
};

