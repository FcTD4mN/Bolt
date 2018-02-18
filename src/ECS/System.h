#pragma once

#include "SFML/Window.hpp"

class cEntity;

class cSystem
{

public:
    // Contruction/Destruction
    virtual  ~cSystem() = 0;
    cSystem();

public:
    // Init/Finalize
    virtual  void  Initialize() = 0;
    virtual  void  Finalize() = 0;

public:
    // Update/Draw
    virtual  void  Draw();
    virtual  void  Update();

public:
    // Entity
    virtual  void  IncomingEntity( cEntity* iEntity ) = 0;
    virtual  void  EntityLost( cEntity* iEntity );

public:
    // Events
    virtual  void  Resized( const sf::Event& iEvent );                ///< The window was resized (data in event.size)
    virtual  void  KeyPressed( const sf::Event& iEvent );             ///< A key was pressed (data in event.key)
    virtual  void  KeyReleased( const sf::Event& iEvent );            ///< A key was released (data in event.key)
    virtual  void  MouseWheelMoved( const sf::Event& iEvent );        ///< The mouse wheel was scrolled (data in event.mouseWheel) (deprecated)
    virtual  void  MouseWheelScrolled( const sf::Event& iEvent );     ///< The mouse wheel was scrolled (data in event.mouseWheelScroll)
    virtual  void  MouseButtonPressed( const sf::Event& iEvent );     ///< A mouse button was pressed (data in event.mouseButton)
    virtual  void  MouseButtonReleased( const sf::Event& iEvent );    ///< A mouse button was released (data in event.mouseButton)
    virtual  void  MouseMoved( const sf::Event& iEvent );             ///< The mouse cursor moved (data in event.mouseMove)
    virtual  void  MouseEntered( const sf::Event& iEvent );           ///< The mouse cursor entered the area of the window (no data)
    virtual  void  MouseLeft( const sf::Event& iEvent );              ///< The mouse cursor left the area of the window (no data)
    virtual  void  JoystickButtonPressed( const sf::Event& iEvent );  ///< A joystick button was pressed (data in event.joystickButton)
    virtual  void  JoystickButtonReleased( const sf::Event& iEvent ); ///< A joystick button was released (data in event.joystickButton)
    virtual  void  JoystickMoved( const sf::Event& iEvent );          ///< The joystick moved along an axis (data in event.joystickMove)
    virtual  void  JoystickConnected( const sf::Event& iEvent );      ///< A joystick was connected (data in event.joystickConnect)
    virtual  void  JoystickDisconnected( const sf::Event& iEvent );   ///< A joystick was disconnected (data in event.joystickConnect)
    virtual  void  TouchBegan( const sf::Event& iEvent );             ///< A touch event began (data in event.touch)
    virtual  void  TouchMoved( const sf::Event& iEvent );             ///< A touch moved (data in event.touch)
    virtual  void  TouchEnded( const sf::Event& iEvent );             ///< A touch event ended (data in event.touch)
    virtual  void  SensorChanged( const sf::Event& iEvent );          ///< A sensor value changed (data in event.sensor)

protected:
    std::vector< cEntity* > mEntityGroup;
};

