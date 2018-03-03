#pragma once

#include "ECS/Core/System.h"

#include <SFML/Graphics.hpp>

class cSimplerRenderer :
    public cSystem
{
public:
    typedef  cSystem  tSuperClass;

public:
    virtual  ~cSimplerRenderer();
    cSimplerRenderer();


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

