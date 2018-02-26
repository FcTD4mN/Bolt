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
    // TOMOVE
    void  WinParseEntityDir();

public:
    // Functions
    static  cEntity* CreateEntityFromFile( const std::string& iFile );

private:
    std::vector< std::wstring > mAllEntityFiles;
    std::unordered_map< std::string, cEntity* > mEntities;
};

