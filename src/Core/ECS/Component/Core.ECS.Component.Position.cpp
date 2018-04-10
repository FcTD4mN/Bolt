#include "Core.ECS.Component.Position.h"


namespace nECS {


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------ Construction/Destruction
// -------------------------------------------------------------------------------------


cPosition::~cPosition()
{
}


cPosition::cPosition() :
    tSuperClass( "position" ),
    mPosition( sf::Vector2i( 0, 0 ) )
{
}


cPosition::cPosition( float iX, float iY ) :
    tSuperClass( "position" ),
    mPosition( sf::Vector2f( iX, iY ) )
{
}


cPosition::cPosition( const sf::Vector2f& iPosition ) :
    tSuperClass( "position" ),
    mPosition( iPosition )
{
}


cPosition::cPosition( const cPosition & iPosition ) :
    tSuperClass( iPosition ),
    mPosition( iPosition.mPosition )
{
}


// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------- Copy
// -------------------------------------------------------------------------------------


cComponent*
cPosition::Clone()
{
    return  new cPosition( *this );
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------ Input/Output
// -------------------------------------------------------------------------------------


void
cPosition::SaveXML( tinyxml2::XMLElement* iNode, tinyxml2::XMLDocument* iDocument )
{
    tSuperClass::SaveXML( iNode, iDocument );
    iNode->SetAttribute( "x", mPosition.x );
    iNode->SetAttribute( "y", mPosition.y );
}


void
cPosition::LoadXML( tinyxml2::XMLElement* iNode )
{
    tSuperClass::LoadXML( iNode );
    mPosition.x = iNode->FloatAttribute( "x", 0.0F );
    mPosition.y = iNode->FloatAttribute( "y", 0.0F );
}


// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------



// -------------------------------------------------------------------------------------
// ------------------------------------------------------------ Construction/Destruction
// -------------------------------------------------------------------------------------


cGPosition::~cGPosition()
{
}


cGPosition::cGPosition() :
    tSuperClass( "position" )
{
    ::nBase::cVariant x( 0.0 );
    ::nBase::cVariant y( 0.0 );
    SetVar( "x", x );
    SetVar( "y", y );
}


cGPosition::cGPosition( float iX, float iY ) :
    tSuperClass( "position" )
{
    ::nBase::cVariant x( iX );
    ::nBase::cVariant y( iY );
    SetVar( "x", x );
    SetVar( "y", y );
}


cGPosition::cGPosition( const sf::Vector2f& iPosition ) :
    tSuperClass( "position" )
{
    ::nBase::cVariant x( iPosition.x );
    ::nBase::cVariant y( iPosition.y );
    SetVar( "x", x );
    SetVar( "y", y );
}


cGPosition::cGPosition( const cGPosition& iPosition ) :
    tSuperClass( iPosition )
{
}


// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------- Copy
// -------------------------------------------------------------------------------------


cComponentGeneric*
cGPosition::Clone()
{
    return  new cGPosition( *this );
}

} // namespace nECS

