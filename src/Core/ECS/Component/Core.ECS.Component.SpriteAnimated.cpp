#include "Core.ECS.Component.SpriteAnimated.h"


#include "Core.Base.ResourceManager.h"


namespace nECS {


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------ Construction/Destruction
// -------------------------------------------------------------------------------------


cSpriteAnimated::~cSpriteAnimated()
{
}


cSpriteAnimated::cSpriteAnimated() :
    tSuperClass( "spriteanimated" )
{
    Build( "empty", 1, 1 );
}


cSpriteAnimated::cSpriteAnimated( const std::string& iFile, int iW, int iH ) :
    tSuperClass( "spriteanimated" ),
    mCurrentSpriteRect( 0, 0, iW, iH )
{
    Build( iFile, iW, iH );
}


cSpriteAnimated::cSpriteAnimated( const cSpriteAnimated & iSpriteAnimated ) :
    tSuperClass( iSpriteAnimated ),
    mSpriteSheet( iSpriteAnimated.mSpriteSheet ), // Copy pointer -> Same object, but this is what we want, we don't copy a same texture ( that's why we have a resource manager )
    mSprite( iSpriteAnimated.mSprite ),
    mCurrentSpriteRect( iSpriteAnimated.mCurrentSpriteRect ),
    mClock( iSpriteAnimated.mClock )
{
}


void
cSpriteAnimated::Build( const std::string & iFile, int iW, int iH )
{
    SetVar( "filename", ::nBase::cVariant::MakeVariant( iFile ) );
    SetVar( "framerate", ::nBase::cVariant::MakeVariant( 24.0 ) );
    SetVar( "paused", ::nBase::cVariant::MakeVariant( false ) );

    mCurrentSpriteRect = sf::IntRect( 0, 0, iW, iH );

    if( iFile != "empty" )
        SetSpriteSheet( iFile, iW, iH );
}


// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------- Copy
// -------------------------------------------------------------------------------------


cComponent*
cSpriteAnimated::Clone()
{
    return  new cSpriteAnimated( *this );
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------ Access
// -------------------------------------------------------------------------------------


const std::string&
cSpriteAnimated::FileName()
{
    return  GetVar( "filename" )->GetValueString();
}


double
cSpriteAnimated::Framerate()
{
    return  GetVar( "framerate" )->GetValueNumber();
}


bool
cSpriteAnimated::Paused()
{
    return  GetVar( "paused" )->GetValueBool();
}


void
cSpriteAnimated::FileName( const std::string & iValue )
{
    GetVar( "filename" )->SetValueString( iValue );
}


void
cSpriteAnimated::Framerate( double iValue )
{
    GetVar( "framerate" )->SetValueNumber( iValue );
}


void
cSpriteAnimated::Paused( bool iValue )
{
    GetVar( "framerate" )->SetValueBool( iValue );
}


// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------- Handle functions
// -------------------------------------------------------------------------------------


void
cSpriteAnimated::NextFrame()
{
    mCurrentSpriteRect.left = (mCurrentSpriteRect.left + mCurrentSpriteRect.width ) % mSpriteSheet->getSize().x;
    mSprite.setTextureRect( mCurrentSpriteRect );
}


void
cSpriteAnimated::PreviousFrame()
{
    mCurrentSpriteRect.left -= mCurrentSpriteRect.width;
    if( mCurrentSpriteRect.left < 0 )
        mCurrentSpriteRect.left = mSpriteSheet->getSize().x - mCurrentSpriteRect.width;

    mSprite.setTextureRect( mCurrentSpriteRect );
}


void
cSpriteAnimated::Flip()
{
    mSprite.setScale( sf::Vector2f( -1.0F, 1.0F ) );
}


void
cSpriteAnimated::Unflip()
{
    mSprite.setScale( sf::Vector2f( 1.0F, 1.0F ) );
}


void
cSpriteAnimated::SetSpriteSheet( const std::string & iFile, int iW, int iH )
{
    mSpriteSheet = ::nBase::cResourceManager::Instance()->GetTexture( iFile );
    mSprite.setTexture( *mSpriteSheet );
    mSprite.setTextureRect( mCurrentSpriteRect );
    mSprite.setOrigin( sf::Vector2f( float( iW / 2 ), float( iH / 2 ) ) );
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------ Input/Output
// -------------------------------------------------------------------------------------


void
cSpriteAnimated::SaveXML( tinyxml2::XMLElement* iNode, tinyxml2::XMLDocument* iDocument )
{
    tSuperClass::SaveXML( iNode, iDocument );
    iNode->SetAttribute( "width", mCurrentSpriteRect.width );
    iNode->SetAttribute( "height", mCurrentSpriteRect.height );
}


void
cSpriteAnimated::LoadXML( tinyxml2::XMLElement* iNode )
{
    tSuperClass::LoadXML( iNode );
    int width = iNode->IntAttribute( "width", 0 );
    int height = iNode->IntAttribute( "height", 0 );

    mCurrentSpriteRect.width = width;
    mCurrentSpriteRect.height = height;

    SetSpriteSheet( FileName(), width, height );
}


} // namespace nECS

