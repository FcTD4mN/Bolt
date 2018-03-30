#pragma once

#include "Application/Application.h"

class cWorld;
class cMainMenu;

class cEditorApplication :
    public cApplication
{
public:
    typedef  cApplication  tSuperClass;

public:
    cEditorApplication();

public:
    static cEditorApplication* App();

public:
    // Access
    cWorld*         World();

public:
    void Initialize();
    void Finalize();

public:
    void Update( unsigned int iDeltaTime );
    void Draw( sf::RenderTarget* iRenderTarget );

private:
    cWorld*     mWorld;
    cMainMenu*  mMMenu;
};

