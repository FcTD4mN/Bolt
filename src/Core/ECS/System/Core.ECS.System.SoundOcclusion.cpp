 #include "Core.ECS.System.SoundOcclusion.h"

#include "Core.ECS.Core.Entity.h"
#include "Core.ECS.Core.World.h"

#include "Core.ECS.Component.Transformation.h"
#include "Core.ECS.Component.SimplePhysic.h"
#include "Core.ECS.Component.Sound.h"
#include "Core.ECS.Component.OcclusionFactor.h"

#include "Core.Render.Layer.h"
#include "Core.Math.Edge.h"
#include "Core.Math.Utils.h"


namespace nCore {
namespace nECS {
namespace nSystem {


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------ Construction/Destruction
// -------------------------------------------------------------------------------------


cSoundOcclusion::~cSoundOcclusion()
{
}


cSoundOcclusion::cSoundOcclusion() :
    tSuperClass( "SoundOcclusion" ),
    mListener( 0 )
{
}


cSoundOcclusion::cSoundOcclusion( const cSoundOcclusion & iSys ) :
    tSuperClass( iSys )
{
}


::nCore::nECS::nCore::cSystem*
cSoundOcclusion::Clone() const
{
    return  new cSoundOcclusion( *this );
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------- Update/Draw
// -------------------------------------------------------------------------------------


void
cSoundOcclusion::Update( unsigned int iDeltaTime )
{
    ::nCore::nMapping::cEntityGrid* entityMap = 0;
    bool applyOcclusion = false;

    for( int i = 0; i < mSoundEmitters.size(); ++i )
    {
        ::nCore::nECS::nCore::cEntity* entity = mSoundEmitters[ i ];

        if( entity == mListener )
            continue;

        auto layer = entity->Layer();
        if( layer )
            entityMap = layer->EntityGrid();
        else
            entityMap = mWorld->EntityMap();

        auto transformation = entity->GetComponentByNameAs< ::nCore::nECS::nComponent::cTransformation* >( "transformation" );
        auto sound = entity->GetComponentByNameAs< ::nCore::nECS::nComponent::cSound* >( "sound" );

        double finalOcclusion = 1.0F;

        std::set< ::nCore::nECS::nCore::cEntity* >  entitiesInBetween;
        entityMap->GetEntitiesFollowingLineFromEntityToEntity( &entitiesInBetween, mListener, entity,::nCore::nMath::cEdgeF::MakePointPoint( transformation->PositionAsVector2F(), mListenerPosition->PositionAsVector2F() ) );
        for( auto ent : entitiesInBetween )
        {
            auto occlusionfactor = dynamic_cast< ::nCore::nECS::nComponent::cOcclusionFactor* >( ent->GetComponentByName( "occlusionfactor" ) );
            if( occlusionfactor )
            {
                finalOcclusion *= occlusionfactor->OcclusionFactor();
                applyOcclusion = !false;
            }
        }

        //if( applyOcclusion )
            sound->SetSoundOcclusionFactor( finalOcclusion );
    }
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------ Entity
// -------------------------------------------------------------------------------------


void
cSoundOcclusion::IncomingEntity( ::nCore::nECS::nCore::cEntity * iEntity )
{
    auto transformation = iEntity->GetComponentByNameAs< ::nCore::nECS::nComponent::cTransformation* >( "transformation" );
    auto simplephysic = iEntity->GetComponentByNameAs< ::nCore::nECS::nComponent::cSimplePhysic* >( "simplephysic" );
    auto occlusionfactor = iEntity->GetComponentByNameAs< ::nCore::nECS::nComponent::cOcclusionFactor* >( "occlusionfactor" );
    auto sound = iEntity->GetComponentByNameAs< ::nCore::nECS::nComponent::cSound* >( "sound" );

    if( transformation && simplephysic && ( occlusionfactor || sound ) )
    {
        AcceptEntity( iEntity );

        if( occlusionfactor )
            mSoundOccluser.push_back( iEntity );
        else if( sound )
            mSoundEmitters.push_back( iEntity );
        else
            printf( "On est pas bon la\n" );
    }

    if( transformation && simplephysic && iEntity->HasTag( "listener" ) )
    {
        mListener = iEntity;
        mListenerPosition = mListener->GetComponentByNameAs< ::nCore::nECS::nComponent::cTransformation* >( "transformation" );
    }
}


} // namespace nSystem
} // namespace nECS
} // namespace nCore

