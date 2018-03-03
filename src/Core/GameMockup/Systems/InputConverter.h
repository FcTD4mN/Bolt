#pragma once

#include "ECS/Core/System.h"

#include <SFML/Graphics.hpp>

class cInputConverter :
    public cSystem
{
public:
    typedef  cSystem  tSuperClass;

public:
    virtual  ~cInputConverter();
    cInputConverter();


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

public:
    // Events
    virtual  void  KeyPressed( const sf::Event& iEvent ) override;             ///< A key was pressed (data in event.key)
    virtual  void  KeyReleased( const sf::Event& iEvent ) override;            ///< A key was released (data in event.key)

};

