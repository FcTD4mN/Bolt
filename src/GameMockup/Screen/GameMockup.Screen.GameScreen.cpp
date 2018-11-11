#include "GameMockup.Screen.GameScreen.h"


#include "Core.Application.GlobalAccess.h"

#include "Core.ECS.Core.Entity.h"
#include "Core.ECS.Core.World.h"
#include "Core.Registries.SystemRegistry.h"

#include "Core.ECS.Component.Animations.h"
#include "Core.ECS.Component.Color.h"
#include "Core.ECS.Component.OcclusionFactor.h"
#include "Core.ECS.Component.Transformation.h"
#include "Core.ECS.Component.SimplePhysic.h"
#include "Core.ECS.Component.Sound.h"
#include "Core.ECS.Component.UserInput.h"
#include "Core.ECS.Component.ZDepth.h"

#include "Core.Render.LayerEngine.h"

#include "Core.Shader.Shader2D.h"


#include "GameMockup.ECS.System.SquareController.h"
#include "GameMockup.Application.GameApplication.h"


#include "SFML/Audio.hpp"


#include <iostream>


namespace nScreen {


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------ Construction
// -------------------------------------------------------------------------------------


cGameScreen::~cGameScreen()
{
}


cGameScreen::cGameScreen() :
    tSuperClass( "gamescreen" )
{
}


// -------------------------------------------------------------------------------------
// ----------------------------------------------------------------------- Init/Finalize
// -------------------------------------------------------------------------------------


void
cGameScreen::Initialize()
{
    tSuperClass::Initialize();

    sf::Vector2f  availableGeometry = sf::Vector2f( float( ::nCore::nApplication::cApplication::App()->Window()->getSize().x ),
                                                    float( ::nCore::nApplication::cApplication::App()->Window()->getSize().y ) );
    double posRatio     = 3./5.;
    double sizeRatio    = 2./5.;
    sf::Vector2f  size      = sf::Vector2f( availableGeometry.x, availableGeometry.y * float(sizeRatio) );
    sf::Vector2f  position  = sf::Vector2f( 0, availableGeometry.y * float(posRatio));
    mConsoleWidget.SetSize( size );
    mConsoleWidget.SetPosition( position );
    mConsoleWidget.ToggleVisibility();


    // Not compatible with input system
    //cGameApplication::App()->Window()->setKeyRepeatEnabled( true );



    std::function< void( void )> f = [=]( void ) {
        ::nCore::nECS::nCore::cEntity* ent = new ::nCore::nECS::nCore::cEntity();
        auto animation = new ::nCore::nECS::nComponent::cAnimations();
        animation->AddSpriteSheetBasedAnimation( "main", "resources/Core/Images/SpriteSheets/communiste_spritesheet.png", 12 );
        animation->CurrentAnimationFrameRate( 24.0 );
        animation->CurrentAnimationIsPaused( false );

        ent->AddComponent( animation );
        sf::Window* window = ::nCore::nApplication::cApplication::App()->Window();
        sf::Vector2u size = window->getSize();
        float posX = float(rand() % ( size.x - 10 ));
        float posY = float(rand() % (size.y - 10));

        ent->AddComponent( new ::nCore::nECS::nComponent::cTransformation( sf::Vector2f( posX, posY ), sf::Vector2f( 0.0F, 0.0F ), 0.0F ) );
        ent->AddComponent( new ::nCore::nECS::nComponent::cUserInput() );
        ent->AddComponent( new ::nCore::nECS::nComponent::cSimplePhysic( 40.0F, 64.0F, ::nCore::nECS::nComponent::cSimplePhysic::eType::kDynamic, false ) );
        mWorld->AddEntityAndPutInLayer( ent, 0 );
    };

    ::nCore::nBoltScript::Env()->RegisterFunction( "newEntity", f );
}


void
cGameScreen::Finalize()
{
    tSuperClass::Finalize();
}


void
cGameScreen::AdditionnalBuildScreen()
{
    mWorld->AddLayer( sf::Vector2f( 800.F, 600.F ), 1.0 );
    mWorld->AddLayer( sf::Vector2f( 800.F, 600.F ), 3.0 );

    mWorld->AddSystem( ::nCore::nRegistries::cSystemRegistry::Instance()->CreateSystemFromName( "SimpleRenderer" ) );
    mWorld->AddSystem( ::nCore::nRegistries::cSystemRegistry::Instance()->CreateSystemFromName( "SquareController" ) );
    mWorld->AddSystem( ::nCore::nRegistries::cSystemRegistry::Instance()->CreateSystemFromName( "SimplePhysics" ) );
    mWorld->AddSystem( ::nCore::nRegistries::cSystemRegistry::Instance()->CreateSystemFromName( "SoundOcclusion" ) );
    mWorld->AddSystem( ::nCore::nRegistries::cSystemRegistry::Instance()->CreateSystemFromName( "InputConverter" ) );

    mWorld->mLayerEngine->LayerDistanceAtIndex( 2, 0 );

    // Shader tests
    ::nCore::nShader::cShader2D* Hblur = new ::nCore::nShader::cShader2D( "BoxBlurHorizontal.frag", "HBlur" );
    ::nCore::nShader::cShader2D* Vblur = new ::nCore::nShader::cShader2D( "BoxBlurVertical.frag", "VBlur" );

    Hblur->SetNewVariable( "blur_radius", ::nCore::nBase::cVariant::MakeVariant( 2.0F ) );
    Vblur->SetNewVariable( "blur_radius", ::nCore::nBase::cVariant::MakeVariant( 2.0F ) );

    Hblur->ApplyUniforms();
    Vblur->ApplyUniforms();

    mWorld->mLayerEngine->AddShaderToLayer( Hblur, 0 );
    mWorld->mLayerEngine->AddShaderToLayer( Vblur, 0 );
    //mWorld->mLayerEngine->AddShaderToLayer( Hblur, 1 );
    //mWorld->mLayerEngine->AddShaderToLayer( Vblur, 1 );
    //mWorld->mLayerEngine->AddShaderToLayer( Hblur, 2 );
    //mWorld->mLayerEngine->AddShaderToLayer( Vblur, 2 );

    ::nCore::nECS::nCore::cEntity* ent = new ::nCore::nECS::nCore::cEntity();
    ent->AddComponent( new ::nCore::nECS::nComponent::cTransformation( sf::Vector2f( 500.0F, 320.0F ), sf::Vector2f( 40.0F, 40.0F ), 0.0F ) );
    ent->AddComponent( new ::nCore::nECS::nComponent::cColor( 255, 0, 0 ) );
    ent->AddComponent( new ::nCore::nECS::nComponent::cUserInput() );
    ent->AddComponent( new ::nCore::nECS::nComponent::cSimplePhysic( 40.0F, 40.0F, ::nCore::nECS::nComponent::cSimplePhysic::eType::kDynamic, false ) );
    ent->AddTag( "listener" );

    mWorld->AddEntityAndPutInLayer( ent, 0 );


    ::nCore::nECS::nCore::cEntity* ent2 = new ::nCore::nECS::nCore::cEntity();
    ent2->AddComponent( new ::nCore::nECS::nComponent::cTransformation( sf::Vector2f( 200.0F, 450.0F ), sf::Vector2f( 40.0F, 40.0F ), 0.0F ) );
    ent2->AddComponent( new ::nCore::nECS::nComponent::cColor( 0, 255, 0 ) );
    ent2->AddComponent( new ::nCore::nECS::nComponent::cSimplePhysic( 40.0F, 40.0F, ::nCore::nECS::nComponent::cSimplePhysic::eType::kStatic, false ) );

    //auto sound = new ::nCore::nECS::nComponent::cSound( "resources/Shared/Audio/kick.wav" );
    //auto sound = new ::nCore::nECS::nComponent::cSound( "resources/Shared/Audio/DryGuitar.wav" );
    auto sound = new ::nCore::nECS::nComponent::cSound( "resources/Shared/Audio/SineWave.wav" );
    sound->Position( sf::Vector3f( 200.0F, 450.0F, 0.0F ) );
    sound->Attenuation( 0.5 );
    sound->Loop( true );
    sound->Play();
    ent2->AddComponent( sound );

    mWorld->AddEntityAndPutInLayer( ent2, 0 );


    ::nCore::nECS::nCore::cEntity* emmiter2 = new ::nCore::nECS::nCore::cEntity();
    emmiter2->AddComponent( new ::nCore::nECS::nComponent::cTransformation( sf::Vector2f( 200.0F, 350.0F ), sf::Vector2f( 40.0F, 40.0F ), 0.0F ) );
    emmiter2->AddComponent( new ::nCore::nECS::nComponent::cColor( 0, 100, 0 ) );
    emmiter2->AddComponent( new ::nCore::nECS::nComponent::cSimplePhysic( 40.0F, 40.0F, ::nCore::nECS::nComponent::cSimplePhysic::eType::kStatic, false ) );

    auto sound2 = new ::nCore::nECS::nComponent::cSound( "resources/Shared/Audio/DryGuitar.wav" );
    sound2->Position( sf::Vector3f( 200.0F, 350.0F, 0.0F ) );
    sound2->Attenuation( 0.01 );
    sound2->Loop( true );
    sound2->Play();
    emmiter2->AddComponent( sound2 );

    mWorld->AddEntityAndPutInLayer( emmiter2, 0 );

    ::nCore::nECS::nCore::cEntity* emmiter3 = new ::nCore::nECS::nCore::cEntity();
    emmiter3->AddComponent( new ::nCore::nECS::nComponent::cTransformation( sf::Vector2f( 400.0F, 350.0F ), sf::Vector2f( 40.0F, 40.0F ), 0.0F ) );
    emmiter3->AddComponent( new ::nCore::nECS::nComponent::cColor( 0, 100, 0 ) );
    emmiter3->AddComponent( new ::nCore::nECS::nComponent::cSimplePhysic( 40.0F, 40.0F, ::nCore::nECS::nComponent::cSimplePhysic::eType::kStatic, false ) );

    auto sound22 = new ::nCore::nECS::nComponent::cSound( "resources/Shared/Audio/Kick.wav" );
    sound22->Position( sf::Vector3f( 400.0F, 350.0F, 0.0F ) );
    sound22->Attenuation( 0.01 );
    sound22->Loop( true );
    sound22->Play();
    emmiter3->AddComponent( sound22 );

    mWorld->AddEntityAndPutInLayer( emmiter3, 0 );

    ::nCore::nECS::nCore::cEntity* wall1 = new ::nCore::nECS::nCore::cEntity();
    wall1->AddComponent( new ::nCore::nECS::nComponent::cTransformation( sf::Vector2f( 420.0F, 400.0F ), sf::Vector2f( 200.0F, 40.0F ), 0.0F ) );
    wall1->AddComponent( new ::nCore::nECS::nComponent::cColor( 0, 150, 255 ) );
    wall1->AddComponent( new ::nCore::nECS::nComponent::cOcclusionFactor( 0.5 ) );
    wall1->AddComponent( new ::nCore::nECS::nComponent::cSimplePhysic( 200.0F, 40.0F, ::nCore::nECS::nComponent::cSimplePhysic::eType::kStatic, false ) );
    mWorld->AddEntityAndPutInLayer( wall1, 0 );


    //int swall = 60;
    int swall = 10;
    //int swall = 5;
    for( int i = 0; i < swall; ++i )
    {
        for( int j = 0; j < swall; ++j )
        {
            ::nCore::nECS::nCore::cEntity* wall = new ::nCore::nECS::nCore::cEntity();
            wall->AddComponent( new ::nCore::nECS::nComponent::cTransformation( sf::Vector2f( float( i ) * 800.0F / float( swall ), float( j ) * 600.0F / float( swall ) ), sf::Vector2f( 5.0F, 5.0F ), 0.0F ) );
            wall->AddComponent( new ::nCore::nECS::nComponent::cColor( 20, 180, 20 ) );
            wall->AddTag( "wall" );
            mWorld->AddEntityAndPutInLayer( wall, 0 );
        }
    }


    int alo = 10;
    for( int j = 0; j < alo; ++j )
    {
        ::nCore::nECS::nCore::cEntity* soundProofing = new ::nCore::nECS::nCore::cEntity();
        soundProofing->AddComponent( new ::nCore::nECS::nComponent::cTransformation( sf::Vector2f( 400.F + float( j ) * 32.F, 450.F ), sf::Vector2f( 31.0F, 31.0F ), 0.0F ) );
        soundProofing->AddComponent( new ::nCore::nECS::nComponent::cColor( 254, 180, 39 ) );
        soundProofing->AddComponent( new ::nCore::nECS::nComponent::cOcclusionFactor( 0.2 ) );
        soundProofing->AddComponent( new ::nCore::nECS::nComponent::cSimplePhysic( 31.0f, 31.F, ::nCore::nECS::nComponent::cSimplePhysic::eType::kStatic, false ) );
        mWorld->AddEntityAndPutInLayer( soundProofing, 0 );
    }

    tSuperClass::AdditionnalBuildScreen();
}


// -------------------------------------------------------------------------------------
// -------------------------------------------------------------- Main Running functions
// -------------------------------------------------------------------------------------


void
cGameScreen::Draw( sf::RenderTarget* iRenderTarget )
{
    tSuperClass::Draw( iRenderTarget );

    auto window = ::nCore::nApplication::cApplication::App()->Window();
    sf::View view = window->getView();
    window->setView( window->getDefaultView() );
    mConsoleWidget.Draw( iRenderTarget );
    window->setView( view );
}


void
cGameScreen::Update( unsigned int iDeltaTime )
{
    tSuperClass::Update( iDeltaTime );
    mConsoleWidget.Update( iDeltaTime );
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------ Events
// -------------------------------------------------------------------------------------


void
cGameScreen::TextEntered( const sf::Event& iEvent )
{
    mConsoleWidget.TextEntered( iEvent );
    tSuperClass::TextEntered( iEvent );
}


void
cGameScreen::KeyPressed( const sf::Event& iEvent )
{
    mConsoleWidget.KeyPressed( iEvent );

    tSuperClass::KeyPressed( iEvent );
}


void
cGameScreen::KeyReleased( const sf::Event& iEvent )
{
    if( iEvent.key.code == sf::Keyboard::Key::K )
    {
        ExportToFile( ::nCore::nApplication::cGlobalAccess::Instance()-> ProjectFolder() + "/GameSave.save" );
    }
    else if( iEvent.key.code == sf::Keyboard::Key::L )
    {
        ImportFromFile( ::nCore::nApplication::cGlobalAccess::Instance()->ProjectFolder() + "/GameSave.save" );
    }

    mConsoleWidget.KeyReleased( iEvent );

    tSuperClass::KeyReleased( iEvent );
}


} // namespace nScreen

