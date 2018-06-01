 #include "Core.ECS.System.SoundMixer.h"

#include "Core.ECS.Core.Entity.h"

#include "Core.ECS.Component.Sound.h"

#include "Core.Math.Utils.h"


namespace nECS {


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------ Construction/Destruction
// -------------------------------------------------------------------------------------


cSoundMixer::~cSoundMixer()
{
}


cSoundMixer::cSoundMixer() :
    tSuperClass()
{
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------- Update/Draw
// -------------------------------------------------------------------------------------


void
cSoundMixer::Update( unsigned int iDeltaTime )
{
    for( int i = 0; i < mEntityGroup.size(); ++i )
    {
        cEntity* entity = mEntityGroup[ i ];

        auto    sound = dynamic_cast< cSound* >( entity->GetComponentByName( "sound" ) );

        if( sound->mNeedSwap )
        {
            double volume = sound->Volume();
            sound->CurrentSound().setVolume( volume );
            sound->SwaperSound().setVolume( 100.0 - volume );
            sound->mNeedSwap = false;
        }

        if( sound->FileName() == "resources/Shared/Audio/SineWave.wav" )
        {
            auto lp = sf::Listener::getPosition();
            auto ep = sound->Position();

            auto delta = ep - lp;
            printf( "%f\n", ::nMath::Magnitude( delta ) );
        }
    }
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------ Entity
// -------------------------------------------------------------------------------------


void
cSoundMixer::IncomingEntity( cEntity * iEntity )
{
    auto sound = iEntity->GetComponentByName( "sound" );
    if( sound )
        AcceptEntity( iEntity );
}


} // namespace nECS

