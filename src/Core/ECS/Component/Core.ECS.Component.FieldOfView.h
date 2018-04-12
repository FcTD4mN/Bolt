#pragma once

#include "Core.ECS.Core.Component.h"

#include <tinyxml2.h>


namespace nECS {


class cFieldOfView :
    public cComponentGeneric
{
public:
    typedef  cComponentGeneric  tSuperClass;

public:
    virtual  ~cFieldOfView();
    cFieldOfView();
    cFieldOfView( double iAngle, double iDistance );
    cFieldOfView( const cFieldOfView& iRHS );

public:
    // Copy
    virtual  cFieldOfView* Clone() override;

public:
    // Access / Set
    double Angle();
    double Distance();

    void Angle( double iAngle );
    void Distance( double iDistance );
};


} // namespace nECS

