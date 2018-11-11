#include "Core.ECS.Component.Direction.h"


namespace nCore {
namespace nECS {
namespace nComponent {


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------ Construction/Destruction
// -------------------------------------------------------------------------------------


cDirection::~cDirection()
{
}


cDirection::cDirection() :
    tSuperClass( "direction" )
{
    SetNewVariable( "x", ::nCore::nBase::cVariant::MakeVariant( 0.0 ) );
    SetNewVariable( "y", ::nCore::nBase::cVariant::MakeVariant( 0.0 ) );
}


cDirection::cDirection( float iX, float iY ) :
    tSuperClass( "direction" )
{
    SetNewVariable( "x", ::nCore::nBase::cVariant::MakeVariant( iX ) );
    SetNewVariable( "y", ::nCore::nBase::cVariant::MakeVariant( iY ) );
}


cDirection::cDirection( const sf::Vector2f& iPosition ) :
    tSuperClass( "direction" )
{
    SetNewVariable( "x", ::nCore::nBase::cVariant::MakeVariant( iPosition.x ) );
    SetNewVariable( "y", ::nCore::nBase::cVariant::MakeVariant( iPosition.y ) );
}


cDirection::cDirection( const cDirection & iRHS ) :
    tSuperClass( iRHS )
{
}


// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------- Copy
// -------------------------------------------------------------------------------------


::nCore::nECS::nCore::cComponent*
cDirection::Clone() const
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


} // namespace nComponent
} // namespace nECS
} // namespace nCore

