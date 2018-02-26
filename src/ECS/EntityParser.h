#pragma once

#include <string>
#include <vector>
#include <unordered_map>

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
    cEntity* CreateEntityFromFile( const std::string& iFile );
    cEntity* CreateEntityFromPrototypeMap( const std::string& iEntityName );

private:
    std::vector< std::wstring > mAllEntityFiles;
    std::unordered_map< std::string, cEntity* > mEntities;
};

