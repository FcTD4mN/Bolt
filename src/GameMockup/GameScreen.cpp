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
    sf::Window* window = cGameApplication::App()->Window();
    sf::Vector2u size = window->getSize();

    cWorld* world = cGameApplication::App()->World();
    for( int i = 0; i < 10; ++i )
    {
        int posX = rand() % ( size.x - 10 );
        int posY = rand() % (size.y - 10);

        cEntity* ent = new cEntity( world );
        cSpriteAnimated* animation = new cSpriteAnimated( "resources/Images/SpriteSheets/communiste_spritesheet.png", 40, 64 );
        animation->mFrameRate = 24;
        animation->mPaused = false;

        ent->AddComponent( animation );
        ent->AddComponent( new cPosition( float(posX), float(posY) ) );
        world->AddEntity( ent );
    }

    cEntity* ent = new cEntity( world );
    cSpriteAnimated* animation = new cSpriteAnimated( "resources/Images/SpriteSheets/communiste_spritesheet.png", 40, 64 );
    animation->mFrameRate = 24;
    animation->mPaused = false;

    ent->AddComponent( animation );
    ent->AddComponent( new cPosition( 400.0, 300.0 ) );
    ent->AddComponent( new cUserInput() );
    world->AddEntity( ent );

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
}


void
cGameScreen::Update( unsigned int iDeltaTime )
{
    // Does nothing
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
cGameScreen::KeyPressed( const sf::Event& iEvent )
{
    // Does nothing

}


void
cGameScreen::KeyReleased( const sf::Event& iEvent )
{
    // Does nothing
    cEntityParser::CreateEntityFromFile( "resources/Entities/test.entity" );
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





