#include "EntityParser.h"

#include "SFML/System.hpp"

#include <iostream>

#define BUFFER_SIZE 1024

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
cEntityParser::CreateEntityFromFile( const std::string & iFile )
{
    sf::FileInputStream file;

    if( !file.open( iFile ) )
        return  nullptr;

    int fileSize = file.getSize();

    char buffer[ BUFFER_SIZE ];
    memset( buffer, '\0', BUFFER_SIZE );
    int readSize = BUFFER_SIZE > fileSize ? fileSize : BUFFER_SIZE;

    sf::Int64 nbRead = file.read( buffer, readSize );
    std::string line = "";

    int i = 0;
    while( (buffer[ i ] != '\n' && buffer[ i ] != '\r') && i < BUFFER_SIZE )
    {
        line += buffer[ i ];
        ++i;
    }

    std::cout << "-" << line.c_str() << "-" << std::endl;

    return  0;
}

