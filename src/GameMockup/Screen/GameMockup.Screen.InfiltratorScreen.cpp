#include "GameMockup.Screen.InfiltratorScreen.h"


#include "Core.ECS.Core.Entity.h"
#include "Core.ECS.Core.World.h"
#include "Core.ECS.Utilities.EntityParser.h"

#include "Core.ECS.Component.Color.h"
#include "Core.ECS.Component.Direction.h"
#include "Core.ECS.Component.Position.h"
#include "Core.ECS.Component.FieldOfView.h"
#include "Core.ECS.Component.SimplePhysic.h"
#include "Core.ECS.Component.Size.h"
#include "Core.ECS.Component.SpriteAnimated.h"
#include "Core.ECS.Component.UserInput.h"

#include "Core.Math.Utils.h"

#include "GameMockup.Application.GameApplication.h"



#include <iostream>


namespace nScreen {


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
    sf::Window* window = ::nApplication::cGameApplication::App()->Window();
    sf::Vector2u windowSize = window->getSize();

    ::nECS::cWorld* world = ::nApplication::cGameApplication::App()->World();

    ::nECS::cEntity* wall1 = new ::nECS::cEntity( world );
    wall1->AddComponent( new ::nECS::cPosition( 0.0F, 500.0F ) );
    wall1->AddComponent( new ::nECS::cSize( 800.0F, 100.0F ) );
    wall1->AddComponent( new ::nECS::cColor( 180, 185, 183 ) );
    wall1->AddTag( "wall" );
    wall1->AddComponent( new ::nECS::cSimplePhysic( 0.0F, 500.0F, 800.0F, 100.0F, ::nECS::cSimplePhysic::eType::kStatic ) );
    world->AddEntity( wall1 );

    //cEntity* wall2 = new cEntity( world );
    //wall2->AddComponent( new cPosition( 124.0F, 124.0F ) );
    //wall2->AddComponent( new cSize( 256.0F, 64.0F ) );
    //wall2->AddComponent( new cColor( 20, 180, 20 ) );
    //wall2->AddTag( "wall" );
    //wall2->AddComponent( new cSimplePhysic( 124.0F, 124.0F, 256.0F, 64.0F, cSimplePhysic::eType::kStatic ) );
    //world->AddEntity( wall2 );

    //cEntity* wall3 = new cEntity( world );
    //wall3->AddComponent( new cPosition( 60.0F, 250.0F ) );
    //wall3->AddComponent( new cSize( 64.0F, 64.0F ) );
    //wall3->AddComponent( new cColor( 20, 180, 20 ) );
    //wall3->AddTag( "wall" );
    //wall3->AddComponent( new cSimplePhysic( 60.0F, 250.0F, 64.0F, 64.0F, cSimplePhysic::eType::kStatic ) );
    //world->AddEntity( wall3 );

    //cEntity* wall4 = new cEntity( world );
    //wall4->AddComponent( new cPosition( 450.0F, 200.0F ) );
    //wall4->AddComponent( new cSize( 64.0F, 256.0F ) );
    //wall4->AddComponent( new cColor( 20, 180, 20 ) );
    //wall4->AddTag( "wall" );
    //wall4->AddComponent( new cSimplePhysic( 450.0F, 200.0F, 64.0F, 256.0F, cSimplePhysic::eType::kStatic ) );
    //world->AddEntity( wall4 );

    ::nECS::cEntity* hero = new ::nECS::cEntity( world );
    hero->AddComponent( new ::nECS::cPosition( 350.0F, 350.0F ) );
    hero->AddComponent( new ::nECS::cSize( 100.0F, 90.0F ) );
    hero->AddComponent( new ::nECS::cColor( 20, 20, 200 ) );
    hero->AddComponent( new ::nECS::cUserInput() );
    hero->AddTag( "hero" );
    hero->AddComponent( new ::nECS::cSimplePhysic( 350.0F, 350.0F, 100.0F, 90.0F, ::nECS::cSimplePhysic::eType::kDynamic ) );
    world->AddEntity( hero );

