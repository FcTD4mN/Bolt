#pragma once

#include "Base/PrimitiveType.h"

#include <string>
#include "tinyxml2.h"

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
    virtual  ~cComponent() = 0;
    cComponent( const std::string& iName );
    cComponent( const cComponent& iComponent );

public:
    // Copy
    virtual  cComponent* Clone() = 0;

public:
    // Access/Get
    const  std::string&  Name() const;
    const cVariant&     GetVar( const std::string& iVarName ) const;
    void                SetVar( const std::string& iVarName, const cVariant& iValue );

public:
    // Input/Output
    virtual  void SaveXML( tinyxml2::XMLElement* iNode, tinyxml2::XMLDocument* iDocument );
    virtual  void LoadXML( tinyxml2::XMLElement* iNode );

protected:
    std::string mName;
    std::unordered_map< std::string, cVariant > mVars;
};
