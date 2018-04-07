#include "GameScreen.h"

#include "ECS/Core/Entity.h"
#include "ECS/Utilities/EntityParser.h"
#include "ECS/Core/World.h"

#include "ECS/BasicComponents/Color.h"
#include "ECS/BasicComponents/Position.h"
#include "ECS/BasicComponents/SimplePhysic.h"
#include "ECS/BasicComponents/Size.h"
#include "ECS/BasicComponents/SpriteAnimated.h"
#include "ECS/BasicComponents/UserInput.h"

#include "GameMockup/GameApplication.h"

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
    sf::Window* window = ::nApplication::cGameApplication::App()->Window();
    sf::Vector2u windowSize = window->getSize();

    ::nECS::cWorld* world = ::nApplication::cGameApplication::App()->World();

    for( int i = 0; i < 500; ++i )
    {
        int posX = rand() % ( windowSize.x - 10 );
        int posY = rand() % (windowSize.y - 10);

        ::nECS::cEntity* ent = new ::nECS::cEntity( world );
        ent->AddComponent( new ::nECS::cSize( 2.0F, 2.0F ) );
        ent->AddComponent( new ::nECS::cColor( 255, 20, 20 ) );
        ent->AddComponent( new ::nECS::cPosition( float(posX), float(posY) ) );
        ent->AddComponent( new ::nECS::cSimplePhysic( float( posX ), float( posY ), 2.0F, 2.0F, ::nECS::cSimplePhysic::eType::kDynamic ) );
        world->AddEntity( ent );
    }

    ::nECS::cEntity* ent = new ::nECS::cEntity( world );
    ent->AddComponent( new ::nECS::cPosition( 400.0F, 300.0F ) );
    ent->AddComponent( new ::nECS::cSize( 5.0F, 5.0F ) );
    ent->AddComponent( new ::nECS::cColor( 20,255,20 ) );
    ent->AddComponent( new ::nECS::cUserInput() );
    ent->AddComponent( new ::nECS::cSimplePhysic( 400.0F, 300.0F, 5.0F, 5.0F, ::nECS::cSimplePhysic::eType::kDynamic ) );
    world->AddEntity( ent );

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
        ::nECS::cEntity* ent = new ::nECS::cEntity( world );
        ::nECS::cSpriteAnimated* animation = new ::nECS::cSpriteAnimated( "resources/Core/Images/SpriteSheets/communiste_spritesheet.png", 40, 64 );
        animation->mFrameRate = 24;
        animation->mPaused = false;

        ent->AddComponent( animation );
        sf::Window* window = ::nApplication::cGameApplication::App()->Window();
        sf::Vector2u size = window->getSize();
        float posX = float(rand() % ( size.x - 10 ));
        float posY = float(rand() % (size.y - 10));
        ent->AddComponent( new ::nECS::cPosition( posX, posY ) );
        ent->AddComponent( new ::nECS::cUserInput() );
        ent->AddComponent( new ::nECS::cSimplePhysic( posX, posY, 40.0F, 64.0F, ::nECS::cSimplePhysic::eType::kDynamic ) );
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
    auto window = ::nApplication::cGameApplication::App()->Window();
    sf::View view = window->getView();
    window->setView( window->getDefaultView() );
    mConsoleWidget.Draw( iRenderTarget );
    window->setView( view );
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
    else if( iEvent.key.code == sf::Keyboard::Key::T )
    {
        ::nECS::cEntity* entity = ::nECS::cEntityParser::Instance()->CreateEntityFromFile( "resources/Core/Entities/test.entity", ::nApplication::cGameApplication::App()->World() );
        ::nApplication::cGameApplication::App()->World()->AddEntity( entity );
    }
    else if( iEvent.key.code == sf::Keyboard::Key::A )
    {
        ::nECS::cEntity* entity = ::nECS::cEntityParser::Instance()->CreateEntityFromPrototypeMap( "entA" );
        ::nApplication::cGameApplication::App()->World()->AddEntity( entity );
    }
    else if( iEvent.key.code == sf::Keyboard::Key::B )
    {
        ::nECS::cEntity* entity = ::nECS::cEntityParser::Instance()->CreateEntityFromPrototypeMap( "entB" );
        ::nApplication::cGameApplication::App()->World()->AddEntity( entity );
    }
    else if( iEvent.key.code == sf::Keyboard::Key::C )
    {
        ::nECS::cEntity* entity = ::nECS::cEntityParser::Instance()->CreateEntityFromPrototypeMap( "testUltime" );
        ::nApplication::cGameApplication::App()->World()->AddEntity( entity );
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

} //nScreen




