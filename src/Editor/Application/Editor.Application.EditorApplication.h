#pragma once

#include "Core.Application.Application.h"

namespace nECS { class cWorld; }
namespace nMainMenu { class cMainMenu; }

namespace nApplication {

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
    ::nECS::cWorld*         World();

public:
    void Initialize();
    void Finalize();

public:
    void Update( unsigned int iDeltaTime );
    void Draw( sf::RenderTarget* iRenderTarget );

private:
    ::nECS::cWorld*     mWorld;
    ::nMainMenu::cMainMenu*  mMMenu;
};

} //nApplication

