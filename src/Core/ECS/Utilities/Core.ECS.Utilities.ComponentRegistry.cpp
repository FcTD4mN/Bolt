#include "Core.ECS.Utilities.ComponentRegistry.h"


#include "Core.ECS.Core.Component.h"


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
    if( mComponents[ iName ] != nullptr )
        return  mComponents[ iName ]->Clone();
    return  0;
}


int
cComponentRegistry::GetComponentCount()
{
    return  int(mComponents.size());
}


cComponent *
cComponentRegistry::GetComponentAtIndex( int iIndex )
{
    // Can we do this better than a for loop like this ? like accessing index in unordered map ? even though it's not working like that
    auto iterator = mComponents.begin();
    for( int i = 0; i < iIndex; ++i )
        ++iterator;

    return  iterator->second;
}


} // namespace ECS

