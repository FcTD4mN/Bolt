#include "SpriteAnimated.h"

#include "Base/ResourceManager.h"

// -------------------------------------------------------------------------------------
// ------------------------------------------------------------ Construction/Destruction
// -------------------------------------------------------------------------------------


cSpriteAnimated::~cSpriteAnimated()
{
}


cSpriteAnimated::cSpriteAnimated() :
    tSuperClass( "spriteanimated" ),
    mFileName( "empty" ),
    mSpriteSheet( 0 ),
    mCurrentSpriteRect( 0, 0, 1, 1 ),
    mFrameRate( 24.0F )
{
}


cSpriteAnimated::cSpriteAnimated( const std::string& iFile, int iW, int iH ) :
    tSuperClass( "spriteanimated" ),
    mFileName( iFile ),
    mSpriteSheet( 0 ),
    mCurrentSpriteRect( 0, 0, iW, iH ),
    mFrameRate( 24.0F )
{
    SetSpriteSheet( iFile, iW, iH );
}


cSpriteAnimated::cSpriteAnimated( const cSpriteAnimated & iSpriteAnimated ) :
    tSuperClass( iSpriteAnimated ),
    mFileName( iSpriteAnimated.mFileName ),
    mSpriteSheet( iSpriteAnimated.mSpriteSheet ), // Copy pointer -> Same object, but this is what we want, we don't copy a same texture ( that's why we have a resource manager )
    mSprite( iSpriteAnimated.mSprite ),
    mCurrentSpriteRect( iSpriteAnimated.mCurrentSpriteRect ),
    mFrameRate( iSpriteAnimated.mFrameRate ),
    mPaused( iSpriteAnimated.mPaused ),
    mClock( iSpriteAnimated.mClock )
{
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
    mSpriteSheet = cResourceManager::Instance()->GetTexture( iFile );
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
    iNode->SetAttribute( "file", mFileName.c_str() );
    iNode->SetAttribute( "width", mCurrentSpriteRect.width );
    iNode->SetAttribute( "height", mCurrentSpriteRect.height );
    iNode->SetAttribute( "framerate", mFrameRate );
    iNode->SetAttribute( "paused", mPaused );
}


void
cSpriteAnimated::LoadXML( tinyxml2::XMLElement* iNode )
{
    tSuperClass::LoadXML( iNode );
    mFileName = iNode->Attribute( "file" );
    int width = iNode->IntAttribute( "width", 0 );
    int height = iNode->IntAttribute( "height", 0 );
    mFrameRate = iNode->FloatAttribute( "framerate", 24.0F );
    mPaused = iNode->BoolAttribute( "paused", false );

    mCurrentSpriteRect.width = width;
    mCurrentSpriteRect.height = height;

    SetSpriteSheet( mFileName, width, height );
}

