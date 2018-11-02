#pragma once


#include "Core.ECS.Core.System.h"


#include <SFML/Graphics.hpp>


namespace nCore {
namespace nECS {
namespace nSystem {


    // Number 2 is the one based one the cAnimations component, the number one is based on spriteAnimated
    // this one will replace the old one basically
    // TODO: replace cAnimationRenderer with this one as soon as it's fully operationnal


class cAnimationRenderer :
    public ::nCore::nECS::nCore::cSystem
{
public:
    typedef  cSystem  tSuperClass;

public:
    virtual  ~cAnimationRenderer();
    cAnimationRenderer();
    cAnimationRenderer( const cAnimationRenderer& iSys );

    // Overrides
public:
    virtual  cSystem* Clone() const override;

public:
    // Update/Draw
    virtual  void  DrawEntity( sf::RenderTarget* iRenderTarget, ::nCore::nECS::nCore::cEntity* iEntity ) override;
    virtual  void  Update( unsigned int iDeltaTime ) override;

public:
    // Entity
    virtual  void  IncomingEntity( ::nCore::nECS::nCore::cEntity* iEntity ) override;

};


} // namespace nSystem
} // namespace nECS
} // namespace nCore

