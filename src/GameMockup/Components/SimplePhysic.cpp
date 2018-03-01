 #include "SimplePhysic.h"


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------ Construction/Destruction
// -------------------------------------------------------------------------------------


cSimplePhysic::~cSimplePhysic()
{
}


cSimplePhysic::cSimplePhysic() :
    tSuperClass( "simplephysic" ),
    mHitBox( 0.0F, 0.0F, 0.0F, 0.0F ),
    mVelocity( 0.0F, 0.0F ),
    mType( kStatic )
{
}


cSimplePhysic::cSimplePhysic( float iX, float iY, float iW, float iH, eType iType ) :
    tSuperClass( "simplephysic" ),
    mHitBox( iX, iY, iW, iH ),
    mVelocity( 0.0F, 0.0F ),
    mType( iType )
{
}


cSimplePhysic::cSimplePhysic( const cSimplePhysic & iSimplePhysic ) :
    tSuperClass( iSimplePhysic ),
    mHitBox( iSimplePhysic.mHitBox ),
    mVelocity( iSimplePhysic.mVelocity ),
    mType( iSimplePhysic.mType )
{
}


// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------- Copy
// -------------------------------------------------------------------------------------


cComponent*
cSimplePhysic::Clone()
{
    return  new cSimplePhysic( *this );
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------ Input/Output
// -------------------------------------------------------------------------------------


void
cSimplePhysic::SaveXML( tinyxml2::XMLElement* iNode, tinyxml2::XMLDocument* iDocument )
{
    tSuperClass::SaveXML( iNode, iDocument );
    iNode->SetAttribute( "x", mHitBox.left );
    iNode->SetAttribute( "y", mHitBox.top );
    iNode->SetAttribute( "w", mHitBox.width );
    iNode->SetAttribute( "h", mHitBox.height);

    iNode->SetAttribute( "veloX", mVelocity.x );
    iNode->SetAttribute( "veloY", mVelocity.y );

    iNode->SetAttribute( "type", mType );
}


void
cSimplePhysic::LoadXML( tinyxml2::XMLElement* iNode )
{
    tSuperClass::LoadXML( iNode );
    mHitBox.left    = iNode->FloatAttribute( "x", 0.0F );
    mHitBox.top     = iNode->FloatAttribute( "y", 0.0F );
    mHitBox.width   = iNode->FloatAttribute( "w", 0.0F );
    mHitBox.height  = iNode->FloatAttribute( "h", 0.0F );

    mVelocity.x     = iNode->FloatAttribute( "veloX", 0.0F );
    mVelocity.y     = iNode->FloatAttribute( "veloY", 0.0F );

    mType = eType( iNode->IntAttribute( "type", 0 ) );
}



