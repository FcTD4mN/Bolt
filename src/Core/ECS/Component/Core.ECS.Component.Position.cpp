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
    SetVar( "x", ::nBase::cVariant::MakeVariant( 0.0 ) );
    SetVar( "y", ::nBase::cVariant::MakeVariant( 0.0 ) );
}


cPosition::cPosition( float iX, float iY ) :
    tSuperClass( "position" )
{
    SetVar( "x", ::nBase::cVariant::MakeVariant( iX ) );
    SetVar( "y", ::nBase::cVariant::MakeVariant( iY ) );
}


cPosition::cPosition( const sf::Vector2f& iPosition ) :
    tSuperClass( "position" )
{
    SetVar( "x", ::nBase::cVariant::MakeVariant( iPosition.x ) );
    SetVar( "y", ::nBase::cVariant::MakeVariant( iPosition.y ) );
}


cPosition::cPosition( const cPosition& iPosition ) :
    tSuperClass( iPosition )
{
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
    SetVar( "x", ::nBase::cVariant::MakeVariant( iX ) );
}


void
cPosition::Y( double iY )
{
    SetVar( "y", ::nBase::cVariant::MakeVariant( iY ) );
}


} // namespace nECS

