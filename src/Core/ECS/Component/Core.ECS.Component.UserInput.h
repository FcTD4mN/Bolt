#pragma once


#include "Core.ECS.Core.Component.h"


#include <SFML/Graphics.hpp>


namespace nECS {


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


} // namespace nECS

