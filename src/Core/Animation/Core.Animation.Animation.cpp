#include "Core.Animation.Animation.h"

#include "Core.Base.ResourceManager.h"
#include "Core.Base.FileSystem.h"

namespace nCore {
namespace nAnimation {


cAnimation::~cAnimation()
{
    ClearAllImages();
}


cAnimation::cAnimation( const std::string& iName ) :
    mName( iName ),
    mCurrentFrame( 0 ),
    mNumberOfImages( 0 ),
    mFrameRate( 24 ),
    mPaused( false ),
    mFlipped( false ),
    mIsAnimationLooping( true ),
    mTime( 0 )
{
}


cAnimation::cAnimation( const cAnimation& iRHS ) :
    mCurrentFrame( iRHS.mCurrentFrame ),
    mNumberOfImages( 0 ), // This will be built when calling AddImage / AddSpriteSheet below
    mFrameRate( iRHS.mFrameRate ),
    mPaused( iRHS.mPaused ),
    mFlipped( iRHS.mFlipped ),
    mIsAnimationLooping( iRHS.mIsAnimationLooping ),
    mTime( 0 )
{
    for( auto& data : iRHS.mSprites )
        AddImage( data.mFile );
}


cAnimation*
cAnimation::Clone() const
{
    return  new  cAnimation( *this );
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------- Update/Draw
// -------------------------------------------------------------------------------------


void
cAnimation::Update( unsigned int iDeltaTime )
{
    if( Paused() )
        return;

    mTime += iDeltaTime;

    // We have 1 frame per second -> 1 per 1E6 microseconds
    // So we keep track of the delta time climbing up, and then we get how many times we need to next
    // Most of the time, it's gonna be 1, but if there is lag spike, it might be more
    // This encures that the animation keeps being synced up with the clock
    unsigned int howManyNextFrame = mTime / int( 1E6 / mFrameRate );
    mTime = mTime % (int( 1E6 /mFrameRate));

    while( howManyNextFrame > 0 )
    {
        NextFrame();

        // If we did a NextFrame that ends on the 0 frame, it means we just played the last frame and ended a cycle of animation
        if( mCurrentFrame == 0 )
        {
            if( !mIsAnimationLooping )
                Paused( true );

            if( mEndOfAnimationCB )
                mEndOfAnimationCB();
        }
        --howManyNextFrame;
    }
}


void
cAnimation::Draw( sf::RenderTarget * iRenderTarget )
{
    iRenderTarget->draw( *mSprites[ mCurrentFrame ].mSprite );
}


// -------------------------------------------------------------------------------------
// --------------------------------------------------------------------- Control methods
// -------------------------------------------------------------------------------------


void
cAnimation::NextFrame()
{
    mCurrentFrame = ++mCurrentFrame % mNumberOfImages;
}


void
cAnimation::PreviousFrame()
{
    mCurrentFrame = --mCurrentFrame;
    if( mCurrentFrame < 0 )
        mCurrentFrame = mNumberOfImages - 1;
}


void
cAnimation::Play()
{
    Paused( false );
}


// -------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------- Set/Get
// -------------------------------------------------------------------------------------


void
cAnimation::Name( const std::string & iName )
{
    mName = iName;
}


const std::string&
cAnimation::Name() const
{
    return  mName;
}


void
cAnimation::CurrentFrame( int iCurrentFrame )
{
    mCurrentFrame = iCurrentFrame;
}


int
cAnimation::CurrentFrame() const
{
    return  mCurrentFrame;
}


void
cAnimation::FrameRate( float iFrameRate )
{
    mFrameRate = iFrameRate;
}


float
cAnimation::FrameRate() const
{
    return  mFrameRate;
}


void
cAnimation::Paused( bool iPaused )
{
    mPaused = iPaused;
}


bool
cAnimation::Paused() const
{
    return  mPaused;
}


void
cAnimation::Flipped( bool iFlipped )
{
    if( mFlipped == iFlipped )
        return;

    mFlipped = iFlipped;

    for( auto& sprite : mSprites )
    {
        sf::IntRect spritesRect = sprite.mSprite->getTextureRect();

        spritesRect.left += spritesRect.width;
        spritesRect.width *= -1;
        sprite.mSprite->setTextureRect( spritesRect );
    }
}


bool
cAnimation::Flipped() const
{
    return  mFlipped;
}


void
cAnimation::IsAnimationLooping( bool iIsAnimationLooping )
{
    mIsAnimationLooping = iIsAnimationLooping;
}


bool
cAnimation::IsAnimationLooping() const
{
    return  mIsAnimationLooping;
}


int
cAnimation::SpriteWidth() const
{
    int width =  mSprites[ mCurrentFrame ].mSprite->getTextureRect().width;

    // We don't wanna send a -40 width here, so we need to cancel the minus due to the flip
    // This function returns the actual width, being a positive value.
    if( mFlipped )
        width *= -1;

    return  width;
}


int
cAnimation::SpriteHeight() const
{
    return  mSprites[ mCurrentFrame ].mSprite->getTextureRect().height;
}


void
cAnimation::SpritePosition( const sf::Vector2f & iPosition )
{
    mSprites[ mCurrentFrame ].mSprite->setPosition( iPosition );
}


void
cAnimation::SpriteOrigin( const sf::Vector2f & iOrigin )
{
    mSprites[ mCurrentFrame ].mSprite->setOrigin( iOrigin );
}


void
cAnimation::SpriteScale( const sf::Vector2f & iScale )
{
    mSprites[ mCurrentFrame ].mSprite->setScale( iScale );
}


void
cAnimation::EndOfAnimationCB( std::function<void()> iCB )
{
    mEndOfAnimationCB = iCB;
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------- Images management
// -------------------------------------------------------------------------------------


void
cAnimation::AddImage( const nStdFileSystem::path & iFullFile )
{
    sf::Sprite* newSprite = new sf::Sprite();

    if( nStdFileSystem::exists( iFullFile ) )
        newSprite->setTexture( *::nCore::nBase::cResourceManager::Instance()->GetTexture( iFullFile ) );

    ++mNumberOfImages;

    sData data;
    data.mSprite = newSprite;
    data.mFile = iFullFile;
    mSprites.push_back( data );
}


void
cAnimation::AddSpriteSheet( const nStdFileSystem::path & iFullFile, int iNumberOfImages )
{
    if( !nStdFileSystem::exists( iFullFile ) )
        return;

    sf::Sprite  renderSprite;
    sf::Texture* sheet = ::nCore::nBase::cResourceManager::Instance()->GetTexture( iFullFile );
    renderSprite.setTexture( *sheet );

    sf::Vector2i oneSpriteSize;
    oneSpriteSize.x = sheet->getSize().x / iNumberOfImages;
    oneSpriteSize.y = sheet->getSize().y;

    sf::Sprite* newSprite = 0;

    sf::IntRect sheetRect;
    sheetRect.top = 0;
    sheetRect.width = oneSpriteSize.x;
    sheetRect.height = oneSpriteSize.y;

    for( int i = 0; i < iNumberOfImages; ++i )
    {
        // We check if subfiles for the sprite sheet already exists or not, if they do, no need to rerender it
        nStdFileSystem::path newSubFile =   iFullFile.parent_path().string() + "/" +
                                            iFullFile.stem().string() + "_" + std::to_string( i ) +
                                            iFullFile.extension().string();

        // If not, we render each frame of the sheet into a separate image, and load them as any other image
        if( !nStdFileSystem::exists( newSubFile ) )
        {
            // Set texture on the renderSprite
            sheetRect.left = i * oneSpriteSize.x;
            renderSprite.setTextureRect( sheetRect );

            // Create a render texture to print the sprite on
            sf::RenderTexture* renderTexture = new sf::RenderTexture();
            renderTexture->create( sheetRect.width, sheetRect.height );

            // Draw on the renderTexture
            renderTexture->clear( sf::Color::Transparent );
            renderTexture->draw( renderSprite );
            renderTexture->display();

            auto splitTexture = renderTexture->getTexture();
            sf::Image textureImage = splitTexture.copyToImage();
            textureImage.saveToFile( newSubFile.string() );
        }

        AddImage( newSubFile );
    }
}


void
cAnimation::ChangeImageAtIndex( int iIndex, const nStdFileSystem::path & iFullFile )
{
    mSprites[ iIndex ].mSprite->setTexture( *::nCore::nBase::cResourceManager::Instance()->GetTexture( iFullFile ) );
    mSprites[ iIndex ].mFile = iFullFile;
}


void
cAnimation::RemoveImageByIndex( int iIndex )
{
    delete  mSprites[ iIndex ].mSprite;
    mSprites.erase( mSprites.begin() + iIndex );
    --mNumberOfImages;
}


void
cAnimation::SwapImagesAtIndexes( int iIndexA, int iIndexB )
{
    auto tmp = mSprites[ iIndexA ];
    mSprites[ iIndexA ] = mSprites[ iIndexB ];
    mSprites[ iIndexB ] = tmp;
}


void
cAnimation::ClearAllImages()
{
    for( auto& sprite : mSprites )
        delete  sprite.mSprite;

    mSprites.clear();
}


void
cAnimation::SaveXML( tinyxml2::XMLElement* iNode, tinyxml2::XMLDocument* iDocument ) const
{
    tinyxml2::XMLElement* spritesNode = iDocument->NewElement( "sprites" );
    for( auto& sprite : mSprites )
    {
        tinyxml2::XMLElement* spriteNode = iDocument->NewElement( "sprite" );
        spriteNode->SetAttribute( "fileName", sprite.mFile.string().c_str() );
        spritesNode->LinkEndChild( spriteNode );
    }

    iNode->LinkEndChild( spritesNode );
}


void
cAnimation::LoadXML( tinyxml2::XMLElement* iNode )
{
    ClearAllImages();
    tinyxml2::XMLElement* spritesNode = iNode->FirstChildElement( "sprites" );
    for( tinyxml2::XMLElement* sprite = spritesNode->FirstChildElement( "sprite" ); sprite; sprite = sprite->NextSiblingElement() )
    {
        std::string fileName = sprite->Attribute( "fileName" );
        AddImage( fileName );
    }
}

// =================================
// =============EDITOR==============
// =================================


int
cAnimation::SpriteCount() const
{
    return  int(mSprites.size());
}


sf::Sprite*
cAnimation::SpriteAtIndex( int iIndex )
{
    return  mSprites[ iIndex ].mSprite;
}


const::nStdFileSystem::path&
cAnimation::SpriteFileAtIndex( int iIndex )
{
    return  mSprites[ iIndex ].mFile;
}



} // namespace nBase
} // namespace nCore
