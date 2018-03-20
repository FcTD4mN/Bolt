#include "Entity.h"

#include "ECS/Core/Component.h"
#include "ECS/Core/World.h"
#include "ECS/Core/System.h"

#include "ECS/Utilities/ComponentRegistry.h"

static unsigned int sgEntityCount = 0;


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------ Construction/Destruction
// -------------------------------------------------------------------------------------

cEntity::~cEntity()
{
    for( int i = 0; i < mObserverSystems.size(); ++i )
    {
        mObserverSystems[ i ]->EntityLost( this );
    }

    for( auto it = mComponents.begin(); it != mComponents.end(); ++it )
    {
        delete  it->value;
    }
}


cEntity::cEntity( cWorld* iWorld ) :
    mWorld( iWorld ),
    mID( "idontknow" + std::to_string( sgEntityCount ) ),
    mComponents(),
    mTags(),
    mObserverSystems(),
    mLoaded( false ),
    mDead( false )
{
    mComponents.reserve( 16 );
    mTags.reserve( 64 );
    ++sgEntityCount;
}


cEntity::cEntity( const cEntity& iEntity ) :
    mWorld( iEntity.mWorld ),
    mID( iEntity.mID + "c" + std::to_string( sgEntityCount ) ),
    mComponents(),                                  // This will need to get copied
    mTags( iEntity.mTags ),                         // This can be copied, as there is no pointer
    mObserverSystems( iEntity.mObserverSystems ),   // Same systems will observe this entity
    mLoaded( iEntity.mLoaded ),
    mDead( iEntity.mDead )
{
    mComponents.reserve( 16 );
    mTags.reserve( 64 );
    for( auto it = iEntity.mComponents.begin(); it != iEntity.mComponents.end(); ++it )
    {
        sPair pair;
        pair.key = it->key;
        pair.value = it->value->Clone();
        mComponents.push_back( pair );
    }
}


// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------- Copy
// -------------------------------------------------------------------------------------


cEntity*
cEntity::Clone()
{
    return  new cEntity( *this );
}


// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------- Components
// -------------------------------------------------------------------------------------


void
cEntity::AddComponent( cComponent * iComponent )
{
    sPair pair;
    pair.key = iComponent->Name();
    pair.value = iComponent;
    mComponents.push_back( pair );
}


void
cEntity::RemoveComponent( cComponent * iComponent )
{
    for( int i = 0; i < mComponents.size(); ++i )
    {
        if( mComponents[ i ].key == iComponent->Name() && mComponents[ i ].value == iComponent )
            mComponents.erase( mComponents.begin() + i );
    }
}


void
cEntity::RemoveComponentByName( const std::string & iComponentName )
{
    for( int i = 0; i < mComponents.size(); ++i )
    {
        if( mComponents[ i ].key == iComponentName )
            mComponents.erase( mComponents.begin() + i );
    }
}


cComponent*
cEntity::GetComponentByName( const std::string & iComponentName )
{
    for( int i = 0; i < mComponents.size(); ++i )
    {
        if( mComponents[ i ].key == iComponentName )
            return  mComponents[ i ].value;
    }

    return  0;
}


// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------- Tags
// -------------------------------------------------------------------------------------


void
cEntity::AddTag( const std::string & iTag )
{
    mTags.push_back( iTag );
}


void
cEntity::RemoveTag( const std::string & iTag )
{
    for( int i = 0; i < mTags.size(); ++i )
    {
        if( mTags[ i ] == iTag )
            mTags.erase( mTags.begin() + i );
    }
}


