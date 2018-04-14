#include "Core.ECS.Component.FieldOfView.h"


namespace nECS {


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------ Construction/Destruction
// -------------------------------------------------------------------------------------


cFieldOfView::~cFieldOfView()
{
}


cFieldOfView::cFieldOfView() :
    tSuperClass( "fieldofview" )
{
    SetVar( "angle", ::nBase::cVariant::MakeVariant( 0.0 ) );
    SetVar( "distance", ::nBase::cVariant::MakeVariant( 0.0 ) );
}


cFieldOfView::cFieldOfView( double iAngle, double iDistance ) :
    tSuperClass( "fieldofview" )
{
    SetVar( "angle", ::nBase::cVariant::MakeVariant( iAngle ) );
    SetVar( "distance", ::nBase::cVariant::MakeVariant( iDistance ) );
}


cFieldOfView::cFieldOfView( const cFieldOfView & iRHS ) :
    tSuperClass( iRHS )
{
}


// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------- Copy
// -------------------------------------------------------------------------------------


cComponent*
cFieldOfView::Clone()
{
    return  new cFieldOfView( *this );
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------ Access / Set
// -------------------------------------------------------------------------------------


double
cFieldOfView::Angle()
{
    return  GetVar( "angle" )->GetValueNumber();
}


double
cFieldOfView::Distance()
{
    return  GetVar( "distance" )->GetValueNumber();
}


void
cFieldOfView::Angle( double iAngle )
{
    GetVar( "angle" )->SetValueNumber( iAngle );
}


void
cFieldOfView::Distance( double iDistance )
{
    GetVar( "distance" )->SetValueNumber( iDistance );
}

} // namespace nECS

