#include "Core.ECS.Core.Component.h"

namespace nECS {


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------ Construction
// -------------------------------------------------------------------------------------


cComponent::~cComponent()
{
}


cComponent::cComponent( const std::string& iName ) :
    mName( iName )
{
}


cComponent::cComponent( const cComponent & iComponent ) :
    mName( iComponent.mName )
{
}


// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------- Access/Get
// -------------------------------------------------------------------------------------


const std::string&
cComponent::Name() const
{
    return  mName;
}


// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------- Access/Get
// -------------------------------------------------------------------------------------


void
cComponent::SaveXML( tinyxml2::XMLElement * iNode, tinyxml2::XMLDocument* iDocument )
{
    iNode->SetAttribute( "name", mName.c_str() );
}


void
cComponent::LoadXML( tinyxml2::XMLElement * iNode )
{
    mName = iNode->Attribute( "name" );
}

// ------------------------------------------------------------------------------------ -
// ------------------------------------------------------------------------------------ -
// ------------------------------------------------------------------------------------ -
// ------------------------------------------------------------------------------------ -
// ------------------------------------------------------------------------------------ -
// ------------------------------------------------------------------------------------ -
// ------------------------------------------------------------------------------------ -
// ------------------------------------------------------------------------------------ -
// ------------------------------------------------------------------------------------ -
// ------------------------------------------------------------------------------------ -


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------ Construction
// -------------------------------------------------------------------------------------


cComponentGeneric::~cComponentGeneric()
{
    for( auto var : mVars )
        delete  var.second;
}


cComponentGeneric::cComponentGeneric( const std::string& iName ) :
    tSuperClass( iName )
{
}


cComponentGeneric::cComponentGeneric( const cComponentGeneric & iComponent ) :
    tSuperClass( iComponent.mName )
{
    for( auto& var : iComponent.mVars )
        mVars[ var.first ] = var.second->Clone();
}


// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------- Access/Get
// -------------------------------------------------------------------------------------


::nBase::cVariant*
cComponentGeneric::GetVar( const std::string& iVarName )
{
    return  mVars[ iVarName ];
}


void
cComponentGeneric::SetVar( const std::string& iVarName, ::nBase::cVariant* iValue )
{
    delete  mVars[ iVarName ];
    mVars[ iVarName ] = iValue;
}


int
cComponentGeneric::VarCount() const
{
    return  int( mVars.size() );
}


const ::nBase::cVariant*
cComponentGeneric::GetVarValueAtIndex( int iIndex ) const
{
    auto it = mVars.cbegin();
    for( int i = 0; i < mVars.size(); ++i )
        ++it;

    return  it->second;
}


const std::string&
cComponentGeneric::GetVarNameAtIndex( int iIndex ) const
{
    auto it = mVars.cbegin();
    for( int i = 0; i < mVars.size(); ++i )
        ++it;

    return  it->first;
}


// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------- Access/Get
// -------------------------------------------------------------------------------------


void
cComponentGeneric::SaveXML( tinyxml2::XMLElement * iNode, tinyxml2::XMLDocument* iDocument )
{
    tSuperClass::SaveXML( iNode, iDocument );

    tinyxml2::XMLElement* vars = iDocument->NewElement( "variables" );
    for( auto& var : mVars )
    {
        tinyxml2::XMLElement* variable = iDocument->NewElement( "variable" );
        variable->SetAttribute( "name", var.first.c_str() );

            var.second->SaveXML( variable, iDocument );

        vars->LinkEndChild( variable );
    }

    iNode->LinkEndChild( vars );
}


void
cComponentGeneric::LoadXML( tinyxml2::XMLElement * iNode )
{
    tSuperClass::LoadXML( iNode );

    tinyxml2::XMLElement* variables = iNode->FirstChildElement( "variables" );
    for( tinyxml2::XMLElement* variable = variables->FirstChildElement( "variable" ); variable; variable = variable->NextSiblingElement() )
    {
        ::nBase::cVariant* var = ::nBase::cVariant::MakeFromXML( variable );
        std::string varName = variable->Attribute( "name" );
        mVars[ varName ] = var;
    }
}


} // namespace nECS

