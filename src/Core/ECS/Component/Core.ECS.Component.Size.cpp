#include "Core.ECS.Component.Size.h"


namespace nECS {


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------ Construction/Destruction
// -------------------------------------------------------------------------------------


cSize::~cSize()
{
}


cSize::cSize() :
    tSuperClass( "direction" )
{
    Build( 0.0F, 0.0F );
}


cSize::cSize( float iW, float iH ) :
    tSuperClass( "direction" )
{
    Build( iW, iH );
}


cSize::cSize( const sf::Vector2f& iPosition ) :
    tSuperClass( "direction" )
{
    Build( iPosition.x, iPosition.y );
}


cSize::cSize( const cSize & iRHS ) :
    tSuperClass( iRHS )
{
}


void
cSize::Build( float iW, float iH )
{
    SetVar( "w", ::nBase::cVariant::MakeVariant( iW ) );
    SetVar( "h", ::nBase::cVariant::MakeVariant( iH ) );
}


// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------- Copy
// -------------------------------------------------------------------------------------


cSize*
cSize::Clone()
{
    return  new cSize( *this );
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------ Access / Set
// -------------------------------------------------------------------------------------


double
cSize::W()
{
    return  GetVar( "w" )->GetValueNumber();
}


double
cSize::H()
{
    return  GetVar( "h" )->GetValueNumber();
}


void
cSize::W( double iW )
{
    SetVar( "w", ::nBase::cVariant::MakeVariant( iW ) );
}


void
cSize::H( double iH )
{
    SetVar( "h", ::nBase::cVariant::MakeVariant( iH ) );
}


sf::Vector2f
cSize::AsVector2F()
{
    return  sf::Vector2f( float(W()), float(H()) );
}


void
cSize::SetUsingVector( const sf::Vector2f & iVector )
{
    W( iVector.x );
    H( iVector.y );
}


} // namespace nECS

