#pragma once

#include "Core.ECS.Core.System.h"

#include "Core.Mapping.PhysicEntityGrid.h"


#include <SFML/Graphics.hpp>

// DEBUG
#include "Core.Math.Edge.h"


namespace nECS {


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
    void  SetGravity( float  iGravity );

private:
    sf::FloatRect  GetEntityHitBoxAndCenter( sf::Vector2f* oCenter, ::nECS::cEntity * iEntity );

public:
    // Entity
    virtual  void  IncomingEntity( cEntity* iEntity ) override;
    virtual  void  EntityLost( cEntity* iEntity ) override;

private:
    std::vector< cEntity* > mStaticEntities;
    std::vector< cEntity* > mDynamicEntities;

    float  mGlobalGravity;

    //DEBUG
    ::nMath::cEdgeF mDebugEdge;

};


} // namespace nECS

