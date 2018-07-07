#pragma once


#include "Core.ECS.Core.Component.h"


#include <SFML/Graphics.hpp>
#include <tinyxml2.h>


namespace nECS {


class cSpriteAnimated :
    public cComponentGeneric
{
public:
    typedef  cComponentGeneric  tSuperClass;

public:
    virtual  ~cSpriteAnimated();
    cSpriteAnimated();
    cSpriteAnimated( const std::string& iFile, int iW, int iH );
    cSpriteAnimated( const cSpriteAnimated& iSpriteAnimated );

private:
    void Build( const std::string& iFile, int iW, int iH );
    void BuildCallbacks();
    void UpdateTextureRect();

public:
    // Copy
    virtual  cComponent* Clone() override;

public:
    // Access
    const std::string& FileName();
    double Framerate();
    bool Paused();

    void FileName( const std::string& iValue );
    void Framerate( double iValue );
    void Paused( bool iValue );

public:
    // Handle functions
    void  NextFrame();
    void  PreviousFrame();
    bool  Flip();
    void  Flip( bool iFlip );

public:
    void SetSpriteSheet( const std::string& iFile );

public:
    // Input/Output
    virtual  void SaveXML( tinyxml2::XMLElement* iNode, tinyxml2::XMLDocument* iDocument ) override;
    virtual  void LoadXML( tinyxml2::XMLElement* iNode ) override;

public:
    sf::Texture*    mSpriteSheet;
    sf::Sprite      mSprite;
    sf::IntRect     mCurrentSpriteRect;
    sf::Clock       mClock;             // Animation clock

    int             mNumberOfSprites;

};


} // namespace nECS

