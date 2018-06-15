#include "Editor.Application.EditorApplication.h"


#include "Core.ECS.Core.Entity.h"
#include "Core.ECS.Core.World.h"
#include "Core.ECS.Utilities.ComponentRegistry.h"
#include "Core.ECS.Utilities.EntityParser.h"

#include "Core.ECS.Component.Color.h"
#include "Core.ECS.Component.Position.h"
#include "Core.ECS.Component.SimplePhysic.h"
#include "Core.ECS.Component.Size.h"
#include "Core.ECS.Component.SpriteAnimated.h"
#include "Core.ECS.Component.Text.h"

#include "Core.ECS.System.AnimationRenderer.h"
#include "Core.ECS.System.SimplePhysics.h"
#include "Core.ECS.System.SimplerRenderer.h"

#include "Core.ECS.Core.GlobalEntityMap.h"

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
// ----------------------------------------------------------------------- Init/Finalize
// -------------------------------------------------------------------------------------


void
cEditorApplication::Initialize()
{
    // NO TSUPERCLASS
    // As it would create a mMainWindow, which we don't want here
    // The behaviour is different when embeded into editor

    ::nECS::cGlobalEntityMap::Instance()->Initialize( 1024, 1024, 800 );

    // Following call may need world
    //::nECS::cComponentRegistry::Instance()->Initialize( "I:/ProjectTest" );

    //mWorld->AddSystem( new ::nECS::cSimplerRenderer() );
    //mWorld->AddSystem( new ::nECS::cAnimationRenderer() );

    //::nECS::cEntityParser::Instance()->Initialize( "I:/ProjectTest" );
}


void
cEditorApplication::Finalize()
{
    //::nECS::cComponentRegistry::Instance()->Finalize();

    //delete mWorld;
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------- Update/Draw
// -------------------------------------------------------------------------------------

//
//void
//cEditorApplication::Update( unsigned int iDeltaTime )
//{
//    World()->Update( iDeltaTime );
//}

} //nApplication

