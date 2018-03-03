#pragma once

#include "SFML/Graphics.hpp"

class cScreen;

class cApplication
{
public:
    cApplication();

public:
    sf::RenderWindow* Window();
    void  SetAppTitle( const std::string& iTitle );
    void  SetAppDefaultResolution( int iW, int iH );

public:
    void Initialize();
    void Finalize();

public:
    void Update( unsigned int iDeltaTime );
    void Draw( sf::RenderTarget* iRenderTarget );

public:
    // Screen
    void PushScreen( cScreen* iScreen );
    void PopScreen();

public:
    // Events
    void HandleEvents( sf::Event& iEvent );

    virtual  void  Closed( const sf::Event& iEvent );                 ///< The window requested to be closed (no data)
    virtual  void  Resized( const sf::Event& iEvent );                ///< The window was resized (data in event.size)
    virtual  void  LostFocus( const sf::Event& iEvent );              ///< The window lost the focus (no data)
    virtual  void  GainedFocus( const sf::Event& iEvent );            ///< The window gained the focus (no data)
    virtual  void  TextEntered( const sf::Event& iEvent );            ///< A character was entered (data in event.text)
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
    sf::RenderWindow*       mMainWindow;
    std::vector< cScreen* > mScreenStack;
    cScreen*                mCurrentScreen;
};
