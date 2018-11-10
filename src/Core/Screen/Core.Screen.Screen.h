#pragma once


#include <SFML/Graphics.hpp>

#include <functional>

#include "Core.Base.FileSystem.h"

namespace nCore::nECS::nCore    { class cWorld; }
namespace nCore::nECS::nCore    { class cEntity; }
namespace nMapping              { class cEntityMap; }
namespace nCore::nRender        { class cLayer; }
namespace nCore::nRender        { class cLayerEngine; }

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
    virtual  void  Unload();  // Equals finalize, but has explicit name to be clear

public:
    // This method is called after a loadXML, this is where you do c++ code if writting a c++ screen
    // Here you can for example create dynamic entities, do stuff programmatically
    virtual  void  AdditionnalBuildScreen();

public:
    // Draw / Update
    virtual  void  Draw( sf::RenderTarget* iRenderTarget );
    virtual  void  Update( unsigned int iDeltaTime );

public:
    // Layers
    void  PutEntityInLayer( ::nCore::nECS::nCore::cEntity* iEntity, int iLayerIndex );

    void  LayersEnumerator( std::function< void( ::nCore::nRender::cLayer* ) > iFunction );

public:
    // Get / Set
    const std::string&  Name() const;
    void                Name( const std::string& iName );

    const nStdFileSystem::path&     FilePath() const;
    void                            FilePath( const nStdFileSystem::path& iFilePath );
    void                            FilePath( const std::string& iFilePath );

    sf::View&   View();
    void        View( sf::View& iView );
    void        ApplyScreenView();

    float       ZoomFactor();
    void        ZoomBy( float iAmount );

    bool        Loaded() const;
    bool        Initialized() const;
    bool        AdditionalBuildCompleted() const;

public:
    // EDITOR
    nCore::nECS::nCore::cWorld*             World();

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
        // SaveXML and LoadXML are the functions to save the screen as in the project
    virtual  void SaveXML() const;
    virtual  void LoadXML();

        // These two are functions to export/import from any file
    virtual  void ExportToFile( const nStdFileSystem::path& iFilePath ) const;
    virtual  void ImportFromFile( const nStdFileSystem::path& iFilePath );

protected:
    std::string                     mName;
    nStdFileSystem::path            mFilePath;
    sf::View                        mView;          // This is actually the Core's camera
    float                           mZoomFactor;    // This is stored as the camera's zoom because sf::View doesn't store zoom, it does direct resizing when calling zoom(x)

    ::nCore::nECS::nCore::cWorld*   mWorld;

    bool                            mLoaded;
    bool                            mInitialized;
    bool                            mAdditionalBuildComplete;

    // EDITOR ONLY <-- Might have to find another place for them, as it takes up memory space for nothing when playing the game
    // Maybe just a ifdef EDITOR ? <-- BetterTODO : Do an editor camera and a Core camera, and get rid of BOTH views
    sf::View                        mEditorView;
};


} // namespace nScreen

