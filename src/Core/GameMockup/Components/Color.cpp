#include "Color.h"

#include "ECS/Utilities/ComponentRegistry.h"

// -------------------------------------------------------------------------------------
// ------------------------------------------------------------ Construction/Destruction
// -------------------------------------------------------------------------------------


cColor::~cColor()
{
}


cColor::cColor() :
    tSuperClass( "color" ),
    mColor( sf::Color( 0, 0, 0, 255 ) )
{
}


cColor::cColor( int iR, int iG, int iB, int iA ) :
    tSuperClass( "color" ),
    mColor( sf::Color( iR, iG, iB, iA ) )
{
}


cColor::cColor( sf::Color iColor ) :
    tSuperClass( "color" ),
    mColor( sf::Color( iColor ) )

{
}


cColor::cColor( const cColor & iColor ) :
    tSuperClass( iColor ),
    mColor( iColor.mColor )
{
}


// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------- Copy
// -------------------------------------------------------------------------------------


cComponent*
cColor::Clone()
{
    return  new cColor( *this );
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------ Input/Output
// -------------------------------------------------------------------------------------


void
cColor::SaveXML( tinyxml2::XMLElement* iNode, tinyxml2::XMLDocument* iDocument )
{
    tSuperClass::SaveXML( iNode, iDocument );
    iNode->SetAttribute( "colorr", mColor.r );
    iNode->SetAttribute( "colorg", mColor.g );
    iNode->SetAttribute( "colorb", mColor.b );
    iNode->SetAttribute( "colora", mColor.a );
}


void
cColor::LoadXML( tinyxml2::XMLElement* iNode )
{
    tSuperClass::LoadXML( iNode );
    mColor.r = iNode->IntAttribute( "colorr", 0 );
    mColor.g = iNode->IntAttribute( "colorg", 0 );
    mColor.b = iNode->IntAttribute( "colorb", 0 );
    mColor.a = iNode->IntAttribute( "colora", 255 );
}

