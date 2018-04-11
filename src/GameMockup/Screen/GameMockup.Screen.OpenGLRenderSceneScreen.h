#pragma once


#include "Core.Screen.Screen.h"

#include "Core.GUI.ConsoleWidget.h"
#include "Core.Volumetric.SparseOctree.USROCMap.h"
#include "Core.Shader.Shader.h"


namespace nScreen {


class cOpenGLRenderSceneScreen :
    public cScreen
{

public:
    // Contruction/Destruction
    virtual  ~cOpenGLRenderSceneScreen();
    cOpenGLRenderSceneScreen();

public:
    virtual  void  Initialize() override;
    virtual  void  Finalize() override;

public:
    virtual  void  Draw( sf::RenderTarget* iRenderTarget ) override;
    virtual  void  Update( unsigned int iDeltaTime ) override;

public:
    // Events
    virtual  void  Resized( const sf::Event& iEvent ) override;                 ///< The window was resized (data in event.size)
    virtual  void  TextEntered( const sf::Event& iEvent );                      ///< A character was entered (data in event.text)
    virtual  void  KeyPressed( const sf::Event& iEvent ) override;              ///< A key was pressed (data in event.key)
    virtual  void  KeyReleased( const sf::Event& iEvent ) override;             ///< A key was released (data in event.key)
    virtual  void  MouseWheelMoved( const sf::Event& iEvent ) override;         ///< The mouse wheel was scrolled (data in event.mouseWheel) (deprecated)
    virtual  void  MouseWheelScrolled( const sf::Event& iEvent ) override;      ///< The mouse wheel was scrolled (data in event.mouseWheelScroll)
    virtual  void  MouseButtonPressed( const sf::Event& iEvent ) override;      ///< A mouse button was pressed (data in event.mouseButton)
    virtual  void  MouseButtonReleased( const sf::Event& iEvent ) override;     ///< A mouse button was released (data in event.mouseButton)
    virtual  void  MouseMoved( const sf::Event& iEvent ) override;              ///< The mouse cursor moved (data in event.mouseMove)
    virtual  void  MouseEntered( const sf::Event& iEvent ) override;            ///< The mouse cursor entered the area of the window (no data)
    virtual  void  MouseLeft( const sf::Event& iEvent ) override;               ///< The mouse cursor left the area of the window (no data)
    virtual  void  JoystickButtonPressed( const sf::Event& iEvent ) override;   ///< A joystick button was pressed (data in event.joystickButton)
    virtual  void  JoystickButtonReleased( const sf::Event& iEvent ) override;  ///< A joystick button was released (data in event.joystickButton)
    virtual  void  JoystickMoved( const sf::Event& iEvent ) override;           ///< The joystick moved along an axis (data in event.joystickMove)
    virtual  void  JoystickConnected( const sf::Event& iEvent ) override;       ///< A joystick was connected (data in event.joystickConnect)
    virtual  void  JoystickDisconnected( const sf::Event& iEvent ) override;    ///< A joystick was disconnected (data in event.joystickConnect)
    virtual  void  TouchBegan( const sf::Event& iEvent ) override;              ///< A touch event began (data in event.touch)
    virtual  void  TouchMoved( const sf::Event& iEvent ) override;              ///< A touch moved (data in event.touch)
    virtual  void  TouchEnded( const sf::Event& iEvent ) override;              ///< A touch event ended (data in event.touch)
    virtual  void  SensorChanged( const sf::Event& iEvent ) override;           ///< A sensor value changed (data in event.sensor)

private:
    ::nGUI::cConsoleWidget*  mConsoleWidget;
    sf::Clock  mClock;
    ::nShaders::cShader mShader;

    ::nVolumetric::nSparseOctree::cUSROCMap< ::nVolumetric::nSparseOctree::eLod2N::kLod64,
                                             ::nVolumetric::nSparseOctree::eLod2N::kLod32,
                                             ::nVolumetric::nSparseOctree::eLod2N::kLod16,
                                             ::nVolumetric::nSparseOctree::tByte >
                                             mMap2;
};


} // namespace nScreen

