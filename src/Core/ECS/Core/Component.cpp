#include "Component.h"

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
