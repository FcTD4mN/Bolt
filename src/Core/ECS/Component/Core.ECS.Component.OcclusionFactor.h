#pragma once

#include "Core.ECS.Core.Component.h"

#include <tinyxml2.h>


namespace nECS {


class cOcclusionFactor :
    public cComponentGeneric
{
public:
    typedef  cComponentGeneric  tSuperClass;

public:
    virtual  ~cOcclusionFactor();
    cOcclusionFactor();
    cOcclusionFactor( double iValue );
    cOcclusionFactor( const cOcclusionFactor& iRHS );

private:
    void Build( double iValue );

public:
    // Copy
    virtual  cComponent* Clone() override;

public:
    // Access / Set
    double  OcclusionFactor();
    void   OcclusionFactor( double iValue );
};


} // namespace nECS

