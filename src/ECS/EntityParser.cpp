#include "EntityParser.h"

#include "ECS/Entity.h"

#include "GameMockup/GameApplication.h"

#include "SFML/System.hpp"
#include "tinyxml2.h"

#include <iostream>


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

