#include "GameMockup.Screen.GameScreen.h"


#include "Core.ECS.Core.Entity.h"
#include "Core.ECS.Utilities.EntityParser.h"
#include "Core.ECS.Utilities.SystemRegistry.h"
#include "Core.ECS.Core.World.h"

#include "Core.ECS.Component.Color.h"
#include "Core.ECS.Component.OcclusionFactor.h"
#include "Core.ECS.Component.Position.h"
#include "Core.ECS.Component.SimplePhysic.h"
#include "Core.ECS.Component.Sound.h"
#include "Core.ECS.Component.Size.h"
#include "Core.ECS.Component.SpriteAnimated.h"
#include "Core.ECS.Component.UserInput.h"
#include "Core.ECS.Component.ZDepth.h"

#include "GameMockup.ECS.System.SquareController.h"

#include "GameMockup.Application.GameApplication.h"

#include "Core.Render.LayerEngine.h"

#include "SFML/Audio.hpp"


#include <iostream>


namespace nScreen {


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------ Construction
// -------------------------------------------------------------------------------------


cGameScreen::~cGameScreen()
{
}


cGameScreen::cGameScreen()
{
}


// -------------------------------------------------------------------------------------
// ----------------------------------------------------------------------- Init/Finalize
// -------------------------------------------------------------------------------------


void
cGameScreen::Initialize()
{
    tSuperClass::Initialize();

    ::nECS::cWorld* world = mWorld;
    world->SetUseLayerEngine( true );  // 114 FPS average without layers ; 103 with layers
    world->AddLayer( sf::Vector2f( 800.F, 600.F ) );
    world->AddLayer( sf::Vector2f( 800.F, 600.F ) );

    world->AddSystem( ::nECS::cSystemRegistry::Instance()->GetSystemByName( "SimpleRenderer" ) );
    world->AddSystem( ::nECS::cSystemRegistry::Instance()->GetSystemByName( "SquareController" ) );
    world->AddSystem( ::nECS::cSystemRegistry::Instance()->GetSystemByName( "SimplePhysics" ) );
    world->AddSystem( ::nECS::cSystemRegistry::Instance()->GetSystemByName( "SoundOcclusion" ) );

    auto inputConverter = ::nECS::cSystemRegistry::Instance()->GetSystemByName( "InputConverter" );
    world->AddSystem( inputConverter );
    world->ConnectSystemToEvents( inputConverter );

    world->mLayerEngine->LayerDistanceAtIndex( 2, 0 );

    // Shader tests
    sf::Shader* Hblur = new sf::Shader;
    sf::Shader* Vblur = new sf::Shader;
    if( !Hblur->loadFromFile( "resources/Shared/Shaders/BoxBlurHorizontal.frag", sf::Shader::Fragment ) )
        int breakpoint = 1;
    if( !Vblur->loadFromFile( "resources/Shared/Shaders/BoxBlurVertical.frag", sf::Shader::Fragment ) )
        int breakpoint = 1;

    Hblur->setUniform( "blur_radius", 2.0F );
    Vblur->setUniform( "blur_radius", 2.0F );

    world->mLayerEngine->AddShaderToLayer( Hblur, 0 );
    world->mLayerEngine->AddShaderToLayer( Vblur, 0 );
    //world->mLayerEngine->AddShaderToLayer( Hblur, 1 );
    //world->mLayerEngine->AddShaderToLayer( Vblur, 1 );
    //world->mLayerEngine->AddShaderToLayer( Hblur, 2 );
    //world->mLayerEngine->AddShaderToLayer( Vblur, 2 );

    ::nECS::cEntity* ent = new ::nECS::cEntity();
    ent->AddComponent( new ::nECS::cPosition( 500.0F, 320.0F ) );
    ent->AddComponent( new ::nECS::cSize( 40.0F, 40.0F ) );
    ent->AddComponent( new ::nECS::cColor( 255,0,0 ) );
    ent->AddComponent( new ::nECS::cUserInput() );
    ent->AddComponent( new ::nECS::cSimplePhysic( 40.0F, 40.0F, ::nECS::cSimplePhysic::eType::kDynamic ) );
    ent->AddTag( "listener" );

    world->AddEntity( ent );
    world->PutEntityInLayer( ent, 2 );


    ::nECS::cEntity* ent2 = new ::nECS::cEntity();
    ent2->AddComponent( new ::nECS::cPosition( 200.0F, 450.0F ) );
    ent2->AddComponent( new ::nECS::cSize( 40.0F, 40.0F ) );
    ent2->AddComponent( new ::nECS::cColor( 0, 255, 0 ) );
    ent2->AddComponent( new ::nECS::cSimplePhysic( 40.0F, 40.0F, ::nECS::cSimplePhysic::eType::kStatic ) );

    //auto sound = new ::nECS::cSound( "resources/Shared/Audio/kick.wav" );
    //auto sound = new ::nECS::cSound( "resources/Shared/Audio/DryGuitar.wav" );
    auto sound = new ::nECS::cSound( "resources/Shared/Audio/SineWave.wav" );
    sound->Position( sf::Vector3f( 200.0F, 450.0F, 0.0F ) );
    sound->Attenuation( 0.5 );
    sound->Loop( true );
    sound->Play();
    ent2->AddComponent( sound );

    world->AddEntity( ent2 );
    world->PutEntityInLayer( ent2, 1 );


    ::nECS::cEntity* emmiter2 = new ::nECS::cEntity();
    emmiter2->AddComponent( new ::nECS::cPosition( 200.0F, 350.0F ) );
    emmiter2->AddComponent( new ::nECS::cSize( 40.0F, 40.0F ) );
    emmiter2->AddComponent( new ::nECS::cColor( 0, 100, 0 ) );
    emmiter2->AddComponent( new ::nECS::cSimplePhysic( 40.0F, 40.0F, ::nECS::cSimplePhysic::eType::kStatic ) );

    auto sound2 = new ::nECS::cSound( "resources/Shared/Audio/DryGuitar.wav" );
    sound2->Position( sf::Vector3f( 200.0F, 350.0F, 0.0F ) );
    sound2->Attenuation( 0.01 );
    sound2->Loop( true );
    sound2->Play();
    emmiter2->AddComponent( sound2 );

    world->AddEntity( emmiter2 );
    world->PutEntityInLayer( emmiter2, 1 );

    ::nECS::cEntity* emmiter3 = new ::nECS::cEntity();
    emmiter3->AddComponent( new ::nECS::cPosition( 400.0F, 350.0F ) );
    emmiter3->AddComponent( new ::nECS::cSize( 40.0F, 40.0F ) );
    emmiter3->AddComponent( new ::nECS::cColor( 0, 100, 0 ) );
    emmiter3->AddComponent( new ::nECS::cSimplePhysic( 40.0F, 40.0F, ::nECS::cSimplePhysic::eType::kStatic ) );

    auto sound22 = new ::nECS::cSound( "resources/Shared/Audio/Kick.wav" );
    sound22->Position( sf::Vector3f( 400.0F, 350.0F, 0.0F ) );
    sound22->Attenuation( 0.01 );
    sound22->Loop( true );
    sound22->Play();
    emmiter3->AddComponent( sound22 );

    world->AddEntity( emmiter3 );
    world->PutEntityInLayer( emmiter3, 1 );

    ::nECS::cEntity* wall = new ::nECS::cEntity();
    wall->AddComponent( new ::nECS::cPosition( 420.0F, 400.0F ) );
    wall->AddComponent( new ::nECS::cSize( 200.0F, 40.0F ) );
    wall->AddComponent( new ::nECS::cColor( 0, 150, 255 ) );
    wall->AddComponent( new ::nECS::cOcclusionFactor( 0.5 ) );
    wall->AddComponent( new ::nECS::cSimplePhysic( 200.0F, 40.0F, ::nECS::cSimplePhysic::eType::kStatic ) );
    world->AddEntity( wall );
    world->PutEntityInLayer( wall, 1 );


    //int swall = 60;
    int swall = 10;
    //int swall = 5;
    for( int i = 0; i < swall; ++i )
    {
        for( int j = 0; j < swall; ++j )
        {
            ::nECS::cEntity* wall = new ::nECS::cEntity();
            wall->AddComponent( new ::nECS::cPosition( float( i ) * 800.0F / float( swall ), float( j ) * 600.0F / float( swall ) ) );
            wall->AddComponent( new ::nECS::cSize( 5.0f, 5.0f ) );
            wall->AddComponent( new ::nECS::cColor( 20, 180, 20 ) );
            wall->AddTag( "wall" );
            world->AddEntity( wall );
            world->PutEntityInLayer( wall, 0 );
        }
    }


    int alo = 10;
    for( int j = 0; j < alo; ++j )
    {
        ::nECS::cEntity* soundProofing = new ::nECS::cEntity();
        soundProofing->AddComponent( new ::nECS::cPosition( sf::Vector2f( 400.F + float(j) * 32.F, 450.F ) ) );
        soundProofing->AddComponent( new ::nECS::cSize( 31.0f, 31.F ) );
        soundProofing->AddComponent( new ::nECS::cColor( 254, 180, 39 ) );
        soundProofing->AddComponent( new ::nECS::cOcclusionFactor( 0.2 ) );
        soundProofing->AddComponent( new ::nECS::cSimplePhysic( 31.0f, 31.F, ::nECS::cSimplePhysic::eType::kStatic ) );
        world->AddEntity( soundProofing );
        world->PutEntityInLayer( soundProofing, 2 );
    }


    sf::Vector2f  availableGeometry = sf::Vector2f( float( ::nApplication::cGameApplication::App()->Window()->getSize().x ),
                                                    float( ::nApplication::cGameApplication::App()->Window()->getSize().y ) );
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
        ::nECS::cEntity* ent = new ::nECS::cEntity();
        ::nECS::cSpriteAnimated* animation = new ::nECS::cSpriteAnimated( "resources/Core/Images/SpriteSheets/communiste_spritesheet.png", 40, 64 );
        animation->Framerate( 24.0 );
        animation->Paused( false );

        ent->AddComponent( animation );
        sf::Window* window = ::nApplication::cGameApplication::App()->Window();
        sf::Vector2u size = window->getSize();
        float posX = float(rand() % ( size.x - 10 ));
        float posY = float(rand() % (size.y - 10));
        ent->AddComponent( new ::nECS::cPosition( posX, posY ) );
        ent->AddComponent( new ::nECS::cUserInput() );
        ent->AddComponent( new ::nECS::cSimplePhysic( 40.0F, 64.0F, ::nECS::cSimplePhysic::eType::kDynamic ) );
        world->AddEntity( ent );
    };

