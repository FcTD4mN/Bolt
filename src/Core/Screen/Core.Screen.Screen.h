#pragma once


#include <SFML/Graphics.hpp>

#include <filesystem>
#include <functional>

namespace nECS      { class cWorld; }
namespace nECS      { class cEntity; }
namespace nMapping  { class cEntityGrid; }
namespace nRender   { class cLayer; }
namespace nRender   { class cLayerEngine; }

namespace nScreen {


class cScreen
{
public:
    // Contruction/Destruction
    virtual  ~cScreen();
    cScreen();
    cScreen( const std::string& iName );

public:
    virtual  void  Initialize();
    virtual  void  Finalize();

public:
    // Draw / Update
    virtual  void  Draw( sf::RenderTarget* iRenderTarget );
    virtual  void  Update( unsigned int iDeltaTime );

public:
    // Layers
    void  PutEntityInLayer( ::nECS::cEntity* iEntity, int iLayerIndex );
    void  SetUseLayerEngine( bool iValue );

	void  LayersEnumerator( std::function< void( ::nRender::cLayer* ) > iFunction );

public:
    // Get / Set
    const std::string&  Name() const;
    void                Name( const std::string& iName );

    const std::filesystem::path&    FilePath() const;
    void                            FilePath( const std::filesystem::path& iFilePath );
    void                            FilePath( const std::string& iFilePath );

	sf::View&	View();
	void		View( sf::View& iView );
	void		ApplyScreenView();

	float		ZoomFactor();
	void		ZoomBy( float iAmount );

public:
    // EDITOR
    ::nECS::cWorld*             World();

public:
    // Events
    virtual  void  Resized( const sf::Event& iEvent );                ///< The window was resized (data in event.size)
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

public:
    // Input/Output
    virtual  void SaveXML();
    virtual  void LoadXML( const std::string& iFilePath );

protected:
    std::string                 mName;
    std::filesystem::path       mFilePath;
	sf::View					mView;
	float						mZoomFactor;

    ::nECS::cWorld*             mWorld;
};


} // namespace nScreen

