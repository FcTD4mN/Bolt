#pragma once

#include "Core.Screen.Screen.h"

namespace nScreen {

class cComponentConnectionTests :
    public cScreen
{
public:
    typedef  cScreen  tSuperClass;

public:
    // Contruction/Destruction
    virtual  ~cComponentConnectionTests();
    cComponentConnectionTests();

public:
    virtual  void  Initialize() override;
    virtual  void  Finalize() override;

public:
    virtual  void  AdditionnalBuildScreen() override;

public:
    virtual  void  Draw( sf::RenderTarget* iRenderTarget ) override;
    virtual  void  Update( unsigned int iDeltaTime ) override;

public:
    // Events
    virtual  void  TextEntered( const sf::Event& iEvent ) override;            ///< A character was entered (data in event.text)
    virtual  void  KeyPressed( const sf::Event& iEvent ) override;             ///< A key was pressed (data in event.key)
    virtual  void  KeyReleased( const sf::Event& iEvent ) override;            ///< A key was released (data in event.key)
};

} //nScreen

