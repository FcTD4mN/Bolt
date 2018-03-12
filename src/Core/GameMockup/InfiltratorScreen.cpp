#include "InfiltratorScreen.h"

#include "ECS/Core/Entity.h"
#include "ECS/Utilities/EntityParser.h"
#include "ECS/Core/World.h"

#include "GameMockup/GameApplication.h"
#include "GameMockup/Components/Color.h"
#include "GameMockup/Components/Direction.h"
#include "GameMockup/Components/FieldOfView.h"
#include "GameMockup/Components/Position.h"
#include "GameMockup/Components/Size.h"
#include "GameMockup/Components/SpriteAnimated.h"
#include "GameMockup/Components/UserInput.h"
#include "GameMockup/Components/SimplePhysic.h"

#include <iostream>

// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------ Construction
// -------------------------------------------------------------------------------------


cInfiltratorScreen::~cInfiltratorScreen()
{
}


cInfiltratorScreen::cInfiltratorScreen()
{
}


// -------------------------------------------------------------------------------------
// ----------------------------------------------------------------------- Init/Finalize
// -------------------------------------------------------------------------------------


void
cInfiltratorScreen::Initialize()
{
    sf::Window* window = cGameApplication::App()->Window();
    sf::Vector2u windowSize = window->getSize();

    cWorld* world = cGameApplication::App()->World();

    cEntity* wall1 = new cEntity( world );
    wall1->AddComponent( new cPosition( 0.0F, 0.0F ) );
    wall1->AddComponent( new cSize( 64.0F, 64.0F ) );
    wall1->AddComponent( new cColor( 20, 180, 20 ) );
    wall1->AddTag( "wall" );
    wall1->AddComponent( new cSimplePhysic( 0.0F, 0.0F, 64.0F, 64.0F, cSimplePhysic::eType::kStatic ) );
    world->AddEntity( wall1 );

    cEntity* wall2 = new cEntity( world );
    wall2->AddComponent( new cPosition( 124.0F, 124.0F ) );
    wall2->AddComponent( new cSize( 256.0F, 64.0F ) );
    wall2->AddComponent( new cColor( 20, 180, 20 ) );
    wall2->AddTag( "wall" );
    wall2->AddComponent( new cSimplePhysic( 124.0F, 124.0F, 256.0F, 64.0F, cSimplePhysic::eType::kStatic ) );
    world->AddEntity( wall2 );

    cEntity* wall3 = new cEntity( world );
    wall3->AddComponent( new cPosition( 60.0F, 250.0F ) );
    wall3->AddComponent( new cSize( 64.0F, 64.0F ) );
    wall3->AddComponent( new cColor( 20, 180, 20 ) );
    wall3->AddTag( "wall" );
    wall3->AddComponent( new cSimplePhysic( 60.0F, 250.0F, 64.0F, 64.0F, cSimplePhysic::eType::kStatic ) );
    world->AddEntity( wall3 );

    cEntity* wall4 = new cEntity( world );
    wall4->AddComponent( new cPosition( 450.0F, 200.0F ) );
    wall4->AddComponent( new cSize( 64.0F, 256.0F ) );
    wall4->AddComponent( new cColor( 20, 180, 20 ) );
    wall4->AddTag( "wall" );
    wall4->AddComponent( new cSimplePhysic( 450.0F, 200.0F, 64.0F, 256.0F, cSimplePhysic::eType::kStatic ) );
    world->AddEntity( wall4 );

    cEntity* hero = new cEntity( world );
    hero->AddComponent( new cPosition( 124.0F, 64.0F ) );
    hero->AddComponent( new cSize( 40.0F, 60.0F ) );
    hero->AddComponent( new cColor( 20, 20, 200 ) );
    hero->AddComponent( new cUserInput() );
    hero->AddTag( "hero" );
    hero->AddComponent( new cSimplePhysic( 124.0F, 64.0F, 40.0F, 60.0F, cSimplePhysic::eType::kDynamic ) );
    world->AddEntity( hero );

    mMechant = new cEntity( world );
    mMechant->AddComponent( new cPosition( 156.0F, 256.0F ) );
    mMechant->AddComponent( new cSize( 40.0F, 40.0F ) );
    mMechant->AddComponent( new cColor( 180, 20, 20 ) );
    mMechant->AddComponent( new cFieldOfView( 90, 500 ) );
    mMechant->AddComponent( new cDirection( sf::Vector2f( 1.0F, 1.0F ) ) );
    mMechant->AddComponent( new cSimplePhysic( 156.0F, 256.0F, 40.0F, 40.0F, cSimplePhysic::eType::kDynamic ) );
    world->AddEntity( mMechant );

    mRotationFOV.rotate( 1.0F );

    sf::Vector2f  availableGeometry = sf::Vector2f( float( cGameApplication::App()->Window()->getSize().x ),
                                                    float( cGameApplication::App()->Window()->getSize().y ) );
    double posRatio     = 3./5.;
    double sizeRatio    = 2./5.;
    sf::Vector2f  size      = sf::Vector2f( availableGeometry.x, availableGeometry.y * float(sizeRatio) );
    sf::Vector2f  position  = sf::Vector2f( 0, availableGeometry.y * float(posRatio));
    mConsoleWidget.SetSize( size );
    mConsoleWidget.SetPosition( position );
}


