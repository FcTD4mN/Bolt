#include "Core.ECS.Component.OcclusionFactor.h"


#include "Core.Sound.FX.h"

namespace nECS {


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
    AddNewVariable( "occlusionfactor", ::nBase::cVariant::MakeVariant( iValue ) );
}


// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------- Copy
// -------------------------------------------------------------------------------------


cComponent*
cOcclusionFactor::Clone()
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


} // namespace nECS

