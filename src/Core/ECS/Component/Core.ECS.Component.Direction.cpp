#include "Core.ECS.Component.Direction.h"


namespace nECS {


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------ Construction/Destruction
// -------------------------------------------------------------------------------------


cDirection::~cDirection()
{
}


cDirection::cDirection() :
    tSuperClass( "direction" )
{
    SetVar( "x", ::nBase::cVariant::MakeVariant( 0.0 ) );
    SetVar( "y", ::nBase::cVariant::MakeVariant( 0.0 ) );
}


cDirection::cDirection( float iX, float iY ) :
    tSuperClass( "direction" )
{
    SetVar( "x", ::nBase::cVariant::MakeVariant( iX ) );
    SetVar( "y", ::nBase::cVariant::MakeVariant( iY ) );
}


cDirection::cDirection( const sf::Vector2f& iPosition ) :
    tSuperClass( "direction" )
{
    SetVar( "x", ::nBase::cVariant::MakeVariant( iPosition.x ) );
    SetVar( "y", ::nBase::cVariant::MakeVariant( iPosition.y ) );
}


cDirection::cDirection( const cDirection & iRHS ) :
    tSuperClass( iRHS )
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
// ------------------------------------------------------------------------ Access / Set
// -------------------------------------------------------------------------------------


double
cDirection::X()
{
    return  GetVar( "x" )->GetValueNumber();
}


double
cDirection::Y()
{
    return  GetVar( "y" )->GetValueNumber();
}


void
cDirection::X( double iX )
{
    GetVar( "x" )->SetValueNumber( iX );
}


void
cDirection::Y( double iY )
{
    GetVar( "y" )->SetValueNumber( iY );
}


sf::Vector2f
cDirection::AsVector2F()
{
    return  sf::Vector2f( float(X()), float(Y()) );
}


void
cDirection::SetUsingVector( const sf::Vector2f & iVector )
{
    X( iVector.x );
    Y( iVector.y );
}


} // namespace nECS

