#include "Core.ECS.Component.ZDepth.h"

namespace nECS
{


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
    AddNewVariable( "zdepth", ::nBase::cVariant::MakeVariant( iZDepth ) );
}


cComponent *
cZDepth::Clone()
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


}
