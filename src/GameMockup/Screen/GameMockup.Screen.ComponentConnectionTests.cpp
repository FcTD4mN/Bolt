#include "GameMockup.Screen.ComponentConnectionTests.h"

#include "Core.Application.GlobalAccess.h"

#include "Core.ECS.Core.Entity.h"
#include "Core.ECS.Core.World.h"
#include "Core.Registries.SystemRegistry.h"

#include "Core.ECS.Component.Color.h"
#include "Core.ECS.Component.Transformation.h"
#include "Core.ECS.Component.SimplePhysic.h"
#include "Core.ECS.Component.UserInput.h"

#include "Core.Render.LayerEngine.h"


#include "GameMockup.ECS.System.SquareController.h"
#include "GameMockup.Application.GameApplication.h"


#include "SFML/Audio.hpp"


#include <iostream>


namespace nScreen {


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------ Construction
// -------------------------------------------------------------------------------------


cComponentConnectionTests::~cComponentConnectionTests()
{
}


cComponentConnectionTests::cComponentConnectionTests() :
    tSuperClass( "componentconnection" )
{
}


// -------------------------------------------------------------------------------------
// ----------------------------------------------------------------------- Init/Finalize
// -------------------------------------------------------------------------------------


void
cComponentConnectionTests::Initialize()
{
    tSuperClass::Initialize();
}


void
cComponentConnectionTests::Finalize()
{
    tSuperClass::Finalize();
}


void
cComponentConnectionTests::AdditionnalBuildScreen()
{
    mWorld->AddLayer( PROJECTVIEWSIZE, 1.0 );

    mWorld->AddSystem( ::nCore::nRegistries::cSystemRegistry::Instance()->CreateSystemFromName( "AnimationRenderer" ) );
    mWorld->AddSystem( ::nCore::nRegistries::cSystemRegistry::Instance()->CreateSystemFromName( "SimpleRenderer" ) );
    mWorld->AddSystem( ::nCore::nRegistries::cSystemRegistry::Instance()->CreateSystemFromName( "SquareController" ) );
    mWorld->AddSystem( ::nCore::nRegistries::cSystemRegistry::Instance()->CreateSystemFromName( "SimplePhysics" ) );
    mWorld->AddSystem( ::nCore::nRegistries::cSystemRegistry::Instance()->CreateSystemFromName( "InputConverter" ) );

    ::nCore::nECS::nCore::cEntity* ent = new ::nCore::nECS::nCore::cEntity();
    ent->AddComponent( new ::nCore::nECS::nComponent::cColor( 20, 200, 20 ) );
    ent->AddComponent( new ::nCore::nECS::nComponent::cTransformation( sf::Vector2f( 500.0F, 320.0F ), sf::Vector2f( 40.0F, 40.0F ), 0.0F ) );
    ent->AddComponent( new ::nCore::nECS::nComponent::cUserInput() );
    ent->AddComponent( new ::nCore::nECS::nComponent::cSimplePhysic( 0.F, 0.F, ::nCore::nECS::nComponent::cSimplePhysic::eType::kDynamic, false ) );
    ent->ConnectComponentsVariables( "simplephysic", "SizeW", "transformation", "x" );
    ent->ConnectComponentsVariables( "simplephysic", "SizeH", "transformation", "height" );

    mWorld->AddEntityAndPutInLayer( ent, 0 );


    ::nCore::nECS::nCore::cEntity* wall = new ::nCore::nECS::nCore::cEntity();
    wall->AddComponent( new ::nCore::nECS::nComponent::cTransformation( sf::Vector2f( 500.0F, 500.0F ), sf::Vector2f( 40.0F, 400.0F ), 0.0F ) );
    wall->AddComponent( new ::nCore::nECS::nComponent::cColor( 255, 255, 0 ) );
    wall->AddComponent( new ::nCore::nECS::nComponent::cSimplePhysic( 0.F, 0.F, ::nCore::nECS::nComponent::cSimplePhysic::eType::kStatic, false ) );
    wall->ConnectComponentsVariables( "simplephysic", "SizeW", "transformation", "width" );
    wall->ConnectComponentsVariables( "simplephysic", "SizeH", "transformation", "height" );
    wall->ConnectComponentsVariables( "simplephysic", "SizeH", "transformation", "height" ); // Tests for no duplicates
    wall->AddTag( "wall" );
    mWorld->AddEntityAndPutInLayer( wall, 0 );
    wall->ConnectComponentsVariablesFromEntity( "transformation", "width", ent, "transformation", "x" );
    wall->ConnectComponentsVariablesFromEntity( "transformation", "height", ent, "transformation", "x" );
    wall->DisconnectComponentsVariablesFromEntity( "transformation", "height", ent, "transformation", "x" );

    auto wall2 = wall->Clone();
    auto transWall2 = wall2->GetComponentByIDAs< ::nCore::nECS::nComponent::cTransformation* >( "transformation" );
    transWall2->X( 200.0F );
    transWall2->Y( 200.0F );
    //transWall2->W( 200.0F );
    transWall2->H( 20.0F );


    tSuperClass::AdditionnalBuildScreen();
}


// -------------------------------------------------------------------------------------
// -------------------------------------------------------------- Main Running functions
// -------------------------------------------------------------------------------------


void
cComponentConnectionTests::Draw( sf::RenderTarget* iRenderTarget )
{
    tSuperClass::Draw( iRenderTarget );
}


void
cComponentConnectionTests::Update( unsigned int iDeltaTime )
{
    tSuperClass::Update( iDeltaTime );
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------ Events
// -------------------------------------------------------------------------------------


void
cComponentConnectionTests::TextEntered( const sf::Event& iEvent )
{
    tSuperClass::TextEntered( iEvent );
}


void
cComponentConnectionTests::KeyPressed( const sf::Event& iEvent )
{
    tSuperClass::KeyPressed( iEvent );
}


void
cComponentConnectionTests::KeyReleased( const sf::Event& iEvent )
{
    if( iEvent.key.code == sf::Keyboard::Key::K )
    {
        ExportToFile( ::nCore::nApplication::cGlobalAccess::Instance()-> ProjectFolder() + "/GameSave.save" );
    }
    else if( iEvent.key.code == sf::Keyboard::Key::L )
    {
        ImportFromFile( PROJECTDIR + "/GameSave.save" );
    }

    tSuperClass::KeyReleased( iEvent );
}


} // namespace nScreen

