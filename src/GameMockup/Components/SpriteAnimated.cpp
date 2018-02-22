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
}


// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------- Handle functions
// -------------------------------------------------------------------------------------


void
cSpriteAnimated::NextFrame()
{
    mCurrentSpriteRect.left += mCurrentSpriteRect.width % mSpriteSheet.getSize().x;
}


void
cSpriteAnimated::PreviousFrame()
{
    mCurrentSpriteRect.left -= mCurrentSpriteRect.width;
    if( mCurrentSpriteRect.left < 0 )
        mCurrentSpriteRect.left = mSpriteSheet.getSize().x - mCurrentSpriteRect.width;
}

