#pragma once


#include <SFML/Graphics.hpp>
#include <tinyxml2.h>


#include <unordered_map>
#include <functional>


namespace nCore::nRender    { class cLayer; }
namespace nCore::nRender    { class cLayerEngine; }
namespace nCore::nMapping   { class cEntityGrid; }


namespace nCore {
namespace nECS {
namespace nCore {


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
    void  Draw( sf::RenderTarget* iRenderTarget );
    void  Update( unsigned int iDeltaTime );

public:
    // Layers
    ::nCore::nRender::cLayerEngine* LayerEngine();
    void                            AddLayer( const sf::Vector2f& iViewSize, float iDistance );
    void                            LayersEnumerator( std::function< void( ::nCore::nRender::cLayer* ) > iFunction );

public:
    // Entity
    int         AddEntityAndPutInLayer( cEntity* iEntity, ::nCore::nRender::cLayer* iLayer );   // returns the index of the entity in its layer
    int         AddEntityAndPutInLayer( cEntity* iEntity, int iLayerIndex );                    // returns the index of the entity in its layer
    void        UpdateWorldWithEntity( cEntity* iEntity );                                      // Called if an entity changed component or tag wise, meaning systems will have to undergo incomingEntityAgain etc
    void        DestroyEntity( cEntity* iEntity );
    void        DestroyEntityByID( const  std::string& iID );
    cEntity*    GetEntityByID( const  std::string& iID );
    cEntity*    GetEntityAtIndex( int iIndex );
    void        DestroyAllEntities();
    void        PurgeEntities();                                                                // Actual deletion of destroyed entities

    void        EntityEnumerator( std::function< void( cEntity* ) > iEnumeratorFunction );
    bool        IsIDUnique( const std::string& iID ) const;
    int         EntityCount() const;

private:

public:
    // Systems
    void        AddSystem( cSystem* iSystem );
    void        InsertSystem( cSystem* iSystem, int iIndex );
    void        RemoveSystem( cSystem* iSystem );
    void        RemoveSystemByName( const std::string& iSysName );
    void        ConnectSystemToEvents( cSystem* iSystem );
    void        DisconnectSystemToEvents( cSystem* iSystem );
    int         SystemCount() const;

    // EDITOR
    cSystem*    GetSystemAtIndex( int iIndex );
    cSystem*    GetSystemByName( const std::string& iName );
    bool        HasSystem( const std::string& iSysName ) const;

public:
    // EntityMap
    void                                SetEntityMapDimensions( int iWidth, int iHeight, int iCellSize );
    ::nCore::nMapping::cEntityGrid*     EntityMap();
    void                                EntityMapEnumerator( std::function< void( ::nCore::nMapping::cEntityGrid* iEntityGrid ) > iFunction );

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

public:
    // Input/Output
    virtual  void SaveXML( tinyxml2::XMLElement* iNode, tinyxml2::XMLDocument* iDocument ) const;
    virtual  void LoadXML( tinyxml2::XMLElement* iNode );

private:
    // Private
    void        _AddEntityToWorld( cEntity* iEntity );
    void        _RemoveEntity( cEntity* iEntity );

protected:
    std::unordered_map< std::string, cEntity* > mEntities;
    std::vector< cEntity* >                     mEntitiesToDestroy;

    std::vector< cSystem* >                     mSystems;
    std::vector< cSystem* >                     mEventRelatedSystems;

    ::nCore::nMapping::cEntityGrid*             mEntityMap;

public:
    ::nCore::nRender::cLayerEngine*             mLayerEngine;
};


} // namespace nCore
} // namespace nECS
} // namespace nCore

