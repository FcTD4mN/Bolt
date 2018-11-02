#pragma once


#include <tinyxml2.h>

#include "SFML/Graphics.hpp"

#include <unordered_map>
#include <vector>


namespace nCore { namespace nRegistries { class cEntityRegistry; } }
namespace nCore { namespace nRender     { class cLayer; } }
namespace nCore { namespace nECS        { namespace nCore { class cComponent; } } }
namespace nCore { namespace nECS        { namespace nCore { class cSystem; } } }
namespace nCore { namespace nECS        { namespace nCore { class cWorld; } } }
namespace nCore { namespace nECS        { namespace nCore { class cEntityHandle; } } }


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
    void  AddComponent( cComponent* iComponent );
    void  SetComponent( cComponent* iComponent );
    void  RemoveComponent( cComponent* iComponent );
    void  RemoveComponentByName( const std::string& iComponentName );
    cComponent*  GetComponentByName( const std::string& iComponentName );

    template< class T > T  GetComponentByNameAs( const std::string& iComponentName );

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
    void                AddSystemObserver( cSystem* iSystem );
    cEntityHandle       GetHandle();
    unsigned int        GetIDForHandle() const;

public:
    void  DrawUsingObserverSystems( sf::RenderTarget* iRenderTarget );

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
    ::nCore::nRender::cLayer*   mContainerLayer;    // The layer this entity is in : to allow getting entityGrid fast.

    std::string                 mID;
    std::vector< sPair >        mComponents;
    std::vector< std::string >  mTags;              // Tags are "boolean" components, to avoid creating objects with no data.Gives a property such as lootable, or killable
    std::vector< cSystem* >     mObserverSystems;   // Entity knows which systems are observing, when destroyed, an entity can remove itself from system directly->fast
    bool                        mLoaded;            // Allows creating an entity (ak, adding tags and components) without refreshing systems every time
    bool                        mDead;              // The entity is dead and shall be removed from world

    unsigned int                mIDForHandles;
};


template< class T >
T
cEntity::GetComponentByNameAs( const std::string& iComponentName )
{
    return  dynamic_cast<T>( GetComponentByName( iComponentName ) );
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

