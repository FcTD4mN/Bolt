#pragma once

#include "Base/Variant.h"

#include "tinyxml2.h"

#include <string>
#include <unordered_map>

class cComponent
{

public:
    // Contruction/Destruction
    virtual  ~cComponent() = 0;
    cComponent( const std::string& iName );
    cComponent( const cComponent& iComponent );

public:
    // Copy
    virtual  cComponent* Clone() = 0;

public:
    // Access/Get
    const  std::string&  Name() const;

public:
    // Input/Output
    virtual  void SaveXML( tinyxml2::XMLElement* iNode, tinyxml2::XMLDocument* iDocument );
    virtual  void LoadXML( tinyxml2::XMLElement* iNode );

protected:
    std::string mName;
};


class cComponentGeneric
{
public:
    // Contruction/Destruction
    virtual  ~cComponentGeneric() = 0;
    cComponentGeneric( const std::string& iName );
    cComponentGeneric( const cComponentGeneric& iComponent );

public:
    // Copy
    virtual  cComponentGeneric* Clone() = 0;

public:
    // Access/Get
    const  std::string&  Name() const;
    const cVariant&     GetVar( const std::string& iVarName );
    void                SetVar( const std::string& iVarName, cVariant& iValue );

public:
    // Input/Output
    virtual  void SaveXML( tinyxml2::XMLElement* iNode, tinyxml2::XMLDocument* iDocument );
    virtual  void LoadXML( tinyxml2::XMLElement* iNode );

protected:
    std::string mName;
    std::unordered_map< std::string, cVariant > mVars;
};
