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


cWorld*
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
    mWorld = new cWorld();

    // Following call may need world
    cComponentRegistry::Instance()->Initialize();
    cComponentRegistry::Instance()->RegisterComponent( new cColor() );
    cComponentRegistry::Instance()->RegisterComponent( new cPosition() );
    cComponentRegistry::Instance()->RegisterComponent( new cSize() );
    cComponentRegistry::Instance()->RegisterComponent( new cSpriteAnimated() );
    cComponentRegistry::Instance()->RegisterComponent( new cSimplePhysic() );

    mWorld->AddSystem( new cSimplerRenderer() );
    mWorld->AddSystem( new cAnimationRenderer() );

    cEntityParser::Instance()->Initialize( mWorld );
}


void
cEditorApplication::Finalize()
{
    cComponentRegistry::Instance()->Finalize();

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