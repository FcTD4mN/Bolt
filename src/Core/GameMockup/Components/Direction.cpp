#include "Direction.h"

#include "ECS/Utilities/ComponentRegistry.h"

// -------------------------------------------------------------------------------------
// ------------------------------------------------------------ Construction/Destruction
// -------------------------------------------------------------------------------------


cDirection::~cDirection()
{
}


cDirection::cDirection() :
    tSuperClass( "direction" ),
    mDirection( sf::Vector2f( 0.0F, 0.0F ) )
{
}


cDirection::cDirection( const sf::Vector2f& iDirection ) :
    tSuperClass( "direction" ),
    mDirection( iDirection )
{
}


cDirection::cDirection( const cDirection & iDirection ) :
    tSuperClass( iDirection ),
    mDirection( iDirection.mDirection )
{
}


// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------- Copy
// -------------------------------------------------------------------------------------


cComponent*
cDirection::Clone()
{
    return  new cDirection( *this );
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------ Input/Output
// -------------------------------------------------------------------------------------


void
cDirection::SaveXML( tinyxml2::XMLElement* iNode, tinyxml2::XMLDocument* iDocument )
{
    tSuperClass::SaveXML( iNode, iDocument );
    iNode->SetAttribute( "directionx", mDirection.x );
    iNode->SetAttribute( "directiony", mDirection.y );
}


void
cDirection::LoadXML( tinyxml2::XMLElement* iNode )
{
    tSuperClass::LoadXML( iNode );
    mDirection.x = iNode->FloatAttribute( "directionx", 0.0F );
    mDirection.y = iNode->FloatAttribute( "directiony", 0.0F );
}

