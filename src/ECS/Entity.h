#pragma once

#include <unordered_map>
#include <vector>

#include "tinyxml2.h"

class cComponent;
class cSystem;
class cWorld;

class cEntity
{

public:
    // Contruction/Destruction
    ~cEntity();
    cEntity( cWorld* iWorld );

public:
    // Components
    void  AddComponent( cComponent* iComponent );
    void  RemoveComponent( cComponent* iComponent );
    void  RemoveComponentByName( const std::string& iComponentName );
    cComponent*  GetComponentByName( const std::string& iComponentName );

public:
    // Tags
    void  AddTag( const std::string& iTag );
    void  RemoveTag( const std::string& iTag );
    bool  HasTag( const std::string& iTag );

public:
    bool IsDead() const;
    void SetLoaded();

public:
    // Input/Output
    virtual  void SaveXML( tinyxml2::XMLElement* iNode, tinyxml2::XMLDocument* iDocument );
    virtual  void LoadXML( const tinyxml2::XMLElement* iNode );

private:
    cWorld *                                        mWorld;             // To call for updates if entity changes

    std::string                                     mID;
    std::unordered_map< std::string, cComponent* >  mComponents;
    std::unordered_map< std::string, bool >         mTags;              // Tags are "boolean" components, to avoid creating objects with no data.Gives a property such as lootable, or killable
    std::vector< cSystem* >                         mObserverSystems;   // Entity knows which systems are observing, when destroyed, an entity can remove itself from system directly->fast
    bool                                            mLoaded;            // Allows creating an entity (ak, adding tags and components) without refreshing systems every time
    bool                                            mDead;              // The entity is dead and shall be removed from world

};

