#include "GameMockup.Screen.EntityGridDebug.h"

#include "Core.Application.GlobalAccess.h"

#include "Core.ECS.Core.Entity.h"
#include "Core.ECS.Core.World.h"
#include "Core.Registries.SystemRegistry.h"

#include "Core.ECS.Component.Color.h"
#include "Core.ECS.Component.OcclusionFactor.h"
#include "Core.ECS.Component.Transformation.h"
#include "Core.ECS.Component.SimplePhysic.h"
#include "Core.ECS.Component.Sound.h"
#include "Core.ECS.Component.UserInput.h"
#include "Core.ECS.Component.ZDepth.h"
#include "Core.ECS.Component.Animations.h"

#include "Core.Render.LayerEngine.h"


#include "GameMockup.ECS.System.SquareController.h"
#include "GameMockup.Application.GameApplication.h"


#include <iostream>


namespace nScreen {


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------ Construction
// -------------------------------------------------------------------------------------


cEGridDebug::~cEGridDebug()
{
}


cEGridDebug::cEGridDebug() :
    tSuperClass( "egriddebug" )
{
}


// -------------------------------------------------------------------------------------
// ----------------------------------------------------------------------- Init/Finalize
// -------------------------------------------------------------------------------------


void
cEGridDebug::Initialize()
{
    tSuperClass::Initialize();
}


void
cEGridDebug::Finalize()
{
    tSuperClass::Finalize();
}


void
cEGridDebug::AdditionnalBuildScreen()
{
    mWorld->AddSystem( ::nCore::nRegistries::cSystemRegistry::Instance()->CreateSystemFromName( "AnimationRenderer" ) );
    mWorld->AddSystem( ::nCore::nRegistries::cSystemRegistry::Instance()->CreateSystemFromName( "SimpleRenderer" ) );
    //mWorld->AddSystem( ::nCore::nRegistries::cSystemRegistry::Instance()->CreateSystemFromName( "SquareController" ) );
    mWorld->AddSystem( ::nCore::nRegistries::cSystemRegistry::Instance()->CreateSystemFromName( "SimplePhysics" ) );
    mWorld->AddSystem( ::nCore::nRegistries::cSystemRegistry::Instance()->CreateSystemFromName( "InputConverter" ) );

    mTheEntityToDestroy = new ::nCore::nECS::nCore::cEntity();
    mTheEntityToDestroy->AddComponent( new ::nCore::nECS::nComponent::cTransformation( sf::Vector2f( 100.0F, 200.0F ), sf::Vector2f( 40.0F, 64.0F ), 0.0F ) );
    mTheEntityToDestroy->AddComponent( new ::nCore::nECS::nComponent::cUserInput() );
    mTheEntityToDestroy->AddComponent( new ::nCore::nECS::nComponent::cColor( sf::Color( 20, 60, 60 ) ) );

    auto  physics = new ::nCore::nECS::nComponent::cSimplePhysic( 40.0F, 64.0F, ::nCore::nECS::nComponent::cSimplePhysic::eType::kDynamic, false );
    physics->mVelocity = sf::Vector2f( 1.F, 0.F );
    mTheEntityToDestroy->AddComponent( physics );

    mWorld->AddEntityAndPutInLayer( mTheEntityToDestroy, 0 );

    tSuperClass::AdditionnalBuildScreen();
}


// -------------------------------------------------------------------------------------
// -------------------------------------------------------------- Main Running functions
// -------------------------------------------------------------------------------------


void
cEGridDebug::Draw( sf::RenderTarget* iRenderTarget )
{
    tSuperClass::Draw( iRenderTarget );
}


void
cEGridDebug::Update( unsigned int iDeltaTime )
{
    tSuperClass::Update( iDeltaTime );
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------ Events
// -------------------------------------------------------------------------------------


void
cEGridDebug::TextEntered( const sf::Event& iEvent )
{
    tSuperClass::TextEntered( iEvent );
}


void
cEGridDebug::KeyPressed( const sf::Event& iEvent )
{
    tSuperClass::KeyPressed( iEvent );
}


void
cEGridDebug::KeyReleased( const sf::Event& iEvent )
{
    if( iEvent.key.code == sf::Keyboard::Key::Delete )
    {
        mTheEntityToDestroy->Destroy();
    }

    tSuperClass::KeyReleased( iEvent );
}


} // namespace nScreen

