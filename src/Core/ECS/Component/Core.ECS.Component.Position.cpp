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
    AddNewVariable( "x", ::nCore::nBase::cVariant::MakeVariant( 0.0 ) );
    AddNewVariable( "y", ::nCore::nBase::cVariant::MakeVariant( 0.0 ) );
    BuildCallbacks();
}


cPosition::cPosition( float iX, float iY ) :
    tSuperClass( "position" )
{
    AddNewVariable( "x", ::nCore::nBase::cVariant::MakeVariant( iX ) );
    AddNewVariable( "y", ::nCore::nBase::cVariant::MakeVariant( iY ) );
    BuildCallbacks();
}


cPosition::cPosition( const sf::Vector2f& iPosition ) :
    tSuperClass( "position" )
{
    AddNewVariable( "x", ::nCore::nBase::cVariant::MakeVariant( iPosition.x ) );
    AddNewVariable( "y", ::nCore::nBase::cVariant::MakeVariant( iPosition.y ) );
    BuildCallbacks();
}


cPosition::cPosition( const cPosition & iRHS ) :
    tSuperClass( iRHS )
{
    BuildCallbacks();
}


void
cPosition::BuildCallbacks()
{
    SetVarValueChangeCallback( "x", [ this ]( ::nCore::nBase::eVariableState iState ){

        if( iState == ::nCore::nBase::eVariableState::kBeforeChange )
            mPreviousPosition.x = float(X());
    } );

    SetVarValueChangeCallback( "y", [ this ]( ::nCore::nBase::eVariableState iState ){

        if( iState == ::nCore::nBase::eVariableState::kBeforeChange )
            mPreviousPosition.y = float(Y());
    } );
}


// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------- Copy
// -------------------------------------------------------------------------------------


::nCore::nECS::nCore::cComponent*
cPosition::Clone() const
{
    return  new cPosition(*this);
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
    GetVar( "x" )->SetValueNumber( iX );
}


void
cPosition::Y( double iY )
{
    GetVar( "y" )->SetValueNumber( iY );
}


sf::Vector2f
cPosition::AsVector2F()
{
    return  sf::Vector2f( float(X()), float(Y()) );
}


const sf::Vector2f&
cPosition::PreviousPosition() const
{
    return  mPreviousPosition;
}


void
cPosition::LoadXML( tinyxml2::XMLElement * iNode )
{
    tSuperClass::LoadXML( iNode );
    BuildCallbacks();
}


} // namespace nECS

