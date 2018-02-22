#include "SpriteAnimated.h"


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------ Construction/Destruction
// -------------------------------------------------------------------------------------


cSpriteAnimated::~cSpriteAnimated()
{
}


cSpriteAnimated::cSpriteAnimated( const std::string& iFile, int iW, int iH ) :
    tSuperClass( "spriteanimated" ),
    mCurrentSpriteRect( 0, 0, iW, iH ),
    mFrameRate( 24.0F )
{
    mSpriteSheet.loadFromFile( iFile );
    mSprite.setTexture( mSpriteSheet );
    mSprite.setTextureRect( mCurrentSpriteRect );
    mSprite.setOrigin( sf::Vector2f( iW/2, iH/2 ) );
}


// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------- Handle functions
// -------------------------------------------------------------------------------------


void
cSpriteAnimated::NextFrame()
{
    mCurrentSpriteRect.left = (mCurrentSpriteRect.left + mCurrentSpriteRect.width) % mSpriteSheet.getSize().x;
    mSprite.setTextureRect( mCurrentSpriteRect );
}


void
cSpriteAnimated::PreviousFrame()
{
    mCurrentSpriteRect.left -= mCurrentSpriteRect.width;
    if( mCurrentSpriteRect.left < 0 )
        mCurrentSpriteRect.left = mSpriteSheet.getSize().x - mCurrentSpriteRect.width;

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

