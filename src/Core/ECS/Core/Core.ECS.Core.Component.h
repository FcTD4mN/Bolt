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

    friend  cEntity; // So entity can access the mEntityOwner var, and is the only class able to modify it


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
    const  std::string&  ID() const;

    //EDITOR
    void  ID( const std::string& iNewID );

public:
    // Input/Output
    virtual  void SaveXML( tinyxml2::XMLElement* iNode, tinyxml2::XMLDocument* iDocument ) const;
    virtual  void LoadXML( tinyxml2::XMLElement* iNode );

protected:
    std::string  mID;
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
        // Yes we can get the variant, and modify it on the spot, so it's faster
    ::nCore::nBase::cVariant*       GetVar( const std::string& iVarName );

    // Sets given var name to a new variable. The new variable won't have callbacks ported from the old one if setting an already existing var
    void                            SetNewVariable( const std::string& iVarName, ::nCore::nBase::cVariant* iValue );
    void                            SetVarValueChangeCallback( const std::string& iVarName, std::function< void( ::nCore::nBase::eVariableState ) > iFunction );
    void                            VariableEnumerator( std::function< void( const std::string&, ::nCore::nBase::cVariant* )> iMethod );

    /*
        This connection isn't persistent, as we can't save pointer here.
        This is a low level connection feature, that allows any form of connections between any components from any entities.
        For persistent connections, use the Connect methods in entity
     */
    void                            ConnectVariable( const std::string& iOwnVariable, cComponentGeneric* iOtherComponent, const std::string& iOtherVariable );


    // EDITOR USED methods
    int                         VarCount() const;
    ::nCore::nBase::cVariant*   GetVarAtIndex( int iIndex );
    const std::string&          GetVarNameAtIndex( int iIndex ) const;
    void                        RenameVar( const std::string& iCurrentName, const std::string& iNewName );
    void                        RemoveVar( const std::string& iVarName );

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

