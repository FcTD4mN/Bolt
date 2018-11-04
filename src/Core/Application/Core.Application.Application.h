#pragma once


#include <SFML/Graphics.hpp>

#include "Core.Base.FileSystem.h"

namespace nCore::nApplication   { class cApplication; }
namespace nCore::nProject       { class cProject; }
namespace nScreen               { class cScreen; }


::nCore::nApplication::cApplication* CreateApplication();

namespace nCore {
namespace nApplication {


class  cApplication
{
public:
    static  cApplication*  App();

public:
    cApplication();

public:
    sf::RenderWindow*  Window();
    void  SetAppTitle( const  std::string&  iTitle );
    void  SetAppDefaultResolution( int iW, int iH );

public:
    // Project
    ::nCore::nProject::cProject*    Project();
    void                            NewProject( const  std::string&  iProjectFile );
    bool                            LoadProject( const  nStdFileSystem::path&  iProjectFolder );
    void                            SetDefaultNoProjectScreen(); // Setup a project, whose purpose is to present itself to user if no project is loaded

public:
    // Init/Finalize
    virtual  void  Initialize();
    virtual  void  Finalize();
    virtual  void  BuildProject();

public:
    // Update/Draw
    virtual  void  Update( unsigned int iDeltaTime );
    virtual  void  Draw( sf::RenderTarget*  iRenderTarget );

public:
    // Screen
    void                ChangeScreenASAP( const  std::string&  iScreenName );
    void                PushScreen( ::nScreen::cScreen*  iScreen );
    void                RemoveScreen( const  std::string&  iScreenName );
    ::nScreen::cScreen* CurrentScreen();

public:
    // Events
    void  HandleEvents( sf::Event& iEvent );

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
    sf::RenderWindow*               mMainWindow;
    ::nCore::nProject::cProject*    mProject;

    // As we can't change screen right when we want it (because a lot of things need to end, to be finalized etc), we ask a screen change, and it'll be done as soon as possible
    std::string                     mScreenNameToLoad;
    bool                            mLoadScreenASAP;
};


} // namespace nApplication
} // namespace nCore

