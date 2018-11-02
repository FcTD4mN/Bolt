#pragma once

#include "Core.ECS.Core.Component.h"

#include <SFML/Graphics.hpp>
#include <tinyxml2.h>

#include "Core.Base.FileSystem.h"


namespace nCore::nAnimation { class cAnimation; }

namespace nCore {
namespace nECS {
namespace nComponent {



class cAnimations :
    public ::nCore::nECS::nCore::cComponent
{
public:
    typedef  cComponent  tSuperClass;

public:
    virtual  ~cAnimations();
    cAnimations();
    cAnimations( const cAnimations& iRHS );

public:
    // Copy
    virtual  ::nCore::nECS::nCore::cComponent* Clone() const override;

public:
    // Update/Draw
    void  Update( unsigned int iDeltaTime );
    void  Draw( sf::RenderTarget* iRenderTarget );

public:
    // Animation list management
        // We return  the animation so edition is possible in c++ context
    ::nCore::nAnimation::cAnimation*     AddSpriteSheetBasedAnimation( const std::string& iAnimationName, const nStdFileSystem::path& iFullFilePath, int iNumberOfImages );
    ::nCore::nAnimation::cAnimation*     AddMultiFilesBasedAnimation( const std::string& iAnimationName );

    // Set/Gets
    void            CurrentAnimation( const std::string& iAnimationName );
    std::string     CurrentAnimation() const;

    void  CurrentAnimationCurrentFrame( int iCurrentFrame );
    int   CurrentAnimationCurrentFrame() const;

    void  CurrentAnimationFrameRate( float iFrameRate );
    float CurrentAnimationFrameRate() const;

    void  CurrentAnimationNextFrame();
    void  CurrentAnimationPrevFrame();

    int   CurrentAnimationSpriteWidth() const;
    int   CurrentAnimationSpriteHeight() const;

    void  CurrentAnimationSpritePosition( const sf::Vector2f& iPosition );
    void  CurrentAnimationSpriteOrigin( const sf::Vector2f& iOrigin );
    void  CurrentAnimationSpriteScale( const sf::Vector2f& iScale );

    void  CurrentAnimationIsFlipped( bool iFlipped );
    bool  CurrentAnimationIsFlipped() const;

    void  CurrentAnimationIsPaused( bool iPaused );
    bool  CurrentAnimationIsPaused() const;

    void  CurrentAnimationPlay();

public:
    // Input/Output
    virtual  void SaveXML( tinyxml2::XMLElement* iNode, tinyxml2::XMLDocument* iDocument ) const override;
    virtual  void LoadXML( tinyxml2::XMLElement* iNode ) override;

private:
    ::nCore::nAnimation::cAnimation*    _AnimationByName( const std::string& iName );

public:
    // EDITOR
    void                                SetAnimationNameAtIndex( const std::string& iName, int iIndex );
    int                                 AnimationCount() const;
    ::nCore::nAnimation::cAnimation*    AnimationAtIndex( int iIndex );
    ::nCore::nAnimation::cAnimation*    AddEmptyAnimationAtIndex( const std::string& iAnimationName, int iIndex );
    void                                RemoveAnimationAtIndex( int iIndex );



private:
    // This could be a vector storing a struct pair like components in entity if we wanna optimize
    std::vector< ::nCore::nAnimation::cAnimation* > mAnimations;
    ::nCore::nAnimation::cAnimation*                mCurrentAnimation; // We could store the name, ease the GetCurrentAnimation method, but then we must do an access every time mAnimations[ mCurrent ]
};


} // namespace nComponent
} // namespace nECS
} // namespace nCore


