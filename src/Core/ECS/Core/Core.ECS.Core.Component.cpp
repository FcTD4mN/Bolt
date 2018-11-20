#include "Core.ECS.Core.Component.h"


#include "Core.Base.CommonIncludes.h"
#include "Core.ECS.Core.Entity.h"


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
    mID( iName )
{
}


cComponent::cComponent( const cComponent & iComponent ) :
    mID( iComponent.mID )
{
}


// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------- Access/Get
// -------------------------------------------------------------------------------------


const std::string&
cComponent::ID() const
{
    return  mID;
}


void
cComponent::ID( const std::string & iNewID )
{
    mID = iNewID;
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------ Input/Output
// -------------------------------------------------------------------------------------


void
cComponent::SaveXML( tinyxml2::XMLElement * iNode, tinyxml2::XMLDocument* iDocument ) const
{
    iNode->SetAttribute( "id", mID.c_str() );
}


void
cComponent::LoadXML( tinyxml2::XMLElement * iNode )
{
    mID = iNode->Attribute( "id" );
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
    tSuperClass( iComponent.mID )
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
cComponentGeneric::SetNewVariable( const std::string& iVarName, ::nCore::nBase::cVariant* iValue )
{
    delete  mVars[ iVarName ];
    mVars[ iVarName ] = iValue;
}


void
cComponentGeneric::SetVarValueChangeCallback( const std::string & iVarName, std::function< void( ::nCore::nBase::eVariableState ) > iFunction )
{
    mVars[ iVarName ]->AddValueChangeCallback( iFunction );
}


void
cComponentGeneric::VariableEnumerator( std::function<void( const std::string&, ::nCore::nBase::cVariant* )> iMethod )
{
    for( auto variable : mVars )
        iMethod( variable.first, variable.second );
}


void
cComponentGeneric::ConnectVariable( const std::string & iOwnVariable, cComponentGeneric* iOtherComponent, const std::string & iOtherVariable )
{
    auto myVar = mVars[ iOwnVariable ];
    auto otherVar = iOtherComponent->mVars[ iOtherVariable ];
    assert( myVar && otherVar );

    if( !myVar || !otherVar )
        return;

    // This one is not vital, but makes sense
    assert( myVar->Type() == otherVar->Type() );
    if( myVar->Type() != otherVar->Type() )
        return;

    std::string connectionID = mEntityOwner->ID() + mID + iOwnVariable + iOtherComponent->mEntityOwner->ID() + iOtherComponent->mID + iOtherVariable;

    // No need to stack the same connection
    if( otherVar->CallbackByIDExist( connectionID ) )
        return;

    *myVar = *otherVar;
    otherVar->AddValueChangeCallbackAndAssociateID( [ this, iOwnVariable, iOtherVariable, iOtherComponent ]( ::nCore::nBase::eVariableState iState ){

        if( iState == ::nCore::nBase::kAfterChange )
        {
            *mVars[ iOwnVariable ] = *iOtherComponent->mVars[ iOtherVariable ];
        }
    }, connectionID );
}


void
cComponentGeneric::DisconnectVariable( const std::string & iOwnVariable, cComponentGeneric * iOtherComponent, const std::string & iOtherVariable )
{
    std::string connectionID = mEntityOwner->ID() + mID + iOwnVariable + iOtherComponent->mEntityOwner->ID() + iOtherComponent->mID + iOtherVariable;
    auto otherVar = iOtherComponent->mVars[ iOtherVariable ];
    otherVar->RemoveCallbackByID( connectionID );
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
        std::string varID = variable->Attribute( "name" );
        delete  mVars[ varID ];
        mVars[ varID ] = var;
    }
}


} // namespace nCore
} // namespace nECS
} // namespace nCore

