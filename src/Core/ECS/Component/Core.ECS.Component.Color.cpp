#include "Core.ECS.Component.Color.h"


#include "Core.ECS.Utilities.ComponentRegistry.h"


namespace nECS {


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------ Construction/Destruction
// -------------------------------------------------------------------------------------


cColor::~cColor()
{
}


cColor::cColor() :
    tSuperClass( "color" )
{
    Build( 0, 0, 0, 255 );
}


cColor::cColor( int iR, int iG, int iB, int iA ) :
    tSuperClass( "color" )
{
    Build( iR, iG, iB, iA );
}


cColor::cColor( const sf::Color& iColor ) :
    tSuperClass( "color" )
{
    Build( iColor.r, iColor.g, iColor.b, iColor.a );
}


cColor::cColor( const cColor & iRHS ) :
    tSuperClass( iRHS )
{
}


void
cColor::Build( int iR, int iG, int iB, int iA )
{
    AddNewVariable( "r", ::nBase::cVariant::MakeVariant( iR ) );
    AddNewVariable( "g", ::nBase::cVariant::MakeVariant( iG ) );
    AddNewVariable( "b", ::nBase::cVariant::MakeVariant( iB ) );
    AddNewVariable( "a", ::nBase::cVariant::MakeVariant( iA ) );
}


// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------- Copy
// -------------------------------------------------------------------------------------


cComponent*
cColor::Clone()
{
    return  new cColor( *this );
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------ Access / Set
// -------------------------------------------------------------------------------------


int
cColor::R()
{
    return  int(GetVar( "r" )->GetValueNumber());
}


int
cColor::G()
{
    return  int( GetVar( "g" )->GetValueNumber() );
}


int
cColor::B()
{
    return  int( GetVar( "b" )->GetValueNumber() );
}


int
cColor::A()
{
    return  int( GetVar( "a" )->GetValueNumber() );
}



void
cColor::R( int iR )
{
    GetVar( "r" )->SetValueNumber( iR );
}


void
cColor::G( int iG )
{
    GetVar( "g" )->SetValueNumber( iG );
}


void
cColor::B( int iB )
{
    GetVar( "b" )->SetValueNumber( iB );
}


void
cColor::A( int iA )
{
    GetVar( "a" )->SetValueNumber( iA );
}


sf::Color
cColor::AsSFCOlor()
{
    return  sf::Color( R(), G(), B(), A() );
}



} // namespace nECS

