#include "Entity.h"

#include "ECS/Component.h"

#include "ECS/ComponentRegistry.h"

static unsigned int sgEntityCount = 0;


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------ Construction/Destruction
// -------------------------------------------------------------------------------------

cEntity::~cEntity()
{
    for( auto it = mComponents.begin(); it != mComponents.end(); ++it )
    {
        delete  it->second;
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
    ++sgEntityCount;
}


// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------- Components
// -------------------------------------------------------------------------------------


void
cEntity::AddComponent( cComponent * iComponent )
{
    mComponents.insert( std::make_pair( iComponent->Name(), iComponent ) );
}


void
cEntity::RemoveComponent( cComponent * iComponent )
{
    mComponents.erase( iComponent->Name() );
}


void
cEntity::RemoveComponentByName( const std::string & iComponentName )
{
    mComponents.erase( iComponentName );
}


cComponent*
cEntity::GetComponentByName( const std::string & iComponentName )
{
    return  mComponents[ iComponentName ];

}


// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------- Tags
// -------------------------------------------------------------------------------------


void
cEntity::AddTag( const std::string & iTag )
{
    mTags.insert( std::make_pair( iTag, true ) );
}


void
cEntity::RemoveTag( const std::string & iTag )
{
    mTags.erase( iTag );
}


bool
cEntity::HasTag( const std::string & iTag )
{
    auto found = mTags.find( iTag );
    return found != mTags.end();
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
        if( it->second )
        {
            tinyxml2::XMLElement* component = iDocument->NewElement( "component" );
            it->second->SaveXML( component, iDocument );
            components->LinkEndChild( component );
        }
    }

    iNode->LinkEndChild( components );

    tinyxml2::XMLElement* tags = iDocument->NewElement( "tags" );

    for( auto it = mTags.begin(); it != mTags.end(); ++it )
    {
        // If tag is there and true
        if( it->second )
        {
            tinyxml2::XMLElement* tag = iDocument->NewElement( "tag" );
            tag->SetAttribute( "name", it->first.c_str() );
            tags->LinkEndChild( tag );
        }
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
