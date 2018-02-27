#pragma once

#include "ECS/System.h"

#include <SFML/Graphics.hpp>
#include "Mapping/PhysicEntityGrid.h"

class cSimplePhysics :
    public cSystem
{
public:
    typedef  cSystem  tSuperClass;

public:
    virtual  ~cSimplePhysics();
    cSimplePhysics();


    // Overrides
public:
    // Init/Finalize
    virtual  void  Initialize() override;
    virtual  void  Finalize() override;

public:
    // Update/Draw
    virtual  void  Draw( sf::RenderTarget* iRenderTarget ) override;
    virtual  void  Update( unsigned int iDeltaTime ) override;

public:
    // Entity
    virtual  void  IncomingEntity( cEntity* iEntity ) override;
    virtual  void  EntityLost( cEntity* iEntity ) override;

private:
    cEntityGrid  mEntityMap;
};