bool
cEntity::HasTag( const std::string & iTag )
{
    for( int i = 0; i < mTags.size(); ++i )
    {
        if( mTags[ i ] == iTag )
            return  true;
    }

    return  false;
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------ Access
// -------------------------------------------------------------------------------------


bool
cEntity::IsDead() const
{
    return mDead;
}


void
cEntity::SetLoaded()
{
    mLoaded = true;
}


const std::string&
cEntity::ID() const
{
    return  mID;
}


void
cEntity::Destroy()
{
    mWorld->DestroyEntity( this );

    for( int i = 0; i < mObserverSystems.size(); ++i )
    {
        mObserverSystems[ i ]->EntityLost( this );
    }
    mDead = true;
}


void
cEntity::AddSystemObserver( cSystem * iSystem )
{
    mObserverSystems.push_back( iSystem );
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------ Input/Output
// -------------------------------------------------------------------------------------


void
cEntity::SaveXML( tinyxml2::XMLElement * iNode, tinyxml2::XMLDocument* iDocument )
{
    iNode->SetAttribute( "id", mID.c_str() );

    tinyxml2::XMLElement* components = iDocument->NewElement( "components" );

    for( auto it = mComponents.begin(); it != mComponents.end(); ++it )
    {
        // Thing is wherever you do a mComponents[ "something" ], it creates a key value pair : {"something", NULL}
        if( it->value )
        {
            tinyxml2::XMLElement* component = iDocument->NewElement( "component" );
            it->value->SaveXML( component, iDocument );
            components->LinkEndChild( component );
        }
    }

    iNode->LinkEndChild( components );

    tinyxml2::XMLElement* tags = iDocument->NewElement( "tags" );

    for( auto it = mTags.begin(); it != mTags.end(); ++it )
    {
        tinyxml2::XMLElement* tag = iDocument->NewElement( "tag" );
        tag->SetAttribute( "name", it->c_str() );
        tags->LinkEndChild( tag );
    }

    iNode->LinkEndChild( tags );
}


void
cEntity::LoadXML( tinyxml2::XMLElement * iNode )
{
    mID = iNode->Attribute( "id" );
    tinyxml2::XMLElement* components = iNode->FirstChildElement( "components" );

    for( tinyxml2::XMLElement* component = components->FirstChildElement( "component" ); component; component = component->NextSiblingElement() )
    {
        cComponent* comp = cComponentRegistry::Instance()->CreateComponentFromName( component->Attribute( "name" ) );
        if( comp )
        {
            comp->LoadXML( component );
            AddComponent( comp );
        }
    }

    tinyxml2::XMLElement* tags = iNode->FirstChildElement( "tags" );

    for( tinyxml2::XMLElement* tag = tags->FirstChildElement( "tag" ); tag; tag = tag->NextSiblingElement() )
    {
        AddTag( tag->Attribute( "name" ) );
    }
}




// =================================================
// ========== VERSION UNORDERED_MAP ================
// =================================================

//
//
//
//// -------------------------------------------------------------------------------------
//// ------------------------------------------------------------ Construction/Destruction
//// -------------------------------------------------------------------------------------
//
//cEntity::~cEntity()
//{
//    for( auto it = mComponents.begin(); it != mComponents.end(); ++it )
//    {
//        delete  it->second;
//    }
//}
//
//
//cEntity::cEntity( cWorld* iWorld ) :
//    mWorld( iWorld ),
//    mID( "idontknow" + std::to_string( sgEntityCount ) ),
//    mComponents(),
//    mTags(),
//    mObserverSystems(),
//    mLoaded( false ),
//    mDead( false )
//{
//    ++sgEntityCount;
//}
//
//
//cEntity::cEntity( const cEntity& iEntity ) :
//    mWorld( iEntity.mWorld ),
//    mID( iEntity.mID + "c" + std::to_string( sgEntityCount ) ),
//    mComponents(),                                  // This will need to get copied
//    mTags( iEntity.mTags ),                         // This can be copied, as there is no pointer
//    mObserverSystems( iEntity.mObserverSystems ),   // Same systems will observe this entity
//    mLoaded( iEntity.mLoaded ),
//    mDead( iEntity.mDead )
//{
//    for( auto it = iEntity.mComponents.begin(); it != iEntity.mComponents.end(); ++it )
//    {
//        mComponents[ it->first ] = it->second->Clone();
//    }
//}
//
//
//// -------------------------------------------------------------------------------------
//// -------------------------------------------------------------------------------- Copy
//// -------------------------------------------------------------------------------------
//
//
//cEntity*
//cEntity::Clone()
//{
//    return  new cEntity( *this );
//}
//
//
//// -------------------------------------------------------------------------------------
//// -------------------------------------------------------------------------- Components
//// -------------------------------------------------------------------------------------
//
//
//void
//cEntity::AddComponent( cComponent * iComponent )
//{
//    mComponents.insert( std::make_pair( iComponent->Name(), iComponent ) );
//}
//
//
//void
//cEntity::RemoveComponent( cComponent * iComponent )
//{
//    mComponents.erase( iComponent->Name() );
//}
//
//
//void
//cEntity::RemoveComponentByName( const std::string & iComponentName )
//{
//    mComponents.erase( iComponentName );
//}
//
//
//cComponent*
//cEntity::GetComponentByName( const std::string & iComponentName )
//{
//    return  mComponents[ iComponentName ];
//
//}
//
//
//// -------------------------------------------------------------------------------------
//// -------------------------------------------------------------------------------- Tags
//// -------------------------------------------------------------------------------------
//
//
//void
//cEntity::AddTag( const std::string & iTag )
//{
//    mTags.insert( std::make_pair( iTag, true ) );
//}
//
//
//void
//cEntity::RemoveTag( const std::string & iTag )
//{
//    mTags.erase( iTag );
//}
//
//
//bool
//cEntity::HasTag( const std::string & iTag )
//{
//    auto found = mTags.find( iTag );
//    return found != mTags.end();
//}
//
//
//// -------------------------------------------------------------------------------------
//// ------------------------------------------------------------------------------ Access
//// -------------------------------------------------------------------------------------
//
//
//bool
//cEntity::IsDead() const
//{
//    return mDead;
//}
//
//
//void
//cEntity::SetLoaded()
//{
//    mLoaded = true;
//}
//
//
//const std::string&
//cEntity::ID() const
//{
//    return  mID;
//}
//
//
//// -------------------------------------------------------------------------------------
//// ------------------------------------------------------------------------ Input/Output
//// -------------------------------------------------------------------------------------
//
//
//void
//cEntity::SaveXML( tinyxml2::XMLElement * iNode, tinyxml2::XMLDocument* iDocument )
//{
//    iNode->SetAttribute( "id", mID.c_str() );
//
//    tinyxml2::XMLElement* components = iDocument->NewElement( "components" );
//
//    for( auto it = mComponents.begin(); it != mComponents.end(); ++it )
//    {
//        // Thing is wherever you do a mComponents[ "something" ], it creates a key value pair : {"something", NULL}
//        if( it->second )
//        {
//            tinyxml2::XMLElement* component = iDocument->NewElement( "component" );
//            it->second->SaveXML( component, iDocument );
//            components->LinkEndChild( component );
//        }
//    }
//
//    iNode->LinkEndChild( components );
//
//    tinyxml2::XMLElement* tags = iDocument->NewElement( "tags" );
//
//    for( auto it = mTags.begin(); it != mTags.end(); ++it )
//    {
//        // If tag is there and true
//        if( it->second )
//        {
//            tinyxml2::XMLElement* tag = iDocument->NewElement( "tag" );
//            tag->SetAttribute( "name", it->first.c_str() );
//            tags->LinkEndChild( tag );
//        }
//    }
//
//    iNode->LinkEndChild( tags );
//}
//
//
//void
//cEntity::LoadXML( tinyxml2::XMLElement * iNode )
//{
//    mID = iNode->Attribute( "id" );
//    tinyxml2::XMLElement* components = iNode->FirstChildElement( "components" );
//
//    for( tinyxml2::XMLElement* component = components->FirstChildElement( "component" ); component; component = component->NextSiblingElement() )
//    {
//        cComponent* comp = cComponentRegistry::Instance()->CreateComponentFromName( component->Attribute( "name" ) );
//        if( comp )
//        {
//            comp->LoadXML( component );
//            AddComponent( comp );
//        }
//    }
//
//    tinyxml2::XMLElement* tags = iNode->FirstChildElement( "tags" );
//
//    for( tinyxml2::XMLElement* tag = tags->FirstChildElement( "tag" ); tag; tag = tag->NextSiblingElement() )
//    {
//        AddTag( tag->Attribute( "name" ) );
//    }
//}
//

