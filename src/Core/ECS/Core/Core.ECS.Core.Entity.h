#pragma once


#include <tinyxml2.h>

#include "SFML/Graphics.hpp"

#include <unordered_map>
#include <vector>


namespace nCore::nRegistries { class cEntityRegistry; }
namespace nCore::nRender     { class cLayer; }
namespace nCore::nECS::nCore { class cComponent; }
namespace nCore::nECS::nCore { class cSystem; }
namespace nCore::nECS::nCore { class cWorld; }
namespace nCore::nECS::nCore { class cEntityHandle; }


namespace nCore {
namespace nECS {
namespace nCore {


namespace
{
    struct sPair
    {
        std::string key;
        cComponent* value;
    };
}

class cEntity
{
    // Both friends so they have the right to call delete on entities
    friend cWorld;
    friend ::nCore::nRegistries::cEntityRegistry;

    // To solve the mContainerLayer sync.
    // Can this be done in a cleaner way ? cuz atm, layer can delete entity, which isn't the best
    friend ::nCore::nRender::cLayer;

private: // So nobody except for friends can delete entities
    virtual ~cEntity();

public:
    // Contruction/Destruction
    cEntity();
    cEntity( const cEntity& iEntity );

public:
    // Copy
    cEntity * Clone() const;

public:
    void LeaveAllSystems();

public:
    // Components
    void            AddComponent( cComponent* iComponent );
    void            SetComponent( cComponent* iComponent );
    void            RemoveComponent( cComponent* iComponent );
    void            RemoveComponentByID( const std::string& iComponentID );
    cComponent*     GetComponentByID( const std::string& iComponentID );

    // Allows to connect the variable from components within this entity.
    // For example, we want the hitbox's size to be equal to the transformation's size, or X value, or whatever.
    void            ConnectComponentsVariables( const std::string& iComponentAName, const std::string& iVariableAName, const std::string& iComponentBName, const std::string& iVariableBName );

    template< class T > T  GetComponentByIDAs( const std::string& iComponentID );

    // EDITOR
    cComponent*  GetComponentAtIndex( int iIndex );
    void RemoveComponentAtIndex( int iIndex );

    unsigned int GetComponentCount() const;

public:
    // Tags
    void  AddTag( const std::string& iTag );
    void  RemoveTag( const std::string& iTag );
    bool  HasTag( const std::string& iTag );

    // EDITOR
    const std::string&  GetTagAtIndex( int iIndex );
    void  SetTagAtIndex( int iIndex, const std::string& iTag );
    unsigned int GetTagCount() const;

public:
    // Access/Get
    ::nCore::nRender::cLayer*          Layer();
    const ::nCore::nRender::cLayer*    Layer() const;

    bool                IsDead() const;
    const std::string&  ID() const;
    bool                SetID( const std::string& iID );
    void                Destroy();
    cEntityHandle       GetHandle();
    unsigned int        GetIDForHandle() const;

public:
    // System
    void    AddSystemObserver( cSystem* iSystem );
    void    DrawUsingObserverSystems( sf::RenderTarget* iRenderTarget );

private:
    void IncIDForHandles();

private:
    // World only
    void SetLoaded();
    void SetWorld( cWorld* iWorld );

public:
    // Input/Output
    virtual  void SaveXML( tinyxml2::XMLElement* iNode, tinyxml2::XMLDocument* iDocument ) const;
    virtual  void LoadXML( tinyxml2::XMLElement* iNode );

private:
    cWorld *                    mWorld;             // To call for updates if entity changes
    ::nCore::nRender::cLayer*   mContainerLayer;    // The layer this entity is in : to allow getting EntityMap fast.

    std::string                 mID;                // An ID that allows finding component in hash map easily
    std::vector< sPair >        mComponents;
    std::vector< std::string >  mTags;              // Tags are "boolean" components, to avoid creating objects with no data.Gives a property such as lootable, or killable
    std::vector< cSystem* >     mObserverSystems;   // Entity knows which systems are observing, when destroyed, an entity can remove itself from system directly->fast
    bool                        mLoaded;            // Allows creating an entity (ak, adding tags and components) without refreshing systems every time
    bool                        mDead;              // The entity is dead and shall be removed from world

    unsigned int                mIDForHandles;

    // All internal connections are stored here, so whenever the entity is cloned, we can recreate all connections
    std::vector< std::tuple< std::string, std::string, std::string, std::string > >  mAllComponentsConnections;
};


template< class T >
T
cEntity::GetComponentByIDAs( const std::string& iComponentID )
{
    return  dynamic_cast<T>( GetComponentByID( iComponentID ) );
}


// =================================================
// ===================== HANDLE ====================
// =================================================


class cEntityHandle
{
public:
    ~cEntityHandle();
    cEntityHandle( cEntity* iEntity );

public:
    cEntity * GetEntity();
    bool    IsHandleValid();
    bool    SyncHandle();

private:
    cEntity * mEntity;
    unsigned int  mHandleID;
};


} // namespace nCore
} // namespace nECS
} // namespace nCore

