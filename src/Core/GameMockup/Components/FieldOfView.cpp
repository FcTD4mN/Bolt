#include "FieldOfView.h"

#include "ECS/Utilities/ComponentRegistry.h"

// -------------------------------------------------------------------------------------
// ------------------------------------------------------------ Construction/Destruction
// -------------------------------------------------------------------------------------


cFieldOfView::~cFieldOfView()
{
}


cFieldOfView::cFieldOfView() :
    tSuperClass( "fieldofview" ),
    mAngle( 0.0 )
{
}


cFieldOfView::cFieldOfView( double iAngle ) :
    tSuperClass( "fieldofview" ),
    mAngle( iAngle )
{
}


cFieldOfView::cFieldOfView( const cFieldOfView & iFOV ) :
    tSuperClass( iFOV ),
    mAngle( iFOV.mAngle )
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
// ------------------------------------------------------------------------ Input/Output
// -------------------------------------------------------------------------------------


void
cFieldOfView::SaveXML( tinyxml2::XMLElement* iNode, tinyxml2::XMLDocument* iDocument )
{
    tSuperClass::SaveXML( iNode, iDocument );
    iNode->SetAttribute( "angle", mAngle );
}


void
cFieldOfView::LoadXML( tinyxml2::XMLElement* iNode )
{
    tSuperClass::LoadXML( iNode );
    mAngle = iNode->DoubleAttribute( "angle", 0.0 );
}

