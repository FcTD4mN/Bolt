#pragma once

#include "Core.ECS.Core.Component.h"

#include <SFML/Graphics.hpp>
#include <tinyxml2.h>


namespace nCore {
namespace nECS {
namespace nComponent {


class cZDepth :
    public ::nCore::nECS::nCore::cComponentGeneric
{
public:
    typedef  ::nCore::nECS::nCore::cComponentGeneric  tSuperClass;

public:
    virtual  ~cZDepth();
    cZDepth();
    cZDepth( float iZDepth );
    cZDepth( const cZDepth& iRHS );

    void Build( float iZDepth );

public:
    // Copy
    virtual  ::nCore::nECS::nCore::cComponent* Clone() const override;

public:
    // Access / Set
    double ZDepth();
    void ZDepth( double iZDepth );
};


} // namespace nComponent
} // namespace nECS
} // namespace nCore

