#pragma once

#include "ECS/System.h"

#include <SFML/Graphics.hpp>

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
    virtual  void  Draw( sf::RenderTarget* iRenderTarget ) override;
    virtual  void  Update( unsigned int iDeltaTime ) override;

public:
    // Entity
    virtual  void  IncomingEntity( cEntity* iEntity ) override;
};

