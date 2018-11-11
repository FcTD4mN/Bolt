#include "GameMockup.Application.GameApplication.h"


#include "Core.ECS.Core.Entity.h"
#include "Core.ECS.Core.World.h"
#include "Core.Registries.ComponentRegistry.h"
#include "Core.Registries.SystemRegistry.h"

#include "Core.Project.Project.h"

#include "Core.Screen.Screen.h"

#include "GameMockup.ECS.System.SquareController.h"

#include "GameMockup.Screen.AnimationTestScreen.h"
#include "GameMockup.Screen.ComponentConnectionTests.h"
#include "GameMockup.Screen.GameScreen.h"
#include "GameMockup.Screen.InfiltratorScreen.h"
#include "GameMockup.Screen.PremierScreen.h"
#include "GameMockup.Screen.EntityGridDebug.h"


::nCore::nApplication::cApplication*
CreateApplication()
{
    if( ::nGameMockup::nApplication::cApplication::App() )
        return  ::nGameMockup::nApplication::cApplication::App();
    return  new  ::nGameMockup::nApplication::cApplication();
}

namespace nGameMockup {
namespace nApplication {


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------ Construction/Destruction
// -------------------------------------------------------------------------------------


cApplication::cApplication():
    tSuperClass()
{
}


// -------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------- Instance
// -------------------------------------------------------------------------------------


//static
cApplication*
cApplication::App()
{
    return  dynamic_cast< cApplication* >( tSuperClass::App() );
}


// -------------------------------------------------------------------------------------
// ----------------------------------------------------------------------- Init/Finalize
// -------------------------------------------------------------------------------------


void
cApplication::Initialize()
{
    // =========== GAME SPECIFIC SYSTEMS ===========
    ::nCore::nRegistries::cSystemRegistry::Instance()->RegisterItem( "SquareController", new  ::nECS::cSquareController() );

    // =========== APPLICATION/PROJET INIT ===========
    tSuperClass::Initialize();

    // =========== GENERAL CONFIG ===========
    mMainWindow->setKeyRepeatEnabled( false );

    sf::Vector2u winSize = mMainWindow->getSize();
}


void
cApplication::Finalize()
{
    tSuperClass::Finalize();

    ::nCore::nRegistries::cComponentRegistry::Instance()->Finalize();
}


void
cApplication::BuildProject()
{
    auto infiltratorScreen = new ::nScreen::cInfiltratorScreen();
    mProject->AddScreen( infiltratorScreen );

    auto gameScreen = new ::nScreen::cGameScreen();
    mProject->AddScreen( gameScreen );

    auto animationTestScreen = new ::nScreen::cAnimationTest();
    mProject->AddScreen( animationTestScreen );

    auto premierScreen = new ::nScreen::cPremierScreen();
    mProject->AddScreen( premierScreen );

    auto egriddebug = new ::nScreen::cEGridDebug();
    mProject->AddScreen( egriddebug );

    auto connectionTest = new ::nScreen::cComponentConnectionTests();
    mProject->AddScreen( connectionTest );

    mProject->SetCurrentScreen( "componentconnection" );
}


} // namespace nApplication
} // namespace nGameMockup

