#pragma once

#include "Core.ECS.Core.Component.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <tinyxml2.h>


namespace nECS {


class cSound :
    public cComponentGeneric
{
public:
    typedef  cComponentGeneric  tSuperClass;

public:
    virtual  ~cSound();
    cSound();
    cSound( const std::string& iFileName );
    cSound( const cSound& iRHS );

private:
    void Build( const std::string& iFile );

public:
    // Copy
    virtual  cComponent* Clone() override;

public:
    // Access / Set
    const std::string&  FileName();
    void SetSoundFromFile( const std::string& iFileName );
    sf::Sound& Sound();

private:
    sf::Sound       mSound;
    sf::SoundBuffer mSoundBuffer;
};


} // namespace nECS

