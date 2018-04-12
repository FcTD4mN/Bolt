#pragma once


#include "Core.Base.Variant.h"


#include <tinyxml2.h>


#include <functional>
#include <string>
#include <unordered_map>


namespace nECS {


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
    std::string  mName;

};


class cComponentGeneric :
    public cComponent
{
public:
    typedef cComponent tSuperClass;

public:
    // Contruction/Destruction
    virtual  ~cComponentGeneric();
    cComponentGeneric( const std::string& iName );
    cComponentGeneric( const cComponentGeneric& iComponent );

public:
    // Access/Get
        // Yes we can get the variant, and modify it on the stop, so it's faster
    ::nBase::cVariant*    GetVar( const std::string& iVarName );
        // Simple setter
    void                  SetVar( const std::string& iVarName, ::nBase::cVariant* iValue );

    // EDITOR USED methods
    int     VarCount() const;
    const ::nBase::cVariant*    GetVarValueAtIndex( int iIndex ) const;
    const std::string&    GetVarNameAtIndex( int iIndex ) const;

public:
    // Input/Output
    virtual  void SaveXML( tinyxml2::XMLElement* iNode, tinyxml2::XMLDocument* iDocument );
    virtual  void LoadXML( tinyxml2::XMLElement* iNode );

protected:
    std::unordered_map< std::string, ::nBase::cVariant* > mVars;

};


} // namespace nECS

