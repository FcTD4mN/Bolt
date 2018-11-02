#include "Core.ECS.Component.FieldOfView.h"


namespace nCore {
namespace nECS {
namespace nComponent {


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------ Construction/Destruction
// -------------------------------------------------------------------------------------


cFieldOfView::~cFieldOfView()
{
}


cFieldOfView::cFieldOfView() :
    tSuperClass( "fieldofview" )
{
    AddNewVariable( "angle", ::nCore::nBase::cVariant::MakeVariant( 0.0 ) );
    AddNewVariable( "distance", ::nCore::nBase::cVariant::MakeVariant( 0.0 ) );
}


cFieldOfView::cFieldOfView( double iAngle, double iDistance ) :
    tSuperClass( "fieldofview" )
{
    AddNewVariable( "angle", ::nCore::nBase::cVariant::MakeVariant( iAngle ) );
    AddNewVariable( "distance", ::nCore::nBase::cVariant::MakeVariant( iDistance ) );
}


cFieldOfView::cFieldOfView( const cFieldOfView & iRHS ) :
    tSuperClass( iRHS )
{
}


// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------- Copy
// -------------------------------------------------------------------------------------


::nCore::nECS::nCore::cComponent*
cFieldOfView::Clone() const
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


} // namespace nComponent
} // namespace nECS
} // namespace nCore

