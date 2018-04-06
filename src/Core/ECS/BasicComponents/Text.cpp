#include "Text.h"

#include "ECS/Utilities/ComponentRegistry.h"

// -------------------------------------------------------------------------------------
// ------------------------------------------------------------ Construction/Destruction
// -------------------------------------------------------------------------------------


cText::~cText()
{
}


cText::cText() :
    tSuperClass( "color" ),
    mText( "nothing" )
{
}


cText::cText( const std::string& iText ) :
    tSuperClass( "color" ),
    mText( iText )
{
}


cText::cText( const cText & iText ) :
    tSuperClass( iText ),
    mText( iText.mText )
{
}


// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------- Copy
// -------------------------------------------------------------------------------------


cComponent*
cText::Clone()
{
    return  new cText( *this );
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------ Input/Output
// -------------------------------------------------------------------------------------


void
cText::SaveXML( tinyxml2::XMLElement* iNode, tinyxml2::XMLDocument* iDocument )
{
    tSuperClass::SaveXML( iNode, iDocument );
    iNode->SetAttribute( "text", mText.c_str() );
}


void
cText::LoadXML( tinyxml2::XMLElement* iNode )
{
    tSuperClass::LoadXML( iNode );
    mText = iNode->Attribute( "text" );
}

