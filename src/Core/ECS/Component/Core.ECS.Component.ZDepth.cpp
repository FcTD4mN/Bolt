#include "Core.ECS.Component.ZDepth.h"


namespace nCore {
namespace nECS {
namespace nComponent {


cZDepth::~cZDepth()
{
}


cZDepth::cZDepth() :
    tSuperClass( "zdepth" )
{
}


cZDepth::cZDepth( float iZDepth ) :
    tSuperClass( "zdepth" )
{
    Build( iZDepth );
}


cZDepth::cZDepth( const cZDepth & iRHS ) :
    tSuperClass( iRHS )
{
}


void
cZDepth::Build( float iZDepth )
{
    AddNewVariable( "zdepth", ::nCore::nBase::cVariant::MakeVariant( iZDepth ) );
}


::nCore::nECS::nCore::cComponent*
cZDepth::Clone() const
{
    return  new  cZDepth( *this );
}


double
cZDepth::ZDepth()
{
    return  GetVar( "zdepth" )->GetValueNumber();
}


void
cZDepth::ZDepth( double iZDepth )
{
    GetVar( "zdepth" )->SetValueNumber( iZDepth );
}


} // namespace nComponent
} // namespace nECS
} // namespace nCore