    ::nBoltScript::Env()->RegisterFunction( "newEntity", f );
}


void
cGameScreen::Finalize()
{

}


// -------------------------------------------------------------------------------------
// -------------------------------------------------------------- Main Running functions
// -------------------------------------------------------------------------------------


void
cGameScreen::Draw( sf::RenderTarget* iRenderTarget )
{
    tSuperClass::Draw( iRenderTarget );

    auto window = ::nApplication::cGameApplication::App()->Window();
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
    // Does nothing
    if( iEvent.key.code == sf::Keyboard::Key::K )
    {
        SaveXML();
    }
    //else if( iEvent.key.code == sf::Keyboard::Key::T )
    //{
    //    ::nECS::cEntity* entity = ::nECS::cEntityParser::Instance()->CreateEntityFromFile( "resources/Core/Entities/test.entity", ::nApplication::cGameApplication::App()->World() );
    //    ::nApplication::cGameApplication::App()->World()->AddEntity( entity );
    //}
    //else if( iEvent.key.code == sf::Keyboard::Key::A )
    //{
    //    ::nECS::cEntity* entity = ::nECS::cEntityParser::Instance()->CreateEntityFromPrototypeMap( "entA" );
    //    ::nApplication::cGameApplication::App()->World()->AddEntity( entity );
    //}
    //else if( iEvent.key.code == sf::Keyboard::Key::B )
    //{
    //    ::nECS::cEntity* entity = ::nECS::cEntityParser::Instance()->CreateEntityFromPrototypeMap( "entB" );
    //    ::nApplication::cGameApplication::App()->World()->AddEntity( entity );
    //}
    //else if( iEvent.key.code == sf::Keyboard::Key::C )
    //{
    //    ::nECS::cEntity* entity = ::nECS::cEntityParser::Instance()->CreateEntityFromPrototypeMap( "testUltime" );
    //    ::nApplication::cGameApplication::App()->World()->AddEntity( entity );
    //}

    mConsoleWidget.KeyReleased( iEvent );

    tSuperClass::KeyReleased( iEvent );
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------ Input/Output
// -------------------------------------------------------------------------------------

void
cGameScreen::SaveXML()
{
    tinyxml2::XMLDocument doc;
    tinyxml2::XMLElement* elm = doc.NewElement( "world" );

    ::nApplication::cGameApplication::App()->World()->SaveXML( elm, &doc );

    doc.InsertFirstChild( elm );

    tinyxml2::XMLError error = doc.SaveFile( "test.xml" );
    if( error )
    {
        std::cout << "Heh, couldn't save ..." << std::endl;
    }
}


void
cGameScreen::LoadXML()
{
    tinyxml2::XMLDocument doc;
    tinyxml2::XMLError error = doc.LoadFile( "test.xml" );

    ::nApplication::cGameApplication::App()->World()->LoadXML( doc.FirstChildElement( "world" ) );

    if( !error )
        std::cout << "Successfuly loaded " << std::endl;
    else
        std::cout << "Failed to load" << std::endl;
}


} // namespace nScreen

