#include "Core.ECS.Utilities.ComponentRegistry.h"


#include "Core.ECS.Core.Component.h"

#include <algorithm>


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
        delete  it->second.mComponent;
    }
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------ Registry functions
// -------------------------------------------------------------------------------------


void
cComponentRegistry::RegisterComponent( cComponent * iComponent )
{
    mComponents[ iComponent->Name() ].mComponent = iComponent;
    mComponents[ iComponent->Name() ].mFileName = L"";
}


void
cComponentRegistry::UnregisterComponent( cComponent * iComponent )
{
    mComponents.erase( iComponent->Name() );
    // delete or not ?
}


void
cComponentRegistry::UnregisterComponentByName( const std::string & iName )
{
    mComponents.erase( iName );
    // delete or not ?
}


cComponent*
cComponentRegistry::CreateComponentFromName( const std::string & iName )
{
    if( mComponents[ iName ].mComponent != nullptr )
        return  mComponents[ iName ].mComponent->Clone();

    return  0;
}


int
cComponentRegistry::ComponentCount()
{
    return  int(mComponents.size());
}


cComponent*
cComponentRegistry::GetComponentAtIndex( int iIndex )
{
    // Can we do this better than a for loop like this ? like accessing index in unordered map ? even though it's not working like that
    auto iterator = mComponents.begin();
    for( int i = 0; i < iIndex; ++i )
        ++iterator;

    return  iterator->second.mComponent;
}


cComponent*
cComponentRegistry::GetComponentByName( const std::string & iName )
{
    return  mComponents[ iName ].mComponent;
}


std::vector<std::string>
cComponentRegistry::GetComponentNamesSorted()
{
    std::vector<std::string> output;
    output.reserve( mComponents.size() );

    for( auto comp : mComponents )
    {
        if( comp.second.mComponent )
            output.push_back( comp.second.mComponent->Name() );
    }

    std::sort( output.begin(), output.end() );

    return  output;
}


const std::wstring &
cComponentRegistry::GetComponentFileNameByComponentName( const std::string & iName )
{
    return  mComponents[ iName ].mFileName;
}


bool
cComponentRegistry::IsNameAvailable( const std::string & iID )
{
    for( auto comp : mComponents )
    {
        if( comp.second.mComponent->Name() == iID )
            return  true;
    }

    return  true;
}


} // namespace ECS

