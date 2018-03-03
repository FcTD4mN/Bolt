#pragma once

#include "ECS/Core/System.h"

#include <SFML/Graphics.hpp>

class cSquareController :
    public cSystem
{
public:
    typedef  cSystem  tSuperClass;

public:
    virtual  ~cSquareController();
    cSquareController();


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