    mMechant = new ::nECS::cEntity( world );
    mMechant->AddComponent( new ::nECS::cPosition( 150.0F, 100.0F ) );
    mMechant->AddComponent( new ::nECS::cSize( 1.0F, 1.0F ) );
    mMechant->AddComponent( new ::nECS::cColor( 180, 20, 20 ) );
    mMechant->AddComponent( new ::nECS::cFieldOfView( 90, 1000 ) );
    mMechant->AddComponent( new ::nECS::cDirection( ::nMath::Normale( sf::Vector2f( 0.0F, 1.0F ) ) ) );
    mMechant->AddComponent( new ::nECS::cSimplePhysic( 150.0F, 100.0F, 1.0F, 1.0F, ::nECS::cSimplePhysic::eType::kDynamic ) );
    world->AddEntity( mMechant );

    ::nECS::cEntity* light = new ::nECS::cEntity( world );
    light->AddComponent( new ::nECS::cPosition( 650.0F, 100.0F ) );
    light->AddComponent( new ::nECS::cSize( 1.0F, 1.0F ) );
    light->AddComponent( new ::nECS::cColor( 180, 20, 20 ) );
    light->AddComponent( new ::nECS::cFieldOfView( 90, 1000 ) );
    light->AddComponent( new ::nECS::cDirection( ::nMath::Normale( sf::Vector2f( 0.0F, 1.0F ) ) ) );
    light->AddComponent( new ::nECS::cSimplePhysic( 650.0F, 100.0F, 1.0F, 1.0F, ::nECS::cSimplePhysic::eType::kDynamic ) );
    world->AddEntity( light );

    int swall = 5;
    for( int i = 0; i < swall; ++i )
    {
        for( int j = 0; j < swall; ++j )
        {
            ::nECS::cEntity* wall = new ::nECS::cEntity( world );
            wall->AddComponent( new ::nECS::cPosition( float(i) * 800.0F / float( swall ), float( j ) * 600.0F / float( swall ) ) );
            wall->AddComponent( new ::nECS::cSize( 5.0f, 5.0f ) );
            wall->AddComponent( new ::nECS::cColor( 20, 180, 20 ) );
            wall->AddComponent( new ::nECS::cSimplePhysic( float( i ) * 800.0F / float( swall ), float( j ) * 600.0F / float( swall ), 5.0f, 5.0f, ::nECS::cSimplePhysic::eType::kDynamic ) );
            wall->AddTag( "wall" );
            world->AddEntity( wall );
        }
    }

    mRotationFOV.rotate( 2.0F );
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
}


void
cInfiltratorScreen::Update( unsigned int iDeltaTime )
{
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
}


void
cInfiltratorScreen::KeyPressed( const sf::Event& iEvent )
{
    if( iEvent.key.code == sf::Keyboard::Key::X )
    {
        auto direction = dynamic_cast< ::nECS::cDirection* >( mMechant->GetComponentByName( "direction" ) );
        direction->SetUsingVector( mRotationFOV.transformPoint( direction->AsVector2F() ) );
    }
    else if( iEvent.key.code == sf::Keyboard::Key::C )
    {
        auto direction = dynamic_cast< ::nECS::cDirection* >( mMechant->GetComponentByName( "direction" ) );
        mRotationFOV = mRotationFOV.getInverse();
        direction->SetUsingVector( mRotationFOV.transformPoint( direction->AsVector2F() ) );
        mRotationFOV = mRotationFOV.getInverse();
    }
    else if( iEvent.key.code == sf::Keyboard::Key::K )
    {
        SaveXML();
    }
    else if( iEvent.key.code == sf::Keyboard::Key::L )
    {
        LoadXML();
    }
}


void
cInfiltratorScreen::KeyReleased( const sf::Event& iEvent )
{
    // Does nothing
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

    ::nApplication::cGameApplication::App()->World()->SaveXML( elm, &doc );

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

    ::nApplication::cGameApplication::App()->World()->LoadXML( doc.FirstChildElement( "world" ) );

    if( !error )
        std::cout << "Successfuly loaded " << std::endl;
    else
        std::cout << "Failed to load" << std::endl;
    //mMechant = cGameApplication::App()->World()->GetEntityByID( "idontknow9" );
}


} // namespace nScreen

