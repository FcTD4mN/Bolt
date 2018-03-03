#pragma once

#include "ECS/Core/Component.h"

#include <SFML/Graphics.hpp>

#include "tinyxml2.h"

class cSpriteAnimated :
    public cComponent
{
public:
    typedef  cComponent  tSuperClass;

public:
    virtual  ~cSpriteAnimated();
    cSpriteAnimated();
    cSpriteAnimated( const std::string& iFile, int iW, int iH );
    cSpriteAnimated( const cSpriteAnimated& iSpriteAnimated );

public:
    // Copy
    virtual  cComponent* Clone();

public:
    // Handle functions
    void  NextFrame();
    void  PreviousFrame();
    void  Flip();
    void  Unflip();

public:
    void SetSpriteSheet( const std::string& iFile, int iW, int iH );

public:
    // Input/Output
    virtual  void SaveXML( tinyxml2::XMLElement* iNode, tinyxml2::XMLDocument* iDocument );
    virtual  void LoadXML( tinyxml2::XMLElement* iNode );

public:
    std::string     mFileName;

    sf::Texture*    mSpriteSheet;
    sf::Sprite      mSprite;
    sf::IntRect     mCurrentSpriteRect;
    float           mFrameRate;         // Animation's frame rate
    bool            mPaused;            // Is the animation paused ?
    sf::Clock       mClock;             // Animation clock
};
