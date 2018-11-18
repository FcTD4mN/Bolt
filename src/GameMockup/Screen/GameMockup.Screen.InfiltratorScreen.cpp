#include "GameMockup.Screen.InfiltratorScreen.h"


#include "Core.Application.GlobalAccess.h"

#include "Core.AI.BehaviourTree.h"

#include "Core.ECS.Core.Entity.h"
#include "Core.ECS.Core.World.h"

#include "Core.ECS.Component.Animations.h"
#include "Core.ECS.Component.BehaviourTree.h"
#include "Core.ECS.Component.Color.h"
#include "Core.ECS.Component.Direction.h"
#include "Core.ECS.Component.Transformation.h"
#include "Core.ECS.Component.FieldOfView.h"
#include "Core.ECS.Component.SimplePhysic.h"
#include "Core.ECS.Component.UserInput.h"

#include "Core.ECS.System.AnimationRenderer.h"
#include "Core.ECS.System.BehaviourTreeSystem.h"
#include "Core.ECS.System.SightSystem.h"
#include "Core.ECS.System.SimplerRenderer.h"
#include "Core.ECS.System.SimplePhysics.h"
#include "Core.ECS.System.InputConverter.h"

#include "Core.Math.Utils.h"


#include "GameMockup.Application.GameApplication.h"

#include "GameMockup.ECS.System.SquareController.h"


#include <iostream>


