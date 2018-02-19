#pragma once

#include "SFML/Window.hpp"

class cEntity;
class cSystem;

class cWorld
{

public:
    // Contruction/Destruction
    ~cWorld();
    cWorld();

public:
    // Update/Draw
    void  Draw();
    void  Update();

public:
    // Entity
    void  AddEntity( cEntity* iEntity );
    void  RemoveEntity( cEntity* iEntity );
    void  UpdateWorldWithEntity( cEntity* iEntity );

public:
    // Systems
    void  AddSystem( cSystem* iSystem );
    void  ConnectSystemToEvents( cSystem* iSystem );

public:
    // Events
    void  Resized( const sf::Event& iEvent );                ///< The window was resized (data in event.size)
    void  KeyPressed( const sf::Event& iEvent );             ///< A key was pressed (data in event.key)
    void  KeyReleased( const sf::Event& iEvent );            ///< A key was released (data in event.key)
    void  MouseWheelMoved( const sf::Event& iEvent );        ///< The mouse wheel was scrolled (data in event.mouseWheel) (deprecated)
    void  MouseWheelScrolled( const sf::Event& iEvent );     ///< The mouse wheel was scrolled (data in event.mouseWheelScroll)
    void  MouseButtonPressed( const sf::Event& iEvent );     ///< A mouse button was pressed (data in event.mouseButton)
    void  MouseButtonReleased( const sf::Event& iEvent );    ///< A mouse button was released (data in event.mouseButton)
    void  MouseMoved( const sf::Event& iEvent );             ///< The mouse cursor moved (data in event.mouseMove)
    void  MouseEntered( const sf::Event& iEvent );           ///< The mouse cursor entered the area of the window (no data)
    void  MouseLeft( const sf::Event& iEvent );              ///< The mouse cursor left the area of the window (no data)
    void  JoystickButtonPressed( const sf::Event& iEvent );  ///< A joystick button was pressed (data in event.joystickButton)
    void  JoystickButtonReleased( const sf::Event& iEvent ); ///< A joystick button was released (data in event.joystickButton)
    void  JoystickMoved( const sf::Event& iEvent );          ///< The joystick moved along an axis (data in event.joystickMove)
    void  JoystickConnected( const sf::Event& iEvent );      ///< A joystick was connected (data in event.joystickConnect)
    void  JoystickDisconnected( const sf::Event& iEvent );   ///< A joystick was disconnected (data in event.joystickConnect)
    void  TouchBegan( const sf::Event& iEvent );             ///< A touch event began (data in event.touch)
    void  TouchMoved( const sf::Event& iEvent );             ///< A touch moved (data in event.touch)
    void  TouchEnded( const sf::Event& iEvent );             ///< A touch event ended (data in event.touch)
    void  SensorChanged( const sf::Event& iEvent );          ///< A sensor value changed (data in event.sensor)

protected:
    std::vector< cEntity* > mEntity;
    std::vector< cSystem* > mSystems;
    std::vector< cSystem* > mEventRelatedSystems;
};

