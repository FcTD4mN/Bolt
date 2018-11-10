#include "Core.ECS.Component.Transformation.h"


#include "Core.ECS.Core.Entity.h"
#include "Core.Mapping.EntityMap.h"
#include "Core.Render.Layer.h"


namespace nCore {
namespace nECS {
namespace nComponent {


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------ Construction/Destruction
// -------------------------------------------------------------------------------------


cTransformation::~cTransformation()
{
}


cTransformation::cTransformation() :
    tSuperClass( "transformation" )
{
    BuildVariables( sf::FloatRect( 0.0F, 0.0F, 0.0F, 0.0F ), 0.0F );
    BuildCallbacks();
}


cTransformation::cTransformation( const sf::FloatRect& iRect, float iRotation ) :
    tSuperClass( "transformation" )
{
    BuildVariables( iRect, iRotation );
    BuildCallbacks();
}


cTransformation::cTransformation( const sf::Vector2f& iPosition, const sf::Vector2f& iSize, float iRotation ) :
    tSuperClass( "transformation" )
{
    BuildVariables( sf::FloatRect( iPosition, iSize ), iRotation );
    BuildCallbacks();
}


cTransformation::cTransformation( const cTransformation & iRHS ) :
    tSuperClass( iRHS )
{
    BuildCallbacks();

    mPreviousRect = iRHS.mPreviousRect;
    mPreviousRotation = iRHS.mPreviousRotation;
}


void
cTransformation::BuildVariables( const sf::FloatRect& iRect, float iRotation )
{
    AddNewVariable( "x", ::nCore::nBase::cVariant::MakeVariant( iRect.left ) );
    AddNewVariable( "y", ::nCore::nBase::cVariant::MakeVariant( iRect.top ) );
    AddNewVariable( "width", ::nCore::nBase::cVariant::MakeVariant( iRect.width ) );
    AddNewVariable( "height", ::nCore::nBase::cVariant::MakeVariant( iRect.height ) );
    AddNewVariable( "rotation", ::nCore::nBase::cVariant::MakeVariant( iRotation ) );

    mPreviousRect = iRect;
    mPreviousRotation = iRotation;
}



void
cTransformation::BuildCallbacks()
{
    // The function stores values of the whole transformation component as it was one step before
    /*
        Why do we set All variables instead of just : if x changed, we set previous.left only ? :
        Let's say i have a rect at 0,10 coordinates.
        Previous rect was 0, 0
        I change its X coord to now 10, 10
        -- > Then, according to a single value change callback approach, it would do:
        previous rect.left == old value of X,
        which was 0 before it changes( we went from 0, 10 to 10, 10 )

        So by the end of it, we had a rect at 0, 10, now a rect at 10, 10,
        BUT the previous rect is still 0, 0 right, because we didn't change previous.TOP value, as we only changed X --> PROBLEM.
        That's why, when we change any value, the previous rect has to be changed entirely.


        //OPTIMIZE:
        This could potentially be cost heavy if we change X, Y, as we'll do double update, when we could only do one update after both value changed
        If this ever happen to be laggy, just add a  bool disengageUpdate in this transformation component, so that when disengaged, it won't update at all
        Then reengage it after changes on coordinates are done, and do one single update.
    */

        auto function = [ this ]( ::nCore::nBase::eVariableState iState ){

        if( iState == ::nCore::nBase::eVariableState::kBeforeChange )
        {
            mPreviousRect.left = float( X() );
            mPreviousRect.top = float( Y() );
            mPreviousRect.width = float( W() );
            mPreviousRect.height = float( H() );
            mPreviousRotation = float( Rotation() );
        }
        else if( iState == ::nCore::nBase::eVariableState::kAfterChange )
        {
            auto layer = mEntityOwner->Layer();
            if( layer ) // We can change entity transform before adding it into world, thus before having a layer associated
                mEntityOwner->Layer()->EntityMap()->UpdateEntity( mEntityOwner );
        }
    };


    SetVarValueChangeCallback( "x", function );
    SetVarValueChangeCallback( "y", function );
    SetVarValueChangeCallback( "width", function );
    SetVarValueChangeCallback( "height", function );
    SetVarValueChangeCallback( "rotation", function );
}


// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------- Copy
// -------------------------------------------------------------------------------------


::nCore::nECS::nCore::cComponent*
cTransformation::Clone() const
{
    return  new cTransformation(*this);
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------ Access / Set
// -------------------------------------------------------------------------------------


double
cTransformation::X()
{
    return  GetVar( "x" )->GetValueNumber();
}


double
cTransformation::Y()
{
    return  GetVar( "y" )->GetValueNumber();
}


void
cTransformation::X( double iX )
{
    GetVar( "x" )->SetValueNumber( iX );
}


void
cTransformation::Y( double iY )
{
    GetVar( "y" )->SetValueNumber( iY );
}


double
cTransformation::W()
{
    return  GetVar( "width" )->GetValueNumber();
}


double
cTransformation::H()
{
    return  GetVar( "height" )->GetValueNumber();
}


void
cTransformation::W( double iW )
{
    GetVar( "width" )->SetValueNumber( iW );
}


void
cTransformation::H( double iH )
{
    GetVar( "height" )->SetValueNumber( iH );
}


double
cTransformation::Rotation()
{
    return  GetVar( "rotation" )->GetValueNumber();
}


void
cTransformation::Rotation( double iRotation )
{
    GetVar( "rotation" )->SetValueNumber( iRotation );
}


sf::Vector2f
cTransformation::PositionAsVector2F()
{
    return  sf::Vector2f( float(X()), float(Y()) );
}


sf::Vector2f
cTransformation::SizeAsVector2F()
{
    return  sf::Vector2f( float( W() ), float( H() ) );
}


sf::Vector2f
cTransformation::PreviousPosition() const
{
    return  sf::Vector2f( mPreviousRect.left, mPreviousRect.top );
}


sf::Vector2f
cTransformation::PreviousSize() const
{
    return  sf::Vector2f( mPreviousRect.width, mPreviousRect.height );
}


double
cTransformation::PreviousRotation() const
{
    return  mPreviousRotation;
}


void
cTransformation::LoadXML( tinyxml2::XMLElement * iNode )
{
    tSuperClass::LoadXML( iNode );
    mPreviousRect.left = float( X() );
    mPreviousRect.top = float( Y() );
    mPreviousRect.width = float( W() );
    mPreviousRect.height = float( H() );
    mPreviousRotation = Rotation();

    BuildCallbacks();
}


} // namespace nComponent
} // namespace nECS
} // namespace nCore

