#include "Core.ECS.Core.Component.h"



namespace nCore {
namespace nECS {
namespace nCore {


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


void
cComponent::Name( const std::string & iNewName )
{
    mName = iNewName;
}


// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------- Access/Get
// -------------------------------------------------------------------------------------


void
cComponent::SaveXML( tinyxml2::XMLElement * iNode, tinyxml2::XMLDocument* iDocument ) const
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


cComponent*
cComponentGeneric::Clone() const
{
    return  new cComponentGeneric( *this );
}


// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------- Access/Get
// -------------------------------------------------------------------------------------


::nCore::nBase::cVariant*
cComponentGeneric::GetVar( const std::string& iVarName )
{
    return  mVars[ iVarName ];
}


void
cComponentGeneric::AddNewVariable( const std::string& iVarName, ::nCore::nBase::cVariant* iValue )
{
    delete  mVars[ iVarName ];
    mVars[ iVarName ] = iValue;
}


void
cComponentGeneric::SetVarValueChangeCallback( const std::string & iVarName, std::function< void( ::nCore::nBase::eVariableState ) > iFunction )
{
    mVars[ iVarName ]->SetValueChangeCallback( iFunction );
}


void
cComponentGeneric::VariableEnumerator( std::function<void( const std::string&, ::nCore::nBase::cVariant* )> iMethod )
{
    for( auto variable : mVars )
        iMethod( variable.first, variable.second );
}


int
cComponentGeneric::VarCount() const
{
    return  int( mVars.size() );
}


::nCore::nBase::cVariant*
cComponentGeneric::GetVarAtIndex( int iIndex )
{
    auto it = mVars.cbegin();
    for( int i = 0; i < iIndex; ++i )
        ++it;

    return  it->second;
}


const std::string&
cComponentGeneric::GetVarNameAtIndex( int iIndex ) const
{
    auto it = mVars.cbegin();
    for( int i = 0; i < iIndex; ++i )
        ++it;

    return  it->first;
}

void
cComponentGeneric::RenameVar( const std::string& iCurrentName, const std::string& iNewName )
{
    mVars[ iNewName ] = mVars[ iCurrentName ];
    mVars.erase( iCurrentName );
}


void
cComponentGeneric::RemoveVar( const std::string & iVarName )
{
    mVars.erase( iVarName );
}


// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------- Access/Get
// -------------------------------------------------------------------------------------


void
cComponentGeneric::SaveXML( tinyxml2::XMLElement * iNode, tinyxml2::XMLDocument* iDocument ) const
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
        ::nCore::nBase::cVariant* var = ::nCore::nBase::cVariant::MakeFromXML( variable );
        std::string varName = variable->Attribute( "name" );
        delete  mVars[ varName ];
        mVars[ varName ] = var;
    }
}


} // namespace nCore
} // namespace nECS
} // namespace nCore