namespace nScreen {


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------ Construction
// -------------------------------------------------------------------------------------


cInfiltratorScreen::~cInfiltratorScreen()
{
}


cInfiltratorScreen::cInfiltratorScreen() :
    tSuperClass( "infiltrator" )
{
}


// -------------------------------------------------------------------------------------
// ----------------------------------------------------------------------- Init/Finalize
// -------------------------------------------------------------------------------------


void
cInfiltratorScreen::Initialize()
{
    tSuperClass::Initialize();
}


void
cInfiltratorScreen::Finalize()
{
    tSuperClass::Finalize();
}


void
cInfiltratorScreen::AdditionnalBuildScreen()
{
    sf::Window* window = ::nCore::nApplication::cApplication::App()->Window();
    sf::Vector2u windowSize = window->getSize();

    // Systems
    mWorld->AddSystem( new ::nCore::nECS::nSystem::cAnimationRenderer() );
    mWorld->AddSystem( new ::nCore::nECS::nSystem::cSimplerRenderer() );
    mWorld->AddSystem( new ::nCore::nECS::nSystem::cSimplePhysics() );
    mWorld->AddSystem( new ::nCore::nECS::nSystem::cSightSystem() );
    mWorld->AddSystem( new ::nECS::cSquareController() );
    mWorld->AddSystem( new ::nCore::nECS::nSystem::cBehaviourTreeSystem() );
    mWorld->AddSystem( new ::nCore::nECS::nSystem::cInputConverter() );

    ::nCore::nECS::nCore::cEntity* wall1 = new ::nCore::nECS::nCore::cEntity();
    wall1->AddComponent( new ::nCore::nECS::nComponent::cTransformation( sf::Vector2f( 0.0F, 500.0F ), sf::Vector2f( 800.0F, 100.0F ), 0.0F ) );
    wall1->AddComponent( new ::nCore::nECS::nComponent::cColor( 180, 185, 183 ) );
    wall1->AddTag( "wall" );
    wall1->AddComponent( new ::nCore::nECS::nComponent::cSimplePhysic( 800.0F, 100.0F, ::nCore::nECS::nComponent::cSimplePhysic::eType::kStatic, false ) );
    mWorld->AddEntityAndPutInLayer( wall1, 0 );

    //cEntity* wall2 = new cEntity( world );
    //wall2->AddComponent( new ::nECS::cTransformation( sf::Vector2f( 124.0F, 124.0F ), sf::Vector2f( 256.0F, 64.0F ), 0.0F ) );
    //wall2->AddComponent( new cColor( 20, 180, 20 ) );
    //wall2->AddTag( "wall" );
    //wall2->AddComponent( new cSimplePhysic( 124.0F, 124.0F, 256.0F, 64.0F, cSimplePhysic::eType::kStatic, false ) );
    //world->AddEntity( wall2 );

    //cEntity* wall3 = new cEntity( world );
    //wall3->AddComponent( new ::nECS::cTransformation( sf::Vector2f( 60.0F, 250.0F ), sf::Vector2f( 64.0F, 64.0F ), 0.0F ) );
    //wall3->AddComponent( new cColor( 20, 180, 20 ) );
    //wall3->AddTag( "wall" );
    //wall3->AddComponent( new cSimplePhysic( 60.0F, 250.0F, 64.0F, 64.0F, cSimplePhysic::eType::kStatic, false ) );
    //world->AddEntity( wall3 );

    //cEntity* wall4 = new cEntity( world );
    //wall4->AddComponent( new ::nECS::cTransformation( sf::Vector2f( 450.0F, 200.0F ), sf::Vector2f( 64.0F, 256.0F ), 0.0F ) );
    //wall4->AddComponent( new cColor( 20, 180, 20 ) );
    //wall4->AddTag( "wall" );
    //wall4->AddComponent( new cSimplePhysic( 450.0F, 200.0F, 64.0F, 256.0F, cSimplePhysic::eType::kStatic, false ) );
    //world->AddEntity( wall4 );

    ::nCore::nECS::nCore::cEntity* hero = new ::nCore::nECS::nCore::cEntity();
    hero->AddComponent( new ::nCore::nECS::nComponent::cTransformation( sf::Vector2f( 350.0F, 350.0F ), sf::Vector2f( 40.0F, 64.0F ), 0.0F ) );
    //hero->AddComponent( new ::nCore::nECS::nComponent::cColor( 20, 20, 200 ) );

    auto animations = new ::nCore::nECS::nComponent::cAnimations();
    hero->AddComponent( animations );

    animations->AddSpriteSheetBasedAnimation( "main", PROJECTDIR + "/Assets/Images/communiste_spritesheet.png", 12, 1 );


    hero->AddComponent( new ::nCore::nECS::nComponent::cUserInput() );
    hero->AddTag( "hero" );
    hero->AddComponent( new ::nCore::nECS::nComponent::cSimplePhysic( 40.0F, 64.0F, ::nCore::nECS::nComponent::cSimplePhysic::eType::kDynamic, false ) );
    mWorld->AddEntityAndPutInLayer( hero, 0 );
    //BuildBehaviourTree( hero );


    ::nCore::nECS::nCore::cEntity* topFrame = new ::nCore::nECS::nCore::cEntity();
    topFrame->AddComponent( new ::nCore::nECS::nComponent::cTransformation( sf::Vector2f( 145.F, 90.F ), sf::Vector2f( 110.0F, 5.0F ), 0.0F ) );
    topFrame->AddComponent( new ::nCore::nECS::nComponent::cColor( 60, 30, 20 ) );
    topFrame->AddComponent( new ::nCore::nECS::nComponent::cSimplePhysic( 110.0f, 5.0f, ::nCore::nECS::nComponent::cSimplePhysic::eType::kStatic, false ) );
    topFrame->AddTag( "wall" );
    mWorld->AddEntityAndPutInLayer( topFrame, 0 );

    ::nCore::nECS::nCore::cEntity* leftFrame = new ::nCore::nECS::nCore::cEntity();
    leftFrame->AddComponent( new ::nCore::nECS::nComponent::cTransformation( sf::Vector2f( 140.F, 95.F ), sf::Vector2f( 5.0F, 10.0F ), 0.0F ) );
    leftFrame->AddComponent( new ::nCore::nECS::nComponent::cColor( 60, 30, 20 ) );
    leftFrame->AddComponent( new ::nCore::nECS::nComponent::cSimplePhysic( 5.0f, 10.0f, ::nCore::nECS::nComponent::cSimplePhysic::eType::kStatic, false ) );
    leftFrame->AddTag( "wall" );
    mWorld->AddEntityAndPutInLayer( leftFrame, 0 );

    ::nCore::nECS::nCore::cEntity* rightFrame = new ::nCore::nECS::nCore::cEntity();
    rightFrame->AddComponent( new ::nCore::nECS::nComponent::cTransformation( sf::Vector2f( 255.F, 95.F ), sf::Vector2f( 5.0F, 10.0F ), 0.0F ) );
    rightFrame->AddComponent( new ::nCore::nECS::nComponent::cColor( 60, 30, 20 ) );
    rightFrame->AddComponent( new ::nCore::nECS::nComponent::cSimplePhysic( 5.0f, 10.0f, ::nCore::nECS::nComponent::cSimplePhysic::eType::kStatic, false ) );
    rightFrame->AddTag( "wall" );
    mWorld->AddEntityAndPutInLayer( rightFrame, 0 );

    mMechant = new ::nCore::nECS::nCore::cEntity();
    mMechant->AddComponent( new ::nCore::nECS::nComponent::cTransformation( sf::Vector2f( 150.0F, 100.0F ), sf::Vector2f( 1.0F, 1.0F ), 0.0F ) );
    mMechant->AddComponent( new ::nCore::nECS::nComponent::cColor( 180, 20, 20 ) );
    mMechant->AddComponent( new ::nCore::nECS::nComponent::cFieldOfView( 360, 1000 ) );
    mMechant->AddComponent( new ::nCore::nECS::nComponent::cDirection( ::nCore::nMath::Normale( sf::Vector2f( 0.0F, 1.0F ) ) ) );
    //mMechant->AddComponent( new ::nECS::cSimplePhysic( 1.0F, 1.0F, ::nECS::cSimplePhysic::eType::kStatic, false ) );
    mWorld->AddEntityAndPutInLayer( mMechant, 0 );

    ::nCore::nECS::nCore::cEntity* light = new ::nCore::nECS::nCore::cEntity();
    light->AddComponent( new ::nCore::nECS::nComponent::cTransformation( sf::Vector2f( 250.0F, 100.0F ), sf::Vector2f( 1.0F, 1.0F ), 0.0F ) );
    light->AddComponent( new ::nCore::nECS::nComponent::cColor( 180, 20, 20 ) );
    light->AddComponent( new ::nCore::nECS::nComponent::cFieldOfView( 360, 1000 ) );
    light->AddComponent( new ::nCore::nECS::nComponent::cDirection( ::nCore::nMath::Normale( sf::Vector2f( 0.0F, 1.0F ) ) ) );
    //light->AddComponent( new ::nECS::cSimplePhysic( 1.0F, 1.0F, ::nECS::cSimplePhysic::eType::kStatic, false ) );
    mWorld->AddEntityAndPutInLayer( light, 0 );

    int swall = 2;
    for( int i = 0; i < swall; ++i )
    {
        for( int j = 0; j < swall; ++j )
        {
            ::nCore::nECS::nCore::cEntity* wall = new ::nCore::nECS::nCore::cEntity();
            wall->AddComponent( new ::nCore::nECS::nComponent::cTransformation( sf::Vector2f( float( i ) * 800.0F / float( swall ), float( j ) * 600.0F / float( swall ) ),
                                sf::Vector2f( 5.0F, 5.0F ),
                                0.0F ) );
            wall->AddComponent( new ::nCore::nECS::nComponent::cColor( 20, 180, 20 ) );
            wall->AddComponent( new ::nCore::nECS::nComponent::cSimplePhysic( 5.0f, 5.0f, ::nCore::nECS::nComponent::cSimplePhysic::eType::kStatic, false ) );
            wall->AddTag( "wall" );
            mWorld->AddEntityAndPutInLayer( wall, 0 );
        }
    }

    mRotationFOV.rotate( 2.0F );

    tSuperClass::AdditionnalBuildScreen();
}


// -------------------------------------------------------------------------------------
// -------------------------------------------------------------- Main Running functions
// -------------------------------------------------------------------------------------


void
cInfiltratorScreen::BuildBehaviourTree( ::nCore::nECS::nCore::cEntity* iEntity )
{
    ::nCore::nAI::cBehaviourTree* idleNode       = new ::nCore::nAI::cBehaviourTree( "idle",      iEntity->GetHandle() );
    idleNode->AddComponentSnapShot( "simplephysic" );
    auto salut = dynamic_cast< ::nCore::nECS::nComponent::cSimplePhysic* >( idleNode->GetSnapShotByName( "simplephysic" ) );
    salut->mVelocity.x = 0;
    salut->mVelocity.y = 0;

    idleNode->AddComponentSnapShot( "animations" );
    auto spriteIdle = dynamic_cast< ::nCore::nECS::nComponent::cAnimations* >( idleNode->GetSnapShotByName( "animations" ) );
    spriteIdle->CurrentAnimationIsPaused( true );


    // =====================================================================
    // =====================================================================


    ::nCore::nAI::cBehaviourTree* moveState = new ::nCore::nAI::cBehaviourTree( "move", iEntity->GetHandle() );
    moveState->SetOnUpdateFunction( []( ::nCore::nECS::nCore::cEntity* iEntity, unsigned int iDeltaTime )
    {
        auto physic = dynamic_cast< ::nCore::nECS::nComponent::cSimplePhysic* >( iEntity->GetComponentByID( "simplephysic" ) );
        auto animations = dynamic_cast< ::nCore::nECS::nComponent::cAnimations* >( iEntity->GetComponentByID( "animations" ) );
        auto userinput= dynamic_cast< ::nCore::nECS::nComponent::cUserInput* >( iEntity->GetComponentByID( "userinput" ) );

        bool rightMotion    = userinput->ContainsAction( "moveright" );
        bool leftMotion     = userinput->ContainsAction( "moveleft" );
        bool upMotion       = userinput->ContainsAction( "moveup" );
        bool downMotion     = userinput->ContainsAction( "movedown" );

        if( rightMotion )
            physic->mVelocity.x = 1.0F;
        if( leftMotion )
            physic->mVelocity.x = -1.0F;

        if( rightMotion == leftMotion )
            physic->mVelocity.x = 0.0F;

        if( upMotion )
            physic->mVelocity.y = -1.0F;
        if( downMotion )
            physic->mVelocity.y = 1.0F;

        if( upMotion == downMotion )
            physic->mVelocity.y = 0.0F;

        animations->CurrentAnimationIsPaused( false );
        animations->CurrentAnimationIsFlipped( rightMotion );
    } );


    idleNode->SetOnEnterFunction( [ idleNode ]( ::nCore::nECS::nCore::cEntity* iEntity )
    {
        auto animation = dynamic_cast< ::nCore::nECS::nComponent::cAnimations* >( iEntity->GetComponentByID( "animations" ) );
        auto ssanimation = dynamic_cast< ::nCore::nECS::nComponent::cAnimations* >( idleNode->GetSnapShotByName( "animations" ) );
        ssanimation->CurrentAnimationIsFlipped( animation->CurrentAnimationIsFlipped() );
    } );


    idleNode->AddNodeConditionnal( moveState, "move", []( ::nCore::nECS::nCore::cEntity* iEntity )
    {
        auto userInput = dynamic_cast< ::nCore::nECS::nComponent::cUserInput* >( iEntity->GetComponentByID( "userinput" ) );
        if( userInput )
        {
            bool rightMotion = userInput->ContainsAction( "moveright" );
            bool leftMotion = userInput->ContainsAction( "moveleft" );
            bool upMotion = userInput->ContainsAction( "moveup" );
            bool downMotion = userInput->ContainsAction( "movedown" );

            return  rightMotion || leftMotion || upMotion || downMotion;
        }

        return  false;
    } );


    moveState->AddNodeConditionnal( idleNode, "idle", []( ::nCore::nECS::nCore::cEntity* iEntity )
    {
        auto userInput = dynamic_cast< ::nCore::nECS::nComponent::cUserInput* >( iEntity->GetComponentByID( "userinput" ) );
        if( userInput )
        {
            bool rightMotion = userInput->ContainsAction( "moveright" );
            bool leftMotion = userInput->ContainsAction( "moveleft" );
            bool upMotion = userInput->ContainsAction( "moveup" );
            bool downMotion = userInput->ContainsAction( "movedown" );

            return  !(rightMotion || leftMotion || upMotion || downMotion);
        }

        return  false;
    } );

    iEntity->AddComponent( new ::nCore::nECS::nComponent::cBehaviourTree( idleNode ) );
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------ Events
// -------------------------------------------------------------------------------------


void
cInfiltratorScreen::KeyPressed( const sf::Event& iEvent )
{
    if( iEvent.key.code == sf::Keyboard::Key::X )
    {
        auto direction = dynamic_cast< ::nCore::nECS::nComponent::cDirection* >( mMechant->GetComponentByID( "direction" ) );
        direction->SetUsingVector( mRotationFOV.transformPoint( direction->AsVector2F() ) );
    }
    else if( iEvent.key.code == sf::Keyboard::Key::C )
    {
        auto direction = dynamic_cast< ::nCore::nECS::nComponent::cDirection* >( mMechant->GetComponentByID( "direction" ) );
        mRotationFOV = mRotationFOV.getInverse();
        direction->SetUsingVector( mRotationFOV.transformPoint( direction->AsVector2F() ) );
        mRotationFOV = mRotationFOV.getInverse();
    }
    else if( iEvent.key.code == sf::Keyboard::Key::K )
    {
        ExportToFile( ::nCore::nApplication::cGlobalAccess::Instance()->ProjectFolder() + "/GameSave.save" );
    }
    else if( iEvent.key.code == sf::Keyboard::Key::L )
    {
        ImportFromFile( ::nCore::nApplication::cGlobalAccess::Instance()->ProjectFolder() + "/GameSave.save" );
    }

    tSuperClass::KeyPressed( iEvent );
}


} // namespace nScreen

