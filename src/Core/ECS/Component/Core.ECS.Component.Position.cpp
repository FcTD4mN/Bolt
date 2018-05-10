#include "Core.ECS.Component.Position.h"


namespace nECS {


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------ Construction/Destruction
// -------------------------------------------------------------------------------------


cPosition::~cPosition()
{
}


cPosition::cPosition() :
    tSuperClass( "position" )
{
    AddNewVariable( "x", ::nBase::cVariant::MakeVariant( 0.0 ) );
    AddNewVariable( "y", ::nBase::cVariant::MakeVariant( 0.0 ) );
}


cPosition::cPosition( float iX, float iY ) :
    tSuperClass( "position" )
{
    AddNewVariable( "x", ::nBase::cVariant::MakeVariant( iX ) );
    AddNewVariable( "y", ::nBase::cVariant::MakeVariant( iY ) );
}


cPosition::cPosition( const sf::Vector2f& iPosition ) :
    tSuperClass( "position" )
{
    AddNewVariable( "x", ::nBase::cVariant::MakeVariant( iPosition.x ) );
    AddNewVariable( "y", ::nBase::cVariant::MakeVariant( iPosition.y ) );
}


cPosition::cPosition( const cPosition & iRHS ) :
    tSuperClass( iRHS )
{
}


// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------- Copy
// -------------------------------------------------------------------------------------


cComponent*
cPosition::Clone()
{
    return  new cPosition(*this);
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------ Access / Set
// -------------------------------------------------------------------------------------


double
cPosition::X()
{
    return  GetVar( "x" )->GetValueNumber();
}


double
cPosition::Y()
{
    return  GetVar( "y" )->GetValueNumber();
}


void
cPosition::X( double iX )
{
    GetVar( "x" )->SetValueNumber( iX );
}


void
cPosition::Y( double iY )
{
    GetVar( "y" )->SetValueNumber( iY );
}


sf::Vector2f
cPosition::AsVector2F()
{
    return  sf::Vector2f( float(X()), float(Y()) );
}


} // namespace nECS

