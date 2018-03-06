#pragma once

#include "ECS/Core/System.h"

#include <SFML/Graphics.hpp>

class cSightSystem :
    public cSystem
{
public:
    typedef  cSystem  tSuperClass;

public:
    virtual  ~cSightSystem();
    cSightSystem();


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

private:
    std::vector< cEntity* > mPointsOfInterest;

    sf::Vector2f mDEBUGSightLine;
    sf::Vector2f mDEBUGSightPA;
    sf::Vector2f mDEBUGSightPB;
};

