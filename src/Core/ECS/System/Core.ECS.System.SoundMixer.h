#pragma once

#include "Core.ECS.Core.System.h"

#include "Core.Mapping.PhysicEntityGrid.h"


#include <SFML/Graphics.hpp>


namespace nECS {

class cEntity;

class cSoundMixer :
    public cSystem
{
public:
    typedef  cSystem  tSuperClass;

public:
    virtual  ~cSoundMixer();
    cSoundMixer();


    // Overrides
public:
    // Update/Draw
    virtual  void  Update( unsigned int iDeltaTime ) override;

public:
    // Entity
    virtual  void  IncomingEntity( cEntity* iEntity ) override;
};


} // namespace nECS

