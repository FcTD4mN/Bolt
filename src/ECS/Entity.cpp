#include "Entity.h"

#include "ECS/Component.h"

// -------------------------------------------------------------------------------------
// ------------------------------------------------------------ Construction/Destruction
// -------------------------------------------------------------------------------------

cEntity::~cEntity()
{
}


cEntity::cEntity()
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
    return  mComponents.find( iComponentName )->second; // Returns a pair < string, cComponent > -> first is string, second is cComponent
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
    mComponents.erase( iTag );
}


bool
cEntity::HasTag( const std::string & iTag )
{
    auto found = mTags.find( iTag );
    return found != mTags.end();
}
