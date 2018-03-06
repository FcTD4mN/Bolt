#pragma once

#include "Application/Application.h"

class cWorld;
class cShortcuts;
class cEntityGrid;

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
    // Access
    cWorld*         World();
    cShortcuts*     ShortcutEngine();
    cEntityGrid*    EntityMap();

public:
    void Initialize();
    void Finalize();

public:
    void Update( unsigned int iDeltaTime );
    void Draw( sf::RenderTarget* iRenderTarget );

public:
    virtual  void  KeyPressed( const sf::Event& iEvent );   ///< A key was pressed (data in event.key)
    virtual  void  KeyReleased( const sf::Event& iEvent );  ///< A key was released (data in event.key)

private:
    cWorld*             mWorld;
    cShortcuts*         mShortcutEngine;
    cEntityGrid*        mEntityMap;
};

