#include "EntityParser.h"

#include "ECS/Entity.h"

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
    //TODO: Create a file manager class to handle every OS, or find a way with sfml
    WIN32_FIND_DATAW  finddata;

    std::wstring entityDir = L"resources\\Entities\\*";

    HANDLE f = FindFirstFileW( entityDir.c_str(), &finddata );
    if( f == INVALID_HANDLE_VALUE )
        return;

    std::wstring file( finddata.cFileName );
    if( ( file != L"." ) && ( file != L".." ) )
        mEntities.push_back( file );

    while( FindNextFileW( f, &finddata ) )
    {
        std::wstring file( finddata.cFileName );
        if( ( file != L"." ) && ( file != L".." ) )
            mEntities.push_back( file );
    }

    FindClose( f );
}


void
cEntityParser::Finalize()
{
}


// -------------------------------------------------------------------------------------
// --------------------------------------------------------------------------- Functions
// -------------------------------------------------------------------------------------


// static
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

