#pragma once

#include "Application/Application.h"


class cGameApplication :
    public cApplication
{
public:
    typedef  cApplication  tSuperClass;

public:
    cGameApplication();

public:
    static cGameApplication* App();

public:
    void Initialize();
    void Finalize();

public:
    void Update();
    void Draw();

public:
    virtual  void  KeyPressed( const sf::Event& iEvent );   ///< A key was pressed (data in event.key)
    virtual  void  KeyReleased( const sf::Event& iEvent );  ///< A key was released (data in event.key)
};

