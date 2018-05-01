#include "Core.ECS.Utilities.EntityParser.h"


#include "Core.Base.Utilities.h"

#include "Core.ECS.Core.Entity.h"
#include "Core.ECS.Core.World.h"

#include <SFML/System.hpp>
#include <tinyxml2.h>

#include <iostream>
#include <Windows.h>

#include <regex>

namespace nECS {


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------ Construction
// -------------------------------------------------------------------------------------


cEntityParser::~cEntityParser()
{
}


cEntityParser::cEntityParser()
{
}


// -------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------- Instance
// -------------------------------------------------------------------------------------


// static
cEntityParser*
cEntityParser::Instance()
{
    static cEntityParser* sgEntityParser = 0;
    if( !sgEntityParser )
        sgEntityParser = new cEntityParser();

    return  sgEntityParser;
}


// -------------------------------------------------------------------------------------
// ----------------------------------------------------------------- Initialize/Finalize
// -------------------------------------------------------------------------------------


void
cEntityParser::Initialize( cWorld* iWorld )
{
    std::vector< std::wstring > fileNames;
    ::nBase::ParseDirWindows( &fileNames, L"Resources/Core/Entities/" );
    tinyxml2::XMLDocument doc;

    for( int i = 0; i < fileNames.size(); ++i )
    {
        std::wstring file = fileNames[ i ];
        std::string conversion( file.begin(), file.end() );

        tinyxml2::XMLError error = doc.LoadFile( conversion.c_str() );
        if( error )
            continue;

        cEntity* entity = new cEntity( iWorld );
        entity->LoadXML( doc.FirstChildElement( "entity" ) );

        mEntities[ entity->ID() ].mEntity = entity;
        mEntities[ entity->ID() ].mFileName = file;
        doc.Clear();
    }
}


void
cEntityParser::Finalize()
{
    for( auto it = mEntities.begin(); it != mEntities.end(); ++it )
        delete  it->second.mEntity;
}


void
cEntityParser::ReparseAll( cWorld* iWorld )
{
    mEntities.clear();
    Initialize( iWorld );
}


// -------------------------------------------------------------------------------------
// --------------------------------------------------------------------------- Functions
// -------------------------------------------------------------------------------------


cEntity*
cEntityParser::CreateEntityFromFile( const std::string& iFile, cWorld* iWorld )
{
    tinyxml2::XMLDocument doc;
    tinyxml2::XMLError error = doc.LoadFile( iFile.c_str() );
    if( error )
        return  0;

    cEntity* entity = new cEntity( iWorld );
    entity->LoadXML( doc.FirstChildElement( "entity" ) );

    return  entity;
}


cEntity*
cEntityParser::CreateEntityFromPrototypeMap( const std::string& iEntityName )
{
    if( !IsEntityNameAValidEntityInRegistry( iEntityName ) )
        return  0;

    // Safety approach
    cEntity* proto = mEntities[ iEntityName ].mEntity;
    if( proto )
        return  mEntities[ iEntityName ].mEntity->Clone();
    else
        return  0;
}


void
cEntityParser::RegisterEntity( cEntity * iEntity )
{
    mEntities[ iEntity->ID() ].mEntity = iEntity;
    mEntities[ iEntity->ID() ].mFileName = L"";
}


void
cEntityParser::UnregisterEntityByName( const std::string & iName )
{
    mEntities.erase( iName );
}


bool
cEntityParser::IsEntityNameAValidEntityInRegistry( const std::string & iName ) const
{
    auto it = mEntities.find( iName );
    if( it != mEntities.end() )
        return  true;

    return  false;
}


// -------------------------------------------------------------------------------------
// --------------------------------------------------------------------------- Accessors
// -------------------------------------------------------------------------------------


const std::string&
cEntityParser::GetEntityNameAtIndex( int iIndex ) const
{
    // Can we do this better than a for loop like this ? like accessing index in unordered map ? even though it's not working like that
    auto iterator = mEntities.begin();
    for( int i = 0; i < iIndex; ++i )
    {
        ++iterator;
    }
    return  iterator->first;
}

const std::wstring &
cEntityParser::GetEntityFileNameAtIndex( int iIndex ) const
{
    // Can we do this better than a for loop like this ? like accessing index in unordered map ? even though it's not working like that
    auto iterator = mEntities.begin();
    for( int i = 0; i < iIndex; ++i )
        ++iterator;

    return  iterator->second.mFileName;
}


std::vector< std::string >
cEntityParser::GetEntityNamesSorted()
{
    std::vector<std::string> output;
    output.reserve( mEntities.size() );

    for( auto ent : mEntities )
    {
        if( ent.second.mEntity )
            output.push_back( ent.second.mEntity->ID() );
    }

    std::sort( output.begin(), output.end() );

    return  output;
}


std::wstring
cEntityParser::GetEntityFileNameByEntityName( const std::string & iName )
{
    if( !IsEntityNameAValidEntityInRegistry( iName ) )
        return  L"";

    return  mEntities[ iName ].mFileName;
}


void
cEntityParser::SetEntityFilenameUsingEntityName( const std::string & iEntityName, const std::wstring & iNewFilename )
{
    if( !IsEntityNameAValidEntityInRegistry( iEntityName ) )
        return;

    mEntities[ iEntityName ].mFileName = iNewFilename;
}


cEntity*
cEntityParser::GetPrototypeByName( const std::string& iName )
{
    if( !IsEntityNameAValidEntityInRegistry( iName ) )
        return  0;

    return  mEntities[ iName ].mEntity;
}


cEntity*
cEntityParser::GetPrototypeAssociatedToFileName( const std::wstring & iFileName )
{
    for( auto ent : mEntities )
    {
        // Going 2 ifs to simplify the reading
        if( ent.second.mFileName == L"" )
            continue;

        if( ent.second.mFileName == iFileName || iFileName.find( ent.second.mFileName ) != std::string::npos )
            return  ent.second.mEntity;
    }

    return  0;
}


unsigned int
cEntityParser::EntityCount() const
{
    return  unsigned int(mEntities.size());
}


bool
cEntityParser::IsIDAvailable( const std::string& iID )
{
    if( !IsEntityNameAValidEntityInRegistry( iID ) )
        return  true;

     if( mEntities[ iID ].mEntity == nullptr )
            return  true;

    return  false;
}


} // namespace ECS

