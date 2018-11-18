#pragma once


#include <SFML/Graphics.hpp>

#include "Core.Base.FileSystem.h"

#include <tinyxml2.h>
#include <functional>

namespace nCore {
namespace nAnimation {


class cAnimation
{
public:
    ~cAnimation();
    cAnimation( const std::string& iName );
    cAnimation( const cAnimation & iRHS );

public:
    cAnimation*  Clone() const;

public:
    // Update/Draw
    virtual  void Update( unsigned int iDeltaTime );
    virtual  void Draw( sf::RenderTarget* iRenderTarget );

public:
    // Control methods
    virtual  void  NextFrame();
    virtual  void  PreviousFrame();

    virtual  void  Play(); // Like setting pause to false, but it's clearer to use

public:
    // Set/Gets
    void                Name( const std::string& iName );
    const std::string&  Name() const;

    void    CurrentFrame( int iCurrentFrame );
    int     CurrentFrame() const;

    void    FrameRate( float iFrameRate );
    float   FrameRate() const;

    void    Paused( bool iPaused );
    bool    Paused() const;

    void    Flipped( bool iFlipped );
    bool    Flipped() const;

    void    IsAnimationLooping( bool iIsAnimationLooping );
    bool    IsAnimationLooping() const;

    int     SpriteWidth() const;
    int     SpriteHeight() const;

    void    SpritePosition( const sf::Vector2f& iPosition );
    void    SpriteOrigin( const sf::Vector2f& iOrigin );
    void    SpriteScale( const sf::Vector2f& iScale );

    void    EndOfAnimationCB( std::function< void() > iCB );

public:
    // Images management
    void  AddImage( const nStdFileSystem::path& iFullFile );
    void  AddSpriteSheet( const nStdFileSystem::path& iFullFile, int iNumberOfImagesX, int iNumberOfImagesY );
    void  ChangeImageAtIndex( int iIndex, const nStdFileSystem::path& iFullFile );
    void  RemoveImageByIndex( int iIndex );
    void  SwapImagesAtIndexes( int iIndexA, int iIndexB );
    void  ClearAllImages();

public:
    // Input/Output
    virtual  void SaveXML( tinyxml2::XMLElement* iNode, tinyxml2::XMLDocument* iDocument ) const;
    virtual  void LoadXML( tinyxml2::XMLElement* iNode );

    // =========================================================
public:
    // EDITOR
    int                             SpriteCount() const;
    sf::Sprite*                     SpriteAtIndex( int iIndex );
    const ::nStdFileSystem::path&   SpriteFileAtIndex( int iIndex );
    // =========================================================



    // Members
private:
    std::string                 mName;

    int                         mCurrentFrame;
    int                         mNumberOfImages;
    float                       mFrameRate;
    bool                        mPaused;
    bool                        mFlipped;
    bool                        mIsAnimationLooping;

    unsigned int                mTime;

    // The callback for when the animation is over
    std::function< void() >     mEndOfAnimationCB;

    // Data, being a sprite and its file. Used to do the association between the two, so we can handle loading new files for a given frame
    // Also, we can handle saving images into their corresponding files
    struct sData
    {
        sf::Sprite*             mSprite;
        nStdFileSystem::path    mFile;
    };

    std::vector< sData >        mSprites;

};


} // namespace nBase
} // namespace nCore

