#include "Core.ECS.Component.Sound.h"


#include "Core.Sound.FX.h"

namespace nECS {


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
    AddNewVariable( "filename", ::nBase::cVariant::MakeVariant( iFile ) );
    SetSoundFromFile( iFile );
}


// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------- Copy
// -------------------------------------------------------------------------------------


cComponent*
cSound::Clone()
{
    return  new cSound(*this);
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
        mSoundBuffer.loadFromFile( iFileName );
        //mSoundBuffer = ::nSound::Reverb( mSoundBuffer, 100 );
        mSoundBuffer = ::nSound::LowPassFilter( mSoundBuffer, 0.99 );

        mSound.setBuffer( mSoundBuffer );
    }
}


sf::Sound&
cSound::Sound()
{
    return  mSound;
}


} // namespace nECS

