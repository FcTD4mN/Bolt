#include "Entity.h"

#include "ECS/Component.h"


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
    mID( "idontknow" ),
    mComponents(),
    mTags(),
    mObserverSystems(),
    mLoaded( false ),
    mDead( false )
{
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
    tinyxml2::XMLElement* entity = iDocument->NewElement( "entity" );
    entity->SetAttribute( "id", mID.c_str() );

        tinyxml2::XMLElement* components = iDocument->NewElement( "components" );

        for( auto it = mComponents.begin(); it != mComponents.end(); ++it )
        {
            it->second->SaveXML( components, iDocument );
        }

        entity->LinkEndChild( components );

    iNode->LinkEndChild( entity );
}


void
cEntity::LoadXML( const tinyxml2::XMLElement * iNode )
{
}
