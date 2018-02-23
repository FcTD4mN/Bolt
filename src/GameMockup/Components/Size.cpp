#include "Size.h"


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------ Construction/Destruction
// -------------------------------------------------------------------------------------


cSize::~cSize()
{
}


cSize::cSize() :
    tSuperClass( "size" ),
    mSize( sf::Vector2f( 0, 0 ) )
{
}


cSize::cSize( float iW, float iH ) :
    tSuperClass( "size" ),
    mSize( sf::Vector2f( iW, iH ) )
{
}


cSize::cSize( const sf::Vector2f& iSize ) :
    tSuperClass( "size" ),
    mSize( iSize )
{
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------ Input/Output
// -------------------------------------------------------------------------------------


void
cSize::SaveXML( tinyxml2::XMLElement* iNode, tinyxml2::XMLDocument* iDocument )
{
    tSuperClass::SaveXML( iNode, iDocument );
    iNode->SetAttribute( "w", mSize.x );
    iNode->SetAttribute( "h", mSize.y );
}


void
cSize::LoadXML( const tinyxml2::XMLElement* iNode )
{
    tSuperClass::LoadXML( iNode );
    mSize.x = iNode->FloatAttribute( "w", 0.0F );
    mSize.y = iNode->FloatAttribute( "h", 0.0F );

}

