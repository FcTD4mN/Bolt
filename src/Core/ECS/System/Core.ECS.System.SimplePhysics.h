#pragma once


#include "Core.ECS.Core.System.h"
#include "Core.Mapping.EntityMap.h"


#include <SFML/Graphics.hpp>


namespace nCore {
namespace nECS {
namespace nSystem {


class cSimplePhysics :
    public ::nCore::nECS::nCore::cSystem
{
public:
    typedef  cSystem  tSuperClass;

public:
    virtual  ~cSimplePhysics();
    cSimplePhysics();
    cSimplePhysics( const cSimplePhysics& iSys );


    // Overrides
public:
    virtual  cSystem* Clone() const override;

public:
    // Update/Draw
    virtual  void  DrawEntity( sf::RenderTarget* iRenderTarget, ::nCore::nECS::nCore::cEntity* iEntity ) override;
    virtual  void  Update( unsigned int iDeltaTime ) override;

public:
    void  SetGravity( float  iGravity );

private:
    sf::FloatRect  GetEntityHitBoxAndCenter( sf::Vector2f* oCenter, ::nCore::nECS::nCore::cEntity * iEntity );

public:
    // Entity
    virtual  void  IncomingEntity( ::nCore::nECS::nCore::cEntity* iEntity ) override;

private:
    float  mGlobalGravity;

    //DEBUG
    ::nCore::nMath::cEdgeF mDebugEdge;

};


} // namespace nSystem
} // namespace nECS
} // namespace nCore

