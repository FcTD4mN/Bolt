#pragma once


#include "Core.ECS.Core.Component.h"


#include <tinyxml2.h>


namespace nCore {
namespace nECS {
namespace nComponent {


class cOcclusionFactor :
    public ::nCore::nECS::nCore::cComponentGeneric
{
public:
    typedef  ::nCore::nECS::nCore::cComponentGeneric  tSuperClass;

public:
    virtual  ~cOcclusionFactor();
    cOcclusionFactor();
    cOcclusionFactor( double iValue );
    cOcclusionFactor( const cOcclusionFactor& iRHS );

private:
    void Build( double iValue );

public:
    // Copy
    virtual  ::nCore::nECS::nCore::cComponent* Clone() const override;

public:
    // Access / Set
    double  OcclusionFactor();
    void   OcclusionFactor( double iValue );
};


} // namespace nComponent
} // namespace nECS
} // namespace nCore

