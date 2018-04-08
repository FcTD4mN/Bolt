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


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------ Construction
// -------------------------------------------------------------------------------------


cComponentGeneric::~cComponentGeneric()
{
}


cComponentGeneric::cComponentGeneric( const std::string& iName ) :
    mName( iName )
{
}


cComponentGeneric::cComponentGeneric( const cComponentGeneric & iComponent ) :
    mName( iComponent.mName )
{
}


// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------- Access/Get
// -------------------------------------------------------------------------------------


const std::string&
cComponentGeneric::Name() const
{
    return  mName;
}


const ::nBase::cVariant&
cComponentGeneric::GetVar( const std::string& iVarName )
{
    return  mVars[ iVarName ];
}


void
cComponentGeneric::SetVar( const std::string& iVarName, ::nBase::cVariant& iValue )
{
    mVars[ iVarName ] = iValue;
}


// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------- Access/Get
// -------------------------------------------------------------------------------------


void
cComponentGeneric::SaveXML( tinyxml2::XMLElement * iNode, tinyxml2::XMLDocument* iDocument )
{
    iNode->SetAttribute( "name", mName.c_str() );

    tinyxml2::XMLElement* vars = iDocument->NewElement( "variables" );
    for( auto& var : mVars )
    {
        tinyxml2::XMLElement* variable = iDocument->NewElement( "variable" );

            var.second.SaveXML( variable, iDocument );

        vars->LinkEndChild( variable );
    }

    iNode->LinkEndChild( vars );
}


void
cComponentGeneric::LoadXML( tinyxml2::XMLElement * iNode )
{
    mName = iNode->Attribute( "name" );

    tinyxml2::XMLElement* variables = iNode->FirstChildElement( "variables" );
    for( tinyxml2::XMLElement* variable = variables->FirstChildElement( "variable" ); variable; variable = variable->NextSiblingElement() )
    {
        ::nBase::cVariant var;
        var.LoadXML( variable );
    }
}


} // namespace nECS