void
cInfiltratorScreen::Finalize()
{

}


// -------------------------------------------------------------------------------------
// -------------------------------------------------------------- Main Running functions
// -------------------------------------------------------------------------------------


void
cInfiltratorScreen::Draw( sf::RenderTarget* iRenderTarget )
{
    auto window = cGameApplication::App()->Window();
    sf::View view = window->getView();
    window->setView( window->getDefaultView() );
    mConsoleWidget.Draw( iRenderTarget );
    window->setView( view );
}


void
cInfiltratorScreen::Update( unsigned int iDeltaTime )
{
    mConsoleWidget.Update( iDeltaTime );
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------ Events
// -------------------------------------------------------------------------------------


void
cInfiltratorScreen::Resized( const sf::Event& iEvent )
{
    // Does nothing
}


void
cInfiltratorScreen::TextEntered( const sf::Event& iEvent )
{
    mConsoleWidget.TextEntered( iEvent );
}


void
cInfiltratorScreen::KeyPressed( const sf::Event& iEvent )
{
    mConsoleWidget.KeyPressed( iEvent );

}


void
cInfiltratorScreen::KeyReleased( const sf::Event& iEvent )
{
    // Does nothing
    if( iEvent.key.code == sf::Keyboard::Key::X )
    {
        auto direction = dynamic_cast< cDirection* >( mMechant->GetComponentByName( "direction" ) );
        direction->mDirection = mRotationFOV.transformPoint( direction->mDirection );
    }
    else if( iEvent.key.code == sf::Keyboard::Key::C )
    {
        auto direction = dynamic_cast< cDirection* >( mMechant->GetComponentByName( "direction" ) );
        mRotationFOV = mRotationFOV.getInverse();
        direction->mDirection = mRotationFOV.transformPoint( direction->mDirection );
        mRotationFOV = mRotationFOV.getInverse();
    }
    mConsoleWidget.KeyReleased( iEvent );
}


void
cInfiltratorScreen::MouseWheelMoved( const sf::Event& iEvent )
{
    // Does nothing
}


void
cInfiltratorScreen::MouseWheelScrolled( const sf::Event& iEvent )
{
    // Does nothing
}


void
cInfiltratorScreen::MouseButtonPressed( const sf::Event& iEvent )
{
    // Does nothing
}


void
cInfiltratorScreen::MouseButtonReleased( const sf::Event& iEvent )
{
}


void
cInfiltratorScreen::MouseMoved( const sf::Event& iEvent )
{
    // Does nothing
}


void
cInfiltratorScreen::MouseEntered( const sf::Event& iEvent )
{
    // Does nothing
}


void
cInfiltratorScreen::MouseLeft( const sf::Event& iEvent )
{
    // Does nothing
}


void
cInfiltratorScreen::JoystickButtonPressed( const sf::Event& iEvent )
{
    // Does nothing
}


void
cInfiltratorScreen::JoystickButtonReleased( const sf::Event& iEvent )
{
    // Does nothing
}


void
cInfiltratorScreen::JoystickMoved( const sf::Event& iEvent )
{
    // Does nothing
}


void
cInfiltratorScreen::JoystickConnected( const sf::Event& iEvent )
{
    // Does nothing
}


void
cInfiltratorScreen::JoystickDisconnected( const sf::Event& iEvent )
{
    // Does nothing
}


void
cInfiltratorScreen::TouchBegan( const sf::Event& iEvent )
{
    // Does nothing
}


void
cInfiltratorScreen::TouchMoved( const sf::Event& iEvent )
{
    // Does nothing
}


void
cInfiltratorScreen::TouchEnded( const sf::Event& iEvent )
{
    // Does nothing
}


void
cInfiltratorScreen::SensorChanged( const sf::Event& iEvent )
{
    // Does nothing
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------ Input/Output
// -------------------------------------------------------------------------------------

void
cInfiltratorScreen::SaveXML()
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
cInfiltratorScreen::LoadXML()
{
    tinyxml2::XMLDocument doc;
    tinyxml2::XMLError error = doc.LoadFile( "test.xml" );

    cGameApplication::App()->World()->LoadXML( doc.FirstChildElement( "world" ) );

    if( !error )
        std::cout << "Successfuly loaded " << std::endl;
    else
        std::cout << "Failed to load" << std::endl;
}






