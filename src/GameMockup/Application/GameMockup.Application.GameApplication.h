#pragma once

#include "Core.Application.Application.h"

namespace nECS { class cWorld; }
namespace nShortcuts { class cShortcuts; }
namespace nMapping { class cEntityGrid; }

namespace nApplication {

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
    ::nECS::cWorld*         World();
    ::nShortcuts::cShortcuts*     ShortcutEngine();
    ::nMapping::cEntityGrid*    EntityMap();

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
    ::nECS::cWorld*             mWorld;
};

} // nApplication