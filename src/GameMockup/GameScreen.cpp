#include "GameScreen.h"

#include "ECS/Entity.h"
#include "ECS/EntityParser.h"
#include "ECS/World.h"

#include "GameMockup/GameApplication.h"
#include "GameMockup/Components/Color.h"
#include "GameMockup/Components/Position.h"
#include "GameMockup/Components/Size.h"
#include "GameMockup/Components/SpriteAnimated.h"
#include "GameMockup/Components/UserInput.h"
#include "GameMockup/Components/SimplePhysic.h"

#include <iostream>

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
    //sf::Window* window = cGameApplication::App()->Window();
    //sf::Vector2u size = window->getSize();

    cWorld* world = cGameApplication::App()->World();

    //for( int i = 0; i < 10; ++i )
    //{
    //    int posX = rand() % ( size.x - 10 );
    //    int posY = rand() % (size.y - 10);

    //    cEntity* ent = new cEntity( world );
    //    cSpriteAnimated* animation = new cSpriteAnimated( "resources/Images/SpriteSheets/communiste_spritesheet.png", 40, 64 );
    //    animation->mFrameRate = 24;
    //    animation->mPaused = false;

    //    ent->AddComponent( animation );
    //    ent->AddComponent( new cPosition( float(posX), float(posY) ) );
    //    world->AddEntity( ent );
    //}

    cEntity* ent = new cEntity( world );
    cSpriteAnimated* animation = new cSpriteAnimated( "resources/Images/SpriteSheets/communiste_spritesheet.png", 40, 64 );
    animation->mFrameRate = 24;
    animation->mPaused = false;

    ent->AddComponent( animation );
    float posX = 400.0F;
    float posY = 300.0F;
    ent->AddComponent( new cPosition( posX, posY ) );
    ent->AddComponent( new cUserInput() );
    ent->AddComponent( new cSimplePhysic( posX, posY, 40.0F, 64.0F, cSimplePhysic::eType::kDynamic ) );
    world->AddEntity( ent );

    cEntity* murtavu = new cEntity( world );
    posX = 500.0F;
    posY = 300.0F;
    murtavu->AddComponent( new cPosition( posX, posY ) );
    murtavu->AddComponent( new cSize( 64.0F, 64.0F ) );
    murtavu->AddComponent( new cColor( 255, 255, 255 ) );
    murtavu->AddComponent( new cSimplePhysic( posX, posY, 64.0F, 64.0F, cSimplePhysic::eType::kStatic ) );
    world->AddEntity( murtavu );

    cEntity* mur2tavu = new cEntity( world );
    posX = 500.0F;
    posY = 235.0F;
    mur2tavu->AddComponent( new cPosition( posX, posY ) );
    mur2tavu->AddComponent( new cSize( 64.0F, 64.0F ) );
    mur2tavu->AddComponent( new cColor( 255, 200, 255 ) );
    mur2tavu->AddComponent( new cSimplePhysic( posX, posY, 64.0F, 64.0F, cSimplePhysic::eType::kStatic ) );
    world->AddEntity( mur2tavu );

    cEntity* mur3tavu = new cEntity( world );
    posX = 200.0;
    posY = 235.0F;
    mur3tavu->AddComponent( new cPosition( posX, posY ) );
    mur3tavu->AddComponent( new cSize( 64.0F, 64.0F ) );
    mur3tavu->AddComponent( new cColor( 255, 200, 255 ) );
    mur3tavu->AddComponent( new cSimplePhysic( posX, posY, 64.0F, 64.0F, cSimplePhysic::eType::kStatic ) );
    world->AddEntity( mur3tavu );

    sf::Vector2f  availableGeometry = sf::Vector2f( float( cGameApplication::App()->Window()->getSize().x ),
                                                    float( cGameApplication::App()->Window()->getSize().y ) );
    double posRatio     = 3./5.;
    double sizeRatio    = 2./5.;
    sf::Vector2f  size      = sf::Vector2f( availableGeometry.x, availableGeometry.y * float(sizeRatio) );
    sf::Vector2f  position  = sf::Vector2f( 0, availableGeometry.y * float(posRatio));
    mConsoleWidget.SetSize( size );
    mConsoleWidget.SetPosition( position );

    // Not compatible with input system
    //cGameApplication::App()->Window()->setKeyRepeatEnabled( true );



    std::function< void( void )> f = [=]( void ) {
        cEntity* ent = new cEntity( world );
        cSpriteAnimated* animation = new cSpriteAnimated( "resources/Images/SpriteSheets/communiste_spritesheet.png", 40, 64 );
        animation->mFrameRate = 24;
        animation->mPaused = false;

        ent->AddComponent( animation );
        sf::Window* window = cGameApplication::App()->Window();
        sf::Vector2u size = window->getSize();
        float posX = float(rand() % ( size.x - 10 ));
        float posY = float(rand() % (size.y - 10));
        ent->AddComponent( new cPosition( posX, posY ) );
        ent->AddComponent( new cUserInput() );
        ent->AddComponent( new cSimplePhysic( posX, posY, 40.0F, 64.0F, cSimplePhysic::eType::kDynamic ) );
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
    mConsoleWidget.Draw( iRenderTarget );
}


