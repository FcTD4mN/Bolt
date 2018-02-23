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
    tinyxml2::XMLElement* component = iDocument->NewElement( "component" );

    iNode->SetAttribute( "name", mName.c_str() );

    iNode->LinkEndChild( component );
}


void
cComponent::LoadXML( const tinyxml2::XMLElement * iNode )
{
    const tinyxml2::XMLElement* component = iNode->FirstChildElement( "component" );
    mName = component->Attribute( "name" );
}
