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

    void Build( const std::string& iFile, int iW, int iH );

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
    void  Flip();
    void  Unflip();

public:
    void SetSpriteSheet( const std::string& iFile, int iW, int iH );

public:
    // Input/Output
    virtual  void SaveXML( tinyxml2::XMLElement* iNode, tinyxml2::XMLDocument* iDocument );
    virtual  void LoadXML( tinyxml2::XMLElement* iNode );

public:
    sf::Texture*    mSpriteSheet;
    sf::Sprite      mSprite;
    sf::IntRect     mCurrentSpriteRect;
    sf::Clock       mClock;             // Animation clock

};


} // namespace nECS

