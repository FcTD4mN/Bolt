#pragma once


#include <tinyxml2.h>

#include "SFML/Graphics.hpp"

#include <unordered_map>
#include <vector>


namespace nRender { class cLayer; }

namespace nECS {


class cComponent;
class cSystem;
class cWorld;
class cEntityParser;
class cEntityHandle;

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
    friend cEntityParser;

private: // So nobody except for friends can delete entities
    ~cEntity();

public:
    // Contruction/Destruction
    cEntity();
    cEntity( const cEntity& iEntity );

public:
    // Copy
    cEntity * Clone();

public:
    void LeaveAllSystems();

public:
    // Components
    void  AddComponent( cComponent* iComponent );
    void  SetComponent( cComponent* iComponent );
    void  RemoveComponent( cComponent* iComponent );
    void  RemoveComponentByName( const std::string& iComponentName );
    cComponent*  GetComponentByName( const std::string& iComponentName );

    // EDITOR
    cComponent*  GetComponentAtIndex( int iIndex );
    void RemoveComponentAtIndex( int iIndex );

    unsigned int GetComponentCount() const;

public:
    // Tags
    void  AddTag( const std::string& iTag );
    void  RemoveTag( const std::string& iTag );
    bool  HasTag( const std::string& iTag );
    const std::string&  GetTagAtIndex( int iIndex );

    unsigned int GetTagCount() const;

public:
    // Access/Get
	::nRender::cLayer*	Layer();

    bool				IsDead() const;
    const std::string&	ID() const;
    bool				SetID( const std::string& iID );
    void				Destroy();
    void				AddSystemObserver( cSystem* iSystem );
    cEntityHandle		GetHandle();
    unsigned int		GetIDForHandle() const;

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
    virtual  void SaveXML( tinyxml2::XMLElement* iNode, tinyxml2::XMLDocument* iDocument );
    virtual  void LoadXML( tinyxml2::XMLElement* iNode );

private:
    cWorld *                    mWorld;             // To call for updates if entity changes
	::nRender::cLayer*			mContainerLayer;	// The layer this entity is in : to allow getting entityGrid fast.

    std::string                 mID;
    std::vector< sPair >        mComponents;
    std::vector< std::string >  mTags;              // Tags are "boolean" components, to avoid creating objects with no data.Gives a property such as lootable, or killable
    std::vector< cSystem* >     mObserverSystems;   // Entity knows which systems are observing, when destroyed, an entity can remove itself from system directly->fast
    bool                        mLoaded;            // Allows creating an entity (ak, adding tags and components) without refreshing systems every time
    bool                        mDead;              // The entity is dead and shall be removed from world

    unsigned int                mIDForHandles;
};


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













// =================================================
// ========== VERSION UNORDERED_MAP ================
// =================================================


    //class cEntity
    //{

    //public:
    //    // Contruction/Destruction
    //    ~cEntity();
    //    cEntity( cWorld* iWorld );
    //    cEntity( const cEntity& iEntity );

    //public:
    //    // Copy
    //    cEntity * Clone();

    //public:
    //    // Components
    //    void  AddComponent( cComponent* iComponent );
    //    void  RemoveComponent( cComponent* iComponent );
    //    void  RemoveComponentByName( const std::string& iComponentName );
    //    cComponent*  GetComponentByName( const std::string& iComponentName );

    //public:
    //    // Tags
    //    void  AddTag( const std::string& iTag );
    //    void  RemoveTag( const std::string& iTag );
    //    bool  HasTag( const std::string& iTag );

    //public:
    //    // Access/Get
    //    bool IsDead() const;
    //    void SetLoaded();
    //    const std::string& ID() const;

    //public:
    //    // Input/Output
    //    virtual  void SaveXML( tinyxml2::XMLElement* iNode, tinyxml2::XMLDocument* iDocument );
    //    virtual  void LoadXML( tinyxml2::XMLElement* iNode );

    //private:
    //    cWorld * mWorld;             // To call for updates if entity changes

    //    std::string                                     mID;
    //    std::unordered_map< std::string, cComponent* >  mComponents;
    //    std::unordered_map< std::string, bool >         mTags;              // Tags are "boolean" components, to avoid creating objects with no data.Gives a property such as lootable, or killable
    //    std::vector< cSystem* >                         mObserverSystems;   // Entity knows which systems are observing, when destroyed, an entity can remove itself from system directly->fast
    //    bool                                            mLoaded;            // Allows creating an entity (ak, adding tags and components) without refreshing systems every time
    //    bool                                            mDead;              // The entity is dead and shall be removed from world

    //};


} // namespace nECS

