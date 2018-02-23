#include "SpriteAnimated.h"

#include "Base/ResourceManager.h"

// -------------------------------------------------------------------------------------
// ------------------------------------------------------------ Construction/Destruction
// -------------------------------------------------------------------------------------


cSpriteAnimated::~cSpriteAnimated()
{
}


cSpriteAnimated::cSpriteAnimated( const std::string& iFile, int iW, int iH ) :
    tSuperClass( "spriteanimated" ),
    mFileName( iFile ),
    mCurrentSpriteRect( 0, 0, iW, iH ),
    mSpriteSheet( 0 ),
    mFrameRate( 24.0F )
{
    mSpriteSheet = cResourceManager::Instance()->GetTexture( mFileName );
    mSprite.setTexture( *mSpriteSheet );
    mSprite.setTextureRect( mCurrentSpriteRect );
    mSprite.setOrigin( sf::Vector2f( float(iW/2), float(iH/2) ) );
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
cSpriteAnimated::LoadXML( const tinyxml2::XMLElement* iNode )
{
    tSuperClass::LoadXML( iNode );
    mFileName = iNode->Attribute( "file", "unknown" );
    float width = iNode->FloatAttribute( "width", 0.0F );
    float height = iNode->FloatAttribute( "height", 0.0F );
    mFrameRate = iNode->FloatAttribute( "framerate", 24.0F );
    mPaused = iNode->BoolAttribute( "paused", false );

    mSpriteSheet = cResourceManager::Instance()->GetTexture( mFileName );
    mCurrentSpriteRect.width = width;
    mCurrentSpriteRect.height = height;

    mSprite.setTexture( *mSpriteSheet );
    mSprite.setTextureRect( mCurrentSpriteRect );
    mSprite.setOrigin( sf::Vector2f( float( width / 2 ), float( height / 2 ) ) );
}

