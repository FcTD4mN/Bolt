#pragma once


#include "Core.ECS.Core.System.h"


#include "Core.Mapping.EntityMap.h"


#include <SFML/Graphics.hpp>


namespace nCore { namespace nECS { namespace nCore { class cEntity; } } }
namespace nCore { namespace nECS { namespace nComponent { class cTransformation; } } }


namespace nCore {
namespace nECS {
namespace nSystem {


class cSoundOcclusion :
    public ::nCore::nECS::nCore::cSystem
{
public:
    typedef  cSystem  tSuperClass;

public:
    virtual  ~cSoundOcclusion();
    cSoundOcclusion();
    cSoundOcclusion( const cSoundOcclusion& iSys );

    // Overrides
public:
    virtual  cSystem* Clone() const override;

public:
    // Update/Draw
    virtual  void  Update( unsigned int iDeltaTime ) override;

public:
    // Entity
    virtual  void  IncomingEntity( ::nCore::nECS::nCore::cEntity* iEntity ) override;

private:
    ::nCore::nECS::nCore::cEntity*  mListener;
    ::nCore::nECS::nComponent::cTransformation*  mListenerPosition;
    std::vector< ::nCore::nECS::nCore::cEntity* >  mSoundEmitters;
    std::vector< ::nCore::nECS::nCore::cEntity* >  mSoundOccluser;
};


} // namespace nSystem
} // namespace nECS
} // namespace nCore

