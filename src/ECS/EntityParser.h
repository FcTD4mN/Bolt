#pragma once

#include <string>
#include <vector>

class cEntity;


class cEntityParser
{
public:
    // Contruction/Destruction
    ~cEntityParser();
    cEntityParser();

public:
    // Instance
    static  cEntityParser* Instance();

public:
    // Initialize/Finalize
    void  Initialize();
    void  Finalize();

public:
    // Functions
    static  cEntity* CreateEntityFromFile( const std::string& iFile );

private:
    std::vector< std::wstring > mEntities;
};

