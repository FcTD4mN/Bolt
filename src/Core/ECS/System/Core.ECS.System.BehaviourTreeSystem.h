#pragma once

#include "Core.ECS.Core.System.h"

#include <SFML/Graphics.hpp>


namespace nECS {


class cBehaviourTreeSystem :
    public cSystem
{
public:
    typedef  cSystem  tSuperClass;

public:
    virtual  ~cBehaviourTreeSystem();
    cBehaviourTreeSystem();


    // Overrides
public:
    // Init/Finalize
    virtual  void  Initialize() override;
    virtual  void  Finalize() override;

public:
    // Update/Draw
    virtual  void  Update( unsigned int iDeltaTime ) override;

public:
    // Entity
    virtual  void  IncomingEntity( cEntity* iEntity ) override;

};


} // namespace ECS

