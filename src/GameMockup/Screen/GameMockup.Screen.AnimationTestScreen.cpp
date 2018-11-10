#include "GameMockup.Screen.AnimationTestScreen.h"

#include "Core.Animation.Animation.h"

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


#include "SFML/Audio.hpp"


#include <iostream>


namespace nScreen {


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------ Construction
// -------------------------------------------------------------------------------------


    cAnimationTest::~cAnimationTest()
{
}


    cAnimationTest::cAnimationTest() :
    tSuperClass( "animationtest" )
{
}


// -------------------------------------------------------------------------------------
// ----------------------------------------------------------------------- Init/Finalize
// -------------------------------------------------------------------------------------


void
cAnimationTest::Initialize()
{
    tSuperClass::Initialize();
}


void
cAnimationTest::Finalize()
{
    tSuperClass::Finalize();
}


void
cAnimationTest::AdditionnalBuildScreen()
{
    mWorld->AddLayer( PROJECTVIEWSIZE, 1.0 );
    mWorld->AddLayer( PROJECTVIEWSIZE, 3.0 );

    mWorld->AddSystem( ::nCore::nRegistries::cSystemRegistry::Instance()->CreateSystemFromName( "AnimationRenderer" ) );
    mWorld->AddSystem( ::nCore::nRegistries::cSystemRegistry::Instance()->CreateSystemFromName( "SimpleRenderer" ) );
    mWorld->AddSystem( ::nCore::nRegistries::cSystemRegistry::Instance()->CreateSystemFromName( "SquareController" ) );
    mWorld->AddSystem( ::nCore::nRegistries::cSystemRegistry::Instance()->CreateSystemFromName( "SimplePhysics" ) );
    mWorld->AddSystem( ::nCore::nRegistries::cSystemRegistry::Instance()->CreateSystemFromName( "InputConverter" ) );

    mWorld->mLayerEngine->LayerDistanceAtIndex( 2, 0 );

    ::nCore::nECS::nCore::cEntity* ent = new ::nCore::nECS::nCore::cEntity();
    ent->AddComponent( new ::nCore::nECS::nComponent::cTransformation( sf::Vector2f( 500.0F, 320.0F ), sf::Vector2f( 40.0F, 64.0F ), 0.0F ) );
    ent->AddComponent( new ::nCore::nECS::nComponent::cUserInput() );
    ent->AddComponent( new ::nCore::nECS::nComponent::cSimplePhysic( 40.0F, 64.0F, ::nCore::nECS::nComponent::cSimplePhysic::eType::kDynamic, false ) );

    auto animations = new ::nCore::nECS::nComponent::cAnimations();
    animations->AddSpriteSheetBasedAnimation( "mainAnimation", PROJECTDIR + "/Assets/Images/communiste_spritesheet.png", 12 );

    ::nCore::nAnimation::cAnimation*  theAnimation = animations->AddMultiFilesBasedAnimation( "second" );
    theAnimation->AddImage( PROJECTDIR + "/Assets/Images/sun_1.png" );
    theAnimation->AddImage( PROJECTDIR + "/Assets/Images/sun_2.png" );
    theAnimation->AddImage( PROJECTDIR + "/Assets/Images/sun_3.png" );
    theAnimation->AddImage( PROJECTDIR + "/Assets/Images/sun_4.png" );
    theAnimation->AddImage( PROJECTDIR + "/Assets/Images/sun_5.png" );
    theAnimation->AddImage( PROJECTDIR + "/Assets/Images/sun_6.png" );
    theAnimation->AddImage( PROJECTDIR + "/Assets/Images/sun_7.png" );
    theAnimation->AddImage( PROJECTDIR + "/Assets/Images/sun_8.png" );
    theAnimation->IsAnimationLooping( false );

    //theAnimation->SetEndOfAnimationCB( [ theAnimation ]()
    //    {
    //        theAnimation->Play();
    //    }
    //);

    ent->AddComponent( animations );
    ent->AddTag( "listener" );

    mWorld->AddEntityAndPutInLayer( ent, 0 );

    ::nCore::nECS::nCore::cEntity* wall = new ::nCore::nECS::nCore::cEntity();
    wall->AddComponent( new ::nCore::nECS::nComponent::cTransformation( sf::Vector2f( 500.0F, 500.0F ), sf::Vector2f( 40.0F, 400.0F ), 0.0F ) );
    wall->AddComponent( new ::nCore::nECS::nComponent::cColor( 255, 255, 0 ) );
    wall->AddComponent( new ::nCore::nECS::nComponent::cSimplePhysic( 40.0F, 400.0F, ::nCore::nECS::nComponent::cSimplePhysic::eType::kStatic, false ) );
    wall->AddTag( "wall" );

    mWorld->AddEntityAndPutInLayer( wall, 0 );

    tSuperClass::AdditionnalBuildScreen();
}


// -------------------------------------------------------------------------------------
// -------------------------------------------------------------- Main Running functions
// -------------------------------------------------------------------------------------


void
cAnimationTest::Draw( sf::RenderTarget* iRenderTarget )
{
    tSuperClass::Draw( iRenderTarget );
}


void
cAnimationTest::Update( unsigned int iDeltaTime )
{
    tSuperClass::Update( iDeltaTime );
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------ Events
// -------------------------------------------------------------------------------------


void
cAnimationTest::TextEntered( const sf::Event& iEvent )
{
    tSuperClass::TextEntered( iEvent );
}


void
cAnimationTest::KeyPressed( const sf::Event& iEvent )
{
    tSuperClass::KeyPressed( iEvent );
}


void
cAnimationTest::KeyReleased( const sf::Event& iEvent )
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

