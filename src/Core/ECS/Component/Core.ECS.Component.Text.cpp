#include "Core.ECS.Component.Text.h"



namespace nCore {
namespace nECS {
namespace nComponent {


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------ Construction/Destruction
// -------------------------------------------------------------------------------------


cText::~cText()
{
}


cText::cText() :
    tSuperClass( "text" )
{
    Build( "nothing" );
}


cText::cText( const std::string& iText ) :
    tSuperClass( "text" )
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
    AddNewVariable( "text", ::nCore::nBase::cVariant::MakeVariant( iString ) );
}


// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------- Copy
// -------------------------------------------------------------------------------------


::nCore::nECS::nCore::cComponent*
cText::Clone() const
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


} // namespace nComponent
} // namespace nECS
} // namespace nCore

