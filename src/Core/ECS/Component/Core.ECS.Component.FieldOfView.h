#pragma once


#include "Core.ECS.Core.Component.h"


#include <tinyxml2.h>


namespace nECS {


class cFieldOfView :
    public cComponent
{
public:
    typedef  cComponent  tSuperClass;

public:
    virtual  ~cFieldOfView();
    cFieldOfView();
    cFieldOfView( double iAngle, double iDistance );
    cFieldOfView( const cFieldOfView& iColor );

public:
    // Copy
    virtual  cComponent* Clone();

public:
    // Input/Output
    virtual  void SaveXML( tinyxml2::XMLElement* iNode, tinyxml2::XMLDocument* iDocument );
    virtual  void LoadXML( tinyxml2::XMLElement* iNode );

public:
    double  mAngle;
    double  mDistance;

};


} // namespace nECS

