#pragma once

#include "Core.ECS.Core.Component.h"

#include <SFML/Graphics.hpp>
#include <tinyxml2.h>


namespace nECS {


class cZDepth :
    public cComponentGeneric
{
public:
    typedef  cComponentGeneric  tSuperClass;

public:
    virtual  ~cZDepth();
    cZDepth();
    cZDepth( float iZDepth );
    cZDepth( const cZDepth& iRHS );

    void Build( float iZDepth );

public:
    // Copy
    virtual  cComponent* Clone() override;

public:
    // Access / Set
    double ZDepth();
    void ZDepth( double iZDepth );
};


} // namespace nECS

