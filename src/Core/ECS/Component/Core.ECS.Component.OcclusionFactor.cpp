#include "Core.ECS.Component.OcclusionFactor.h"


#include "Core.Sound.FX.h"


namespace nCore {
namespace nECS {
namespace nComponent {


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------ Construction/Destruction
// -------------------------------------------------------------------------------------


cOcclusionFactor::~cOcclusionFactor()
{
}


cOcclusionFactor::cOcclusionFactor() :
    tSuperClass( "occlusionfactor" )
{
    Build( 1.0F );
}


cOcclusionFactor::cOcclusionFactor( double iValue ) :
    tSuperClass( "occlusionfactor" )
{
    Build( iValue );
}


cOcclusionFactor::cOcclusionFactor( const cOcclusionFactor & iRHS ) :
    tSuperClass( iRHS )
{
}


void
cOcclusionFactor::Build( double iValue )
{
    AddNewVariable( "occlusionfactor", ::nCore::nBase::cVariant::MakeVariant( iValue ) );
}


// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------- Copy
// -------------------------------------------------------------------------------------


::nCore::nECS::nCore::cComponent*
cOcclusionFactor::Clone() const
{
    return  new cOcclusionFactor( *this );
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------ Access / Set
// -------------------------------------------------------------------------------------


double
cOcclusionFactor::OcclusionFactor()
{
    return  GetVar( "occlusionfactor" )->GetValueNumber();
}


void
cOcclusionFactor::OcclusionFactor( double iValue )
{
    GetVar( "occlusionfactor" )->SetValueNumber( iValue );
}


} // namespace nComponent
} // namespace nECS
} // namespace nCore

