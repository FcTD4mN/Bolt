#include "Core.ECS.Utilities.EntityParser.h"


#include "Core.ECS.Core.Entity.h"
#include "Core.ECS.Core.World.h"


#include <SFML/System.hpp>
#include <tinyxml2.h>


#include <iostream>


#include <Windows.h>


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
    WinParseEntityDir( &fileNames );
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
    {
        delete  it->second.mEntity;
    }
}


void
cEntityParser::ReparseAll( cWorld* iWorld )
{
    mEntities.clear();
    Initialize( iWorld );
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------ TOMOVE
// -------------------------------------------------------------------------------------


void
cEntityParser::WinParseEntityDir( std::vector< std::wstring >* oFileNames )
{
    //TODO: Create a file manager class to handle every OS, or find a way with sfml
    WIN32_FIND_DATAW  finddata;

    std::wstring entityDir = L"resources\\Core\\Entities\\*";

    HANDLE f = FindFirstFileW( entityDir.c_str(), &finddata );
    if( f == INVALID_HANDLE_VALUE )
        return;

    std::wstring file( finddata.cFileName );
    if( ( file != L"." ) && ( file != L".." ) )
        (*oFileNames).push_back( L"resources/Core/Entities/" + file );

    while( FindNextFileW( f, &finddata ) )
    {
        std::wstring file( finddata.cFileName );
        if( ( file != L"." ) && ( file != L".." ) )
            (*oFileNames).push_back( L"resources/Core/Entities/" + file );
    }

    FindClose( f );
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
    // Safety approach
    cEntity* proto = mEntities[ iEntityName ].mEntity;
    if( proto )
        return  mEntities[ iEntityName ].mEntity->Clone();
    else
        return  0;
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


cEntity *
cEntityParser::GetPrototypeByName( const std::string& iName )
{
    return  mEntities[ iName ].mEntity;
}


const std::wstring &
cEntityParser::GetEntityFileNameByEntityName( const std::string & iName )
{
    return  mEntities[ iName ].mFileName;
}


unsigned int
cEntityParser::EntityCount() const
{
    return  unsigned int(mEntities.size());
}


bool
cEntityParser::IsIDAvailable( const std::string& iID )
{
     if( mEntities[ iID ].mEntity == nullptr )
            return  true;

    return  false;
}


} // namespace ECS

