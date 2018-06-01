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
    // Handling
    void  Play();

public:
    // Access / Set
    const std::string&  FileName();
    void SetSoundFromFile( const std::string& iFileName );

    double  Volume();
    void    Volume( double iVolume );

    double  Attenuation();
    void    Attenuation( double iAttenuation );

    bool  Loop();
    void  Loop( bool iLoop );

    sf::Vector3f    Position();
    void            Position( const sf::Vector3f& iPosition );

    double  X();
    double  Y();
    double  Z();

    void  X( double iValue );
    void  Y( double iValue );
    void  Z( double iValue );

    // ==========================

    sf::Sound&  CurrentSound();
    sf::Sound&  SwaperSound(); // No idea for a name

    void  SetSoundOcclusionFactor( double iOcclusionFactor );
    void  ApplySwapBuffer();

    int64_t    FadeTimer();
    void       FadeTimer( int64_t iValue );

private:
    sf::Sound       mSound[ 2 ];
    sf::SoundBuffer mDrySoundBuffer;
    sf::SoundBuffer mWetSoundBuffer[ 2 ];

public:
    int             mCurrentSound;
    bool            mNeedSwap;
    double          mFadeDestinationVolume;
    double          mLastOcclusion;
};


} // namespace nECS

