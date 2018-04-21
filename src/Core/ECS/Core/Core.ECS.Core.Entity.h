#pragma once


#include <tinyxml2.h>


#include <unordered_map>
#include <vector>


namespace nECS {


class cComponent;
class cSystem;
class cWorld;
class cEntityParser;


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
    cEntity( cWorld* iWorld );
    cEntity( const cEntity& iEntity );

public:
    // Copy
    cEntity * Clone();

public:
    // Components
    void  AddComponent( cComponent* iComponent );
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
    bool IsDead() const;
    void SetLoaded();
    const std::string& ID() const;
    void Destroy();
    void AddSystemObserver( cSystem* iSystem );


public:
    // Input/Output
    virtual  void SaveXML( tinyxml2::XMLElement* iNode, tinyxml2::XMLDocument* iDocument );
    virtual  void LoadXML( tinyxml2::XMLElement* iNode );

private:
    cWorld *                    mWorld;             // To call for updates if entity changes

    std::string                 mID;
    std::vector< sPair >        mComponents;
    std::vector< std::string >  mTags;              // Tags are "boolean" components, to avoid creating objects with no data.Gives a property such as lootable, or killable
    std::vector< cSystem* >     mObserverSystems;   // Entity knows which systems are observing, when destroyed, an entity can remove itself from system directly->fast
    bool                        mLoaded;            // Allows creating an entity (ak, adding tags and components) without refreshing systems every time
    bool                        mDead;              // The entity is dead and shall be removed from world

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

