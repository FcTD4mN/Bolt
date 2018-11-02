#include "Core.ECS.Component.Sound.h"


#include "Core.Sound.FX.h"


namespace nCore {
namespace nECS {
namespace nComponent {


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------ Construction/Destruction
// -------------------------------------------------------------------------------------


cSound::~cSound()
{
}


cSound::cSound() :
    tSuperClass( "sound" )
{
    Build( "" );
}


cSound::cSound( const std::string& iFileName ) :
    tSuperClass( "sound" )
{
    Build( iFileName );
}


cSound::cSound( const cSound & iRHS ) :
    tSuperClass( iRHS )
{
}


void
cSound::Build( const std::string & iFile )
{
    AddNewVariable( "filename", ::nCore::nBase::cVariant::MakeVariant( iFile ) );
    SetSoundFromFile( iFile );

    AddNewVariable( "volume", ::nCore::nBase::cVariant::MakeVariant( 100.0 ) );
    AddNewVariable( "attenuation", ::nCore::nBase::cVariant::MakeVariant( 1.0 ) );
    AddNewVariable( "loop", ::nCore::nBase::cVariant::MakeVariant( false ) );
    AddNewVariable( "positionX", ::nCore::nBase::cVariant::MakeVariant( 0.0 ) );
    AddNewVariable( "positionY", ::nCore::nBase::cVariant::MakeVariant( 0.0 ) );
    AddNewVariable( "positionZ", ::nCore::nBase::cVariant::MakeVariant( 0.0 ) );

    mCurrentSound = 0;
    mLastOcclusion = 1.0;
}


// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------- Copy
// -------------------------------------------------------------------------------------


::nCore::nECS::nCore::cComponent*
cSound::Clone() const
{
    return  new cSound(*this);
}


void
cSound::Play()
{
    mSound[ mCurrentSound ].play();
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------ Access / Set
// -------------------------------------------------------------------------------------


const std::string &
cSound::FileName()
{
    return  GetVar( "filename" )->GetValueString();
}


void
cSound::SetSoundFromFile( const std::string & iFileName )
{
    if( iFileName != "" )
    {
        mDrySoundBuffer.loadFromFile( iFileName );
        mSound[ 0 ].setBuffer( mDrySoundBuffer );
        mSound[ 1].setBuffer( mDrySoundBuffer );
    }
}


double
cSound::Volume()
{
    return  GetVar( "volume" )->GetValueNumber();
}


void
cSound::Volume( double iVolume )
{
    GetVar( "volume" )->SetValueNumber( iVolume );
    mSound[ 0 ].setVolume( float(iVolume) );
    mSound[ 1 ].setVolume( float(iVolume) );
}


double
cSound::Attenuation()
{
    return  GetVar( "attenuation" )->GetValueNumber();
}


void
cSound::Attenuation( double iAttenuation )
{
    GetVar( "attenuation" )->SetValueNumber( iAttenuation );
    mSound[ 0 ].setAttenuation( float(iAttenuation) );
    mSound[ 1 ].setAttenuation( float(iAttenuation) );
}


bool
cSound::Loop()
{
    return  GetVar( "loop" )->GetValueBool();
}


void cSound::Loop( bool iLoop )
{
    GetVar( "loop" )->SetValueBool( iLoop );
    mSound[ 0 ].setLoop( iLoop );
    mSound[ 1 ].setLoop( iLoop );
}


sf::Vector3f
cSound::Position()
{
    double x = GetVar( "positionX" )->GetValueNumber();
    double y = GetVar( "positionY" )->GetValueNumber();
    double z = GetVar( "positionZ" )->GetValueNumber();
    return  sf::Vector3f( float(x), float(y), float(z) );
}


void
cSound::Position( const sf::Vector3f & iPosition )
{
    GetVar( "positionX" )->SetValueNumber( iPosition.x );
    GetVar( "positionY" )->SetValueNumber( iPosition.y );
    GetVar( "positionZ" )->SetValueNumber( iPosition.z );
    mSound[ 0 ].setPosition( iPosition );
    mSound[ 1 ].setPosition( iPosition );
}


double
cSound::X()
{
   return  GetVar( "positionX" )->GetValueNumber();
}


double
cSound::Y()
{
    return  GetVar( "positionY" )->GetValueNumber();
}


double
cSound::Z()
{
    return  GetVar( "positionZ" )->GetValueNumber();
}


void
cSound::X( double iValue )
{
    GetVar( "positionX" )->SetValueNumber( iValue );
}


void
cSound::Y( double iValue )
{
    GetVar( "positionY" )->SetValueNumber( iValue );
}


void
cSound::Z( double iValue )
{
    GetVar( "positionZ" )->SetValueNumber( iValue );
}


sf::Sound&
cSound::CurrentSound()
{
    return  mSound[ mCurrentSound ];
}


sf::Sound&
cSound::SwaperSound()
{
    int nextSound = ( mCurrentSound + 1 ) % 2;
    return  mSound[ nextSound ];
}


void
cSound::SetSoundOcclusionFactor( double iOcclusionFactor )
{
    if( iOcclusionFactor != mLastOcclusion )
    {
        int nextSound = ( mCurrentSound + 1 ) % 2;
        mWetSoundBuffer[ nextSound ] = ::nCore::nSound::LowPassFilter( mDrySoundBuffer, 1 - iOcclusionFactor );
        ApplySwapBuffer();
        mLastOcclusion = iOcclusionFactor;
    }
}


void
cSound::ApplySwapBuffer()
{
    // SoundMixer system will then do the swap
    mNeedSwap = true;
    int nextSound = ( mCurrentSound + 1 ) % 2;
    mSound[ nextSound ].setVolume( 0.0F );
    mSound[ nextSound ].setBuffer( mWetSoundBuffer[ nextSound ] );
    mSound[ nextSound ].setPlayingOffset( mSound[ mCurrentSound ].getPlayingOffset() );
    mSound[ nextSound ].play();
    mCurrentSound = nextSound;
}


} // namespace nComponent
} // namespace nECS
} // namespace nCore

