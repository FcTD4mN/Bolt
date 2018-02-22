#pragma once

#include "ECS/Component.h"

#include <SFML/Graphics.hpp>

class cSpriteAnimated :
    public cComponent
{
public:
    typedef  cComponent  tSuperClass;

public:
    virtual  ~cSpriteAnimated();
    cSpriteAnimated( const std::string& iFile, int iW, int iH );

public:
    // Handle functions
    void  NextFrame();
    void  PreviousFrame();

public:
    sf::Texture mSpriteSheet;
    sf::Sprite  mSprite;
    sf::IntRect mCurrentSpriteRect;
    float       mFrameRate;
    int         mSpriteCount; // How many sprites are drawn on the sprite sheet ?
};
