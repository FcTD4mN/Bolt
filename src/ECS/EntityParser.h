#pragma once

#include <string>

class cEntity;


class cEntityParser
{
public:
    // Contruction/Destruction
    ~cEntityParser();
    cEntityParser();

public:
    // Functions
    static  cEntity* CreateEntityFromFile( const std::string& iFile );
};

