#include "Core.ECS.Utilities.SystemRegistry.h"


#include "Core.Base.Utilities.h"

#include "Core.ECS.Core.System.h"
#include "Core.ECS.System.AnimationRenderer.h"
#include "Core.ECS.System.InputConverter.h"
#include "Core.ECS.System.SimplerRenderer.h"
#include "Core.ECS.System.SimplePhysics.h"
#include "Core.ECS.System.SightSystem.h"
#include "Core.ECS.System.SoundMixer.h"
#include "Core.ECS.System.SoundOcclusion.h"
#include "Core.ECS.System.BehaviourTreeSystem.h"

#include <tinyxml2.h>
#include <algorithm>


namespace nECS {


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------ Construction
// -------------------------------------------------------------------------------------


cSystemRegistry::~cSystemRegistry()
{
}


cSystemRegistry::cSystemRegistry()
{
}


// -------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------- Instance
// -------------------------------------------------------------------------------------


cSystemRegistry*
cSystemRegistry::Instance()
{
    static cSystemRegistry* sgSystemsRegistry = 0;
    if( !sgSystemsRegistry )
        sgSystemsRegistry = new cSystemRegistry();

    return  sgSystemsRegistry;
}


// -------------------------------------------------------------------------------------
// ----------------------------------------------------------------------- Init/Finalize
// -------------------------------------------------------------------------------------


void
cSystemRegistry::Initialize( const std::string& iProjectDir )
{
    // Registering all basic systems
    RegisterSystem( new ::nECS::cSimplerRenderer() );
    RegisterSystem( new ::nECS::cInputConverter() );
    RegisterSystem( new ::nECS::cSimplePhysics() );
    RegisterSystem( new ::nECS::cAnimationRenderer() );
    RegisterSystem( new ::nECS::cSightSystem() );
    RegisterSystem( new ::nECS::cSoundOcclusion() );
    RegisterSystem( new ::nECS::cSoundMixer() );
    RegisterSystem( new ::nECS::cBehaviourTreeSystem() );

    //TODO:
    // Parsing file based systems
    mSystemsDir = iProjectDir + "/Assets/Systems";
    std::wstring path( mSystemsDir.begin(), mSystemsDir.end() );

    std::vector< std::wstring > fileNames;
    ::nBase::ParseDirWindows( &fileNames, path );
    tinyxml2::XMLDocument doc;

    for( int i = 0; i < fileNames.size(); ++i )
    {
        std::wstring file = fileNames[ i ];
        std::string conversion( file.begin(), file.end() );

        tinyxml2::XMLError error = doc.LoadFile( conversion.c_str() );
        if( error )
            continue;

        // This will be SystemPython instead of SystemGeneric
        //cSystemGeneric* System = new cSystemGeneric( conversion );
        //System->LoadXML( doc.FirstChildElement( "System" ) );

        //mSystems[ System->Name() ].mSystem = System;
        //mSystems[ System->Name() ].mFileName = file;
        //doc.Clear();
    }
}


void
cSystemRegistry::Finalize()
{
    for( auto it = mSystems.begin(); it != mSystems.end(); ++it )
        delete  it->second.mSystem;
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------ Registry functions
// -------------------------------------------------------------------------------------


void
cSystemRegistry::RegisterSystem( cSystem * iSystem )
{
    mSystems[ iSystem->Name() ].mSystem = iSystem;
    mSystems[ iSystem->Name() ].mFileName = L"";
}


void
cSystemRegistry::UnregisterSystem( cSystem * iSystem )
{
    mSystems.erase( iSystem->Name() );
    // delete or not ?
}


void
cSystemRegistry::UnregisterSystemByName( const std::string & iName )
{
    mSystems.erase( iName );
    // delete or not ?
}


cSystem*
cSystemRegistry::GetSystemByName( const std::string & iName )
{
    if( !IsSystemNameAValidSystemInRegistry( iName ) )
        return  0;

    return  mSystems[ iName ].mSystem;
}


bool
cSystemRegistry::IsSystemNameAValidSystemInRegistry( const std::string & iName ) const
{
    auto it = mSystems.find( iName );
    if( it != mSystems.end() )
        return  true;

    return  false;
}


int
cSystemRegistry::SystemCount()
{
    return  int(mSystems.size());
}


cSystem*
cSystemRegistry::GetSystemAtIndex( int iIndex )
{
    // Can we do this better than a for loop like this ? like accessing index in unordered map ? even though it's not working like that
    auto iterator = mSystems.begin();
    for( int i = 0; i < iIndex; ++i )
        ++iterator;

    return  iterator->second.mSystem;
}


cSystem*
cSystemRegistry::GetSystemAssociatedToFileName( const std::wstring & iFileName )
{
    for( auto ent : mSystems )
    {
        // Going 2 ifs to simplify the reading
        if( ent.second.mFileName == L"" )
            continue;

        if( ent.second.mFileName == iFileName || iFileName.find( ent.second.mFileName ) != std::string::npos )
            return  ent.second.mSystem;
    }

    return  0;
}


std::vector<std::string>
cSystemRegistry::GetSystemNamesSorted()
{
    std::vector<std::string> output;
    output.reserve( mSystems.size() );

    for( auto comp : mSystems )
    {
        if( comp.second.mSystem )
            output.push_back( comp.second.mSystem->Name() );
    }

    std::sort( output.begin(), output.end() );

    return  output;
}


std::wstring
cSystemRegistry::GetSystemFileNameBySystemName( const std::string & iName )
{
    if( !IsSystemNameAValidSystemInRegistry( iName ) )
        return  L"";

    return  mSystems[ iName ].mFileName;
}


void
cSystemRegistry::SetSystemFilenameUsingSystemName( const std::string & iEntityName, const std::wstring & iNewFilename )
{
    if( !IsSystemNameAValidSystemInRegistry( iEntityName ) )
        return;

    mSystems[ iEntityName ].mFileName = iNewFilename;
}


bool
cSystemRegistry::IsNameAvailable( const std::string & iID )
{
    for( auto comp : mSystems )
    {
        if( comp.second.mSystem->Name() == iID )
            return  true;
    }

    return  true;
}


} // namespace ECS

