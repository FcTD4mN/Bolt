#include "Core.ECS.Component.Text.h"


#include "Core.ECS.Utilities.ComponentRegistry.h"


namespace nECS {


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------ Construction/Destruction
// -------------------------------------------------------------------------------------


cText::~cText()
{
}


cText::cText() :
    tSuperClass( "color" )
{
    Build( "nothing" );
}


cText::cText( const std::string& iText ) :
    tSuperClass( "color" )
{
    Build( iText );
}


cText::cText( const cText & iText ) :
    tSuperClass( iText )
{
}


void
cText::Build( const std::string & iString )
{
    AddNewVariable( "text", ::nBase::cVariant::MakeVariant( iString ) );
}


// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------- Copy
// -------------------------------------------------------------------------------------


cComponent*
cText::Clone()
{
    return  new cText( *this );
}


const std::string&
cText::Text()
{
    return  GetVar( "text" )->GetValueString();
}


void
cText::Text( const std::string & iText )
{
    GetVar( "text" )->SetValueString( iText );
}


} // namespace nECS

