#include "EntityParser.h"

#include "ECS/Core/Entity.h"

#include "GameMockup/GameApplication.h"

#include "SFML/System.hpp"
#include "tinyxml2.h"

#include <iostream>
#include <Windows.h>


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
cEntityParser::Initialize()
{
    WinParseEntityDir();
    tinyxml2::XMLDocument doc;

    for( int i = 0; i < mAllEntityFiles.size(); ++i )
    {
        std::wstring file = mAllEntityFiles[ i ];
        std::string conversion( file.begin(), file.end() );

        tinyxml2::XMLError error = doc.LoadFile( conversion.c_str() );
        if( error )
            continue;

        cEntity* entity = new cEntity( cGameApplication::App()->World() );
        entity->LoadXML( doc.FirstChildElement( "entity" ) );

        mEntities[ entity->ID() ] = entity;
        doc.Clear();
    }
}


void
cEntityParser::Finalize()
{
    for( auto it = mEntities.begin(); it != mEntities.end(); ++it )
    {
        delete  it->second;
    }
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------ TOMOVE
// -------------------------------------------------------------------------------------


void
cEntityParser::WinParseEntityDir()
{
    //TODO: Create a file manager class to handle every OS, or find a way with sfml
    WIN32_FIND_DATAW  finddata;

    std::wstring entityDir = L"resources\\Core\\Entities\\*";

    HANDLE f = FindFirstFileW( entityDir.c_str(), &finddata );
    if( f == INVALID_HANDLE_VALUE )
        return;

    std::wstring file( finddata.cFileName );
    if( ( file != L"." ) && ( file != L".." ) )
        mAllEntityFiles.push_back( L"resources/Core/Entities/" + file );

    while( FindNextFileW( f, &finddata ) )
    {
        std::wstring file( finddata.cFileName );
        if( ( file != L"." ) && ( file != L".." ) )
            mAllEntityFiles.push_back( L"resources/Core/Entities/" + file );
    }

    FindClose( f );
}


// -------------------------------------------------------------------------------------
// --------------------------------------------------------------------------- Functions
// -------------------------------------------------------------------------------------


cEntity*
cEntityParser::CreateEntityFromFile( const std::string& iFile )
{
    tinyxml2::XMLDocument doc;
    tinyxml2::XMLError error = doc.LoadFile( iFile.c_str() );
    if( error )
        return  0;

    cEntity* entity = new cEntity( cGameApplication::App()->World() );
    entity->LoadXML( doc.FirstChildElement( "entity" ) );

    return  entity;
}


cEntity*
cEntityParser::CreateEntityFromPrototypeMap( const std::string& iEntityName )
{
    // Safety approach
    cEntity* proto = mEntities[ iEntityName ];
    if( proto )
        return  mEntities[ iEntityName ]->Clone();
    else
        return  0;
}

