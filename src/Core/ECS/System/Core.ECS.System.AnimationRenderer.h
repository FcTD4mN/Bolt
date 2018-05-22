#pragma once


#include "Core.ECS.Core.System.h"


#include <SFML/Graphics.hpp>


namespace nECS {


class cAnimationRenderer :
    public cSystem
{
public:
    typedef  cSystem  tSuperClass;

public:
    virtual  ~cAnimationRenderer();
    cAnimationRenderer();


    // Overrides
public:
    // Init/Finalize
    virtual  void  Initialize() override;
    virtual  void  Finalize() override;

public:
    // Update/Draw
    virtual  void  DrawEntity( sf::RenderTarget* iRenderTarget, cEntity* iEntity ) override;
    virtual  void  Update( unsigned int iDeltaTime ) override;

public:
    // Entity
    virtual  void  IncomingEntity( cEntity* iEntity ) override;

};


} // namespace nECS

