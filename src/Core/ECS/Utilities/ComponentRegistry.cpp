#include "ComponentRegistry.h"

#include "ECS/Core/Component.h"

namespace nECS {

// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------ Construction
// -------------------------------------------------------------------------------------


cComponentRegistry::~cComponentRegistry()
{
}


cComponentRegistry::cComponentRegistry()
{
}


// -------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------- Instance
// -------------------------------------------------------------------------------------


cComponentRegistry*
cComponentRegistry::Instance()
{
    static cComponentRegistry* sgComponentsRegistry = 0;
    if( !sgComponentsRegistry )
        sgComponentsRegistry = new cComponentRegistry();

    return  sgComponentsRegistry;
}


// -------------------------------------------------------------------------------------
// ----------------------------------------------------------------------- Init/Finalize
// -------------------------------------------------------------------------------------


void
cComponentRegistry::Initialize()
{
}


void
cComponentRegistry::Finalize()
{
    for( auto it = mComponents.begin(); it != mComponents.end(); ++it )
    {
        delete  it->second;
    }
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------ Registry functions
// -------------------------------------------------------------------------------------


void
cComponentRegistry::RegisterComponent( cComponent * iComponent )
{
    mComponents.insert( std::make_pair( iComponent->Name(), iComponent ) );
}


cComponent*
cComponentRegistry::CreateComponentFromName( const std::string & iName )
{
    return  mComponents[ iName ]->Clone();
}

} //nECS
