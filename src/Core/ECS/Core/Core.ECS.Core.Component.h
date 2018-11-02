#pragma once


#include "Core.Base.Variant.h"


#include <tinyxml2.h>


#include <functional>
#include <string>
#include <map>


namespace nCore {
namespace nECS {
namespace nCore {


class cEntity;


class cComponent
{

    friend  cEntity; // So it can access the mEntityOwner var, and is the only class able to modify it


public:
    // Contruction/Destruction
    virtual  ~cComponent() = 0;
    cComponent( const std::string& iName );
    cComponent( const cComponent& iComponent );

public:
    // Copy
    virtual  cComponent* Clone() const = 0;

public:
    // Access/Get
    const  std::string&  Name() const;

    //EDITOR
    void  Name( const std::string& iNewName );

public:
    // Input/Output
    virtual  void SaveXML( tinyxml2::XMLElement* iNode, tinyxml2::XMLDocument* iDocument ) const;
    virtual  void LoadXML( tinyxml2::XMLElement* iNode );

protected:
    std::string  mName;
    cEntity*     mEntityOwner;
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
    // Copy
    virtual  cComponent* Clone() const override;

public:
    // Access/Get
        // Yes we can get the variant, and modify it on the stop, so it's faster
    ::nCore::nBase::cVariant*          GetVar( const std::string& iVarName );
        // Simple setter
    void                AddNewVariable( const std::string& iVarName, ::nCore::nBase::cVariant* iValue );
    void                SetVarValueChangeCallback( const std::string& iVarName, std::function< void( ::nCore::nBase::eVariableState ) > iFunction );

    void                VariableEnumerator( std::function< void( const std::string&, ::nCore::nBase::cVariant* )> iMethod );

    // EDITOR USED methods
    int                 VarCount() const;
    ::nCore::nBase::cVariant*  GetVarAtIndex( int iIndex );
    const std::string&  GetVarNameAtIndex( int iIndex ) const;
    void                RenameVar( const std::string& iCurrentName, const std::string& iNewName );
    void                RemoveVar( const std::string& iVarName );

public:
    // Input/Output
    virtual  void SaveXML( tinyxml2::XMLElement* iNode, tinyxml2::XMLDocument* iDocument ) const override;
    virtual  void LoadXML( tinyxml2::XMLElement* iNode ) override;

protected:
    std::map< std::string, ::nCore::nBase::cVariant* >  mVars;
    std::map< std::string, std::function< void() > >    mValueChangeCallbacks; // Callbacks to call when value changed
};


} // namespace nCore
} // namespace nECS
} // namespace nCore

