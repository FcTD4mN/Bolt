 #include "Core.ECS.Component.SimplePhysic.h"


#include "Core.ECS.Core.Entity.h"


namespace nCore {
namespace nECS {
namespace nComponent {


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------ Construction/Destruction
// -------------------------------------------------------------------------------------


cSimplePhysic::~cSimplePhysic()
{
}


cSimplePhysic::cSimplePhysic() :
    tSuperClass( "simplephysic" ),
    mVelocity( 0.0F, 0.0F ),
    mType( kStatic )
{
    BuildComponent( 0.0, 0.0, 0.0, 0.0, kStatic, false );
}


cSimplePhysic::cSimplePhysic( double iW, double iH, eType iType, bool iIsTrigger ) :
    tSuperClass( "simplephysic" ),
    mVelocity( 0.0F, 0.0F ),
    mType( iType )
{
    BuildComponent( 0.0, 0.0, iW, iH, iType, iIsTrigger );
}


cSimplePhysic::cSimplePhysic( const cSimplePhysic & iSimplePhysic ) :
    tSuperClass( iSimplePhysic ),
    mVelocity( iSimplePhysic.mVelocity ),
    mType( iSimplePhysic.mType ),
    mCollisionCB( 0 ), // Don't copy a function pointer
	mIsCacheValid( false )
{
}


void
cSimplePhysic::BuildComponent( double iCenterX, double iCenterY, double iSizeW, double iSizeH, eType iType, bool iIsTrigger )
{
    mCollisionCB = 0;

    AddNewVariable( "CenterX", ::nCore::nBase::cVariant::MakeVariant( iCenterX ) );
    AddNewVariable( "CenterY", ::nCore::nBase::cVariant::MakeVariant( iCenterY ) );
    AddNewVariable( "SizeW", ::nCore::nBase::cVariant::MakeVariant( iSizeW ) );
    AddNewVariable( "SizeH", ::nCore::nBase::cVariant::MakeVariant( iSizeH ) );
    AddNewVariable( "GravityFactor", ::nCore::nBase::cVariant::MakeVariant( 1.0 ) );
    AddNewVariable( "IsTrigger", ::nCore::nBase::cVariant::MakeVariant( iIsTrigger ) );

    mIsCacheValid = false;
}


// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------- Copy
// -------------------------------------------------------------------------------------


::nCore::nECS::nCore::cComponent*
cSimplePhysic::Clone() const
{
    return  new cSimplePhysic( *this );
}


cSimplePhysic::eType
cSimplePhysic::PhysicType() const
{
    return  mType;
}


void
cSimplePhysic::PhysicType( eType iType )
{
    mType = iType;
}


double
cSimplePhysic::CenterX()
{
    return  GetVar( "CenterX" )->GetValueNumber();
}


double
cSimplePhysic::CenterY()
{
    return  GetVar( "CenterY" )->GetValueNumber();
}


sf::Vector2f
cSimplePhysic::CenterAsVector2f()
{
    return  sf::Vector2f( float(CenterX()), float(CenterY()) );
}


void
cSimplePhysic::SetCenter( const sf::Vector2f & iCenter )
{
    GetVar( "CenterX" )->SetValueNumber( iCenter.x );
    GetVar( "CenterY" )->SetValueNumber( iCenter.y );
    mIsCacheValid = false;
}


double
cSimplePhysic::SizeW()
{
    return  GetVar( "SizeW" )->GetValueNumber();
}


double
cSimplePhysic::SizeH()
{
    return  GetVar( "SizeH" )->GetValueNumber();
}


sf::Vector2f
cSimplePhysic::SizeAsVector2f()
{
    return  sf::Vector2f( float(SizeW()), float(SizeH()) );
}


void
cSimplePhysic::SetSize( const sf::Vector2f & iSize )
{
    GetVar( "SizeW" )->SetValueNumber( iSize.x );
    GetVar( "SizeH" )->SetValueNumber( iSize.y );
    mIsCacheValid = false;
}


double
cSimplePhysic::GravityFactor()
{
    return  GetVar( "GravityFactor" )->GetValueNumber();
}


void
cSimplePhysic::GravityFactor( double iGravityFactor )
{
    GetVar( "GravityFactor" )->SetValueNumber( iGravityFactor );
}


bool
cSimplePhysic::IsTrigger()
{
    return  GetVar( "IsTrigger" )->GetValueBool();
}


void
cSimplePhysic::IsTrigger( bool iIsTrigger )
{
    GetVar( "IsTrigger" )->SetValueBool( iIsTrigger );

}


void
cSimplePhysic::SetCollisionCB( std::function<void( ::nCore::nECS::nCore::cEntity* iCollider )> iCB )
{
    mCollisionCB = iCB;
}


void
cSimplePhysic::CallCollisionCB( ::nCore::nECS::nCore::cEntity * iEntity )
{
    if( mCollisionCB )
        mCollisionCB( iEntity );
}


sf::FloatRect
cSimplePhysic::RelativeHitBox()
{
    return  sf::FloatRect( CenterAsVector2f() - SizeAsVector2f()/2.0F, SizeAsVector2f() );
}


sf::FloatRect
cSimplePhysic::GetAbsoluteHitBoxUsingCenterPosition( const sf::Vector2f & iCenterPosition )
{
    if( mIsCacheValid && mCachedHitBoxCenter == iCenterPosition )
        return  mCachedHitBox;

    sf::Rect< float > entityHitBox;

    entityHitBox = RelativeHitBox();
    entityHitBox.left += iCenterPosition.x;
    entityHitBox.top += iCenterPosition.y;

    mCachedHitBox = entityHitBox;
    mIsCacheValid = true;
	mCachedHitBoxCenter = iCenterPosition;

    return  entityHitBox;
}


void
cSimplePhysic::InvalidCache()
{
    mIsCacheValid = false;
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------ Input/Output
// -------------------------------------------------------------------------------------


void
cSimplePhysic::SaveXML( tinyxml2::XMLElement* iNode, tinyxml2::XMLDocument* iDocument )  const
{
    tSuperClass::SaveXML( iNode, iDocument );

    iNode->SetAttribute( "veloX", mVelocity.x );
    iNode->SetAttribute( "veloY", mVelocity.y );

    iNode->SetAttribute( "type", mType );
}


void
cSimplePhysic::LoadXML( tinyxml2::XMLElement* iNode )
{
    tSuperClass::LoadXML( iNode );

    mVelocity.x     = iNode->FloatAttribute( "veloX", 0.0F );
    mVelocity.y     = iNode->FloatAttribute( "veloY", 0.0F );

    mType = eType( iNode->IntAttribute( "type", 0 ) );
}


} // namespace nComponent
} // namespace nECS
} // namespace nCore

