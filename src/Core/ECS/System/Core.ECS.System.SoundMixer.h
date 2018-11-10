#pragma once


#include "Core.ECS.Core.System.h"
#include "Core.Mapping.EntityMap.h"


#include <SFML/Graphics.hpp>


namespace nCore { namespace nECS { namespace nCore { class cEntity; } } }


namespace nCore {
namespace nECS {
namespace nSystem {


class cSoundMixer :
    public ::nCore::nECS::nCore::cSystem
{
public:
    typedef  cSystem  tSuperClass;

public:
    virtual  ~cSoundMixer();
    cSoundMixer();
    cSoundMixer( const cSoundMixer& iSys );

    // Overrides
public:
    virtual  cSystem* Clone() const override;

public:
    // Update/Draw
    virtual  void  Update( unsigned int iDeltaTime ) override;

public:
    // Entity
    virtual  void  IncomingEntity( ::nCore::nECS::nCore::cEntity* iEntity ) override;
};


} // namespace nSystem
} // namespace nECS
} // namespace nCore

