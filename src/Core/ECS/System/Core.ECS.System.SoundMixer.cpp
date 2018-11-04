 #include "Core.ECS.System.SoundMixer.h"


#include "Core.ECS.Core.Entity.h"
#include "Core.ECS.Component.Sound.h"
#include "Core.Math.Utils.h"


namespace nCore {
namespace nECS {
namespace nSystem {


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------ Construction/Destruction
// -------------------------------------------------------------------------------------


cSoundMixer::~cSoundMixer()
{
}


cSoundMixer::cSoundMixer() :
    tSuperClass( "SoundMixer" )
{
}


cSoundMixer::cSoundMixer( const cSoundMixer & iSys ) :
    tSuperClass( iSys )
{
}


::nCore::nECS::nCore::cSystem*
cSoundMixer::Clone() const
{
    return  new cSoundMixer( *this );
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------- Update/Draw
// -------------------------------------------------------------------------------------


void
cSoundMixer::Update( unsigned int iDeltaTime )
{
    for( int i = 0; i < mEntityGroup.size(); ++i )
    {
        ::nCore::nECS::nCore::cEntity* entity = mEntityGroup[ i ];

        auto sound = entity->GetComponentByIDAs< ::nCore::nECS::nComponent::cSound* >( "sound" );

        if( sound->mNeedSwap )
        {
            float volume = float(sound->Volume());
            sound->CurrentSound().setVolume( volume );
            sound->SwaperSound().setVolume( 100.0F - volume );
            sound->mNeedSwap = false;
        }

        if( sound->FileName() == "resources/Shared/Audio/SineWave.wav" )
        {
            auto lp = sf::Listener::getPosition();
            auto ep = sound->Position();

            auto delta = ep - lp;
            printf( "%f\n", ::nCore::nMath::Magnitude( delta ) );
        }
    }
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------ Entity
// -------------------------------------------------------------------------------------


void
cSoundMixer::IncomingEntity( ::nCore::nECS::nCore::cEntity * iEntity )
{
    auto sound = iEntity->GetComponentByID( "sound" );
    if( sound )
        AcceptEntity( iEntity );
}


} // namespace nSystem
} // namespace nECS
} // namespace nCore

