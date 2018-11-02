#include "GameMockup.Screen.PremierScreen.h"


#include "Core.Application.GlobalAccess.h"

#include "Core.ECS.Core.World.h"
#include "Core.ECS.Core.Entity.h"
#include "Core.ECS.Component.UserInput.h"
#include "Core.ECS.Component.SimplePhysic.h"

#include "GameMockup.ECS.System.SquareController.h"
#include "Core.ECS.System.InputConverter.h"



namespace nScreen {


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------ Construction
// -------------------------------------------------------------------------------------


cPremierScreen::~cPremierScreen()
{
}


cPremierScreen::cPremierScreen() :
    tSuperClass( "Premier" )
{
}


// -------------------------------------------------------------------------------------
// ----------------------------------------------------------------------- Init/Finalize
// -------------------------------------------------------------------------------------


void
cPremierScreen::Initialize()
{
    tSuperClass::Initialize();

    FilePath( ::nCore::nApplication::cGlobalAccess::cGlobalAccess::Instance()->ProjectFolder() + "/Screens/Premier.screen" );
}


void
cPremierScreen::AdditionnalBuildScreen()
{
    mWorld->AddSystem( new ::nCore::nECS::nSystem::cInputConverter() );

    auto hero = mWorld->GetEntityByID( "Heroc8" );
    hero->AddComponent( new  ::nCore::nECS::nComponent::cUserInput() );
    auto physics = dynamic_cast< ::nCore::nECS::nComponent::cSimplePhysic* >( hero->GetComponentByName( "simplephysic" ) );
    physics->PhysicType( ::nCore::nECS::nComponent::cSimplePhysic::kDynamic );

    tSuperClass::AdditionnalBuildScreen();
}


} // namespace nScreen

