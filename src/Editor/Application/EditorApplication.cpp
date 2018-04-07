#include "EditorApplication.h"


#include "ECS/Core/Entity.h"
#include "ECS/Core/World.h"
#include "ECS/Utilities/ComponentRegistry.h"
#include "ECS/Utilities/EntityParser.h"

#include "ECS/BasicComponents/Color.h"
#include "ECS/BasicComponents/Position.h"
#include "ECS/BasicComponents/SimplePhysic.h"
#include "ECS/BasicComponents/Size.h"
#include "ECS/BasicComponents/SpriteAnimated.h"
#include "ECS/BasicComponents/Text.h"

#include "ECS/BasicSystems/AnimationRenderer.h"
#include "ECS/BasicSystems/SimplerRenderer.h"

namespace  nApplication {

// -------------------------------------------------------------------------------------
// ------------------------------------------------------------ Construction/Destruction
// -------------------------------------------------------------------------------------


cEditorApplication::cEditorApplication()
{
}


// -------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------- Instance
// -------------------------------------------------------------------------------------


//static
cEditorApplication*
cEditorApplication::App()
{
    static cEditorApplication* gApplication = 0;
    if( !gApplication )
        gApplication = new cEditorApplication();

    return  gApplication;
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------ Access
// -------------------------------------------------------------------------------------


::nECS::cWorld*
cEditorApplication::World()
{
    return mWorld;
}


// -------------------------------------------------------------------------------------
// ----------------------------------------------------------------------- Init/Finalize
// -------------------------------------------------------------------------------------


void
cEditorApplication::Initialize()
{
    // NO TSUPERCLASS
    // As it would create a mMainWindow, which we don't want here
    // The behaviour is different when embeded into editor

    // =======ECS WORLD=======
    mWorld = new ::nECS::cWorld();

    // Following call may need world
    ::nECS::cComponentRegistry::Instance()->Initialize();
    ::nECS::cComponentRegistry::Instance()->RegisterComponent( new ::nECS::cColor() );
    ::nECS::cComponentRegistry::Instance()->RegisterComponent( new ::nECS::cPosition() );
    ::nECS::cComponentRegistry::Instance()->RegisterComponent( new ::nECS::cSize() );
    ::nECS::cComponentRegistry::Instance()->RegisterComponent( new ::nECS::cSpriteAnimated() );
    ::nECS::cComponentRegistry::Instance()->RegisterComponent( new ::nECS::cSimplePhysic() );

    mWorld->AddSystem( new ::nECS::cSimplerRenderer() );
    mWorld->AddSystem( new ::nECS::cAnimationRenderer() );

    ::nECS::cEntityParser::Instance()->Initialize( mWorld );
}


void
cEditorApplication::Finalize()
{
    ::nECS::cComponentRegistry::Instance()->Finalize();

    delete mWorld;
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------- Update/Draw
// -------------------------------------------------------------------------------------


void
cEditorApplication::Update( unsigned int iDeltaTime )
{
    mWorld->Update( iDeltaTime );
}


void
cEditorApplication::Draw( sf::RenderTarget* iRenderTarget )
{
    mWorld->Draw( iRenderTarget );
}

} //nApplication