void
cGameScreen::Update( unsigned int iDeltaTime )
{
    mConsoleWidget.Update( iDeltaTime );
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------ Events
// -------------------------------------------------------------------------------------


void
cGameScreen::Resized( const sf::Event& iEvent )
{
    // Does nothing
}


void
cGameScreen::TextEntered( const sf::Event& iEvent )
{
    mConsoleWidget.TextEntered( iEvent );
}


void
cGameScreen::KeyPressed( const sf::Event& iEvent )
{
    mConsoleWidget.KeyPressed( iEvent );

}


void
cGameScreen::KeyReleased( const sf::Event& iEvent )
{
    // Does nothing
    if( iEvent.key.code == sf::Keyboard::Key::S )
    {
        SaveXML();
    }
    else if( iEvent.key.code == sf::Keyboard::Key::L )
    {
        LoadXML();
    }
    else if( iEvent.key.code == sf::Keyboard::Key::T )
    {
        cEntity* entity = cEntityParser::Instance()->CreateEntityFromFile( "resources/Entities/test.entity" );
        cGameApplication::App()->World()->AddEntity( entity );
    }
    else if( iEvent.key.code == sf::Keyboard::Key::A )
    {
        cEntity* entity = cEntityParser::Instance()->CreateEntityFromPrototypeMap( "entA" );
        cGameApplication::App()->World()->AddEntity( entity );
    }
    else if( iEvent.key.code == sf::Keyboard::Key::B )
    {
        cEntity* entity = cEntityParser::Instance()->CreateEntityFromPrototypeMap( "entB" );
        cGameApplication::App()->World()->AddEntity( entity );
    }
    else if( iEvent.key.code == sf::Keyboard::Key::C )
    {
        cEntity* entity = cEntityParser::Instance()->CreateEntityFromPrototypeMap( "testUltime" );
        cGameApplication::App()->World()->AddEntity( entity );
    }

    mConsoleWidget.KeyReleased( iEvent );
}


void
cGameScreen::MouseWheelMoved( const sf::Event& iEvent )
{
    // Does nothing
}


void
cGameScreen::MouseWheelScrolled( const sf::Event& iEvent )
{
    // Does nothing
}


void
cGameScreen::MouseButtonPressed( const sf::Event& iEvent )
{
    // Does nothing
}


void
cGameScreen::MouseButtonReleased( const sf::Event& iEvent )
{
}


void
cGameScreen::MouseMoved( const sf::Event& iEvent )
{
    // Does nothing
}


void
cGameScreen::MouseEntered( const sf::Event& iEvent )
{
    // Does nothing
}


void
cGameScreen::MouseLeft( const sf::Event& iEvent )
{
    // Does nothing
}


void
cGameScreen::JoystickButtonPressed( const sf::Event& iEvent )
{
    // Does nothing
}


void
cGameScreen::JoystickButtonReleased( const sf::Event& iEvent )
{
    // Does nothing
}


void
cGameScreen::JoystickMoved( const sf::Event& iEvent )
{
    // Does nothing
}


void
cGameScreen::JoystickConnected( const sf::Event& iEvent )
{
    // Does nothing
}


void
cGameScreen::JoystickDisconnected( const sf::Event& iEvent )
{
    // Does nothing
}


void
cGameScreen::TouchBegan( const sf::Event& iEvent )
{
    // Does nothing
}


void
cGameScreen::TouchMoved( const sf::Event& iEvent )
{
    // Does nothing
}


void
cGameScreen::TouchEnded( const sf::Event& iEvent )
{
    // Does nothing
}


void
cGameScreen::SensorChanged( const sf::Event& iEvent )
{
    // Does nothing
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------ Input/Output
// -------------------------------------------------------------------------------------

void
cGameScreen::SaveXML()
{
    tinyxml2::XMLDocument doc;
    tinyxml2::XMLElement* elm = doc.NewElement( "world" );

    cGameApplication::App()->World()->SaveXML( elm, &doc );

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

    cGameApplication::App()->World()->LoadXML( doc.FirstChildElement( "world" ) );

    if( !error )
        std::cout << "Successfuly loaded " << std::endl;
    else
        std::cout << "Failed to load" << std::endl;
}






