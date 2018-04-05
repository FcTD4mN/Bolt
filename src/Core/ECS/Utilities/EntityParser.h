#pragma once

#include <string>
#include <vector>
#include <unordered_map>

class cEntity;
class cWorld;


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
    void  Initialize( cWorld* iWorld );
    void  Finalize();

public:
    // TOMOVE
    void  WinParseEntityDir();

public:
    // Functions
    cEntity* CreateEntityFromFile( const std::string& iFile, cWorld* iWorld );
    cEntity* CreateEntityFromPrototypeMap( const std::string& iEntityName );

public:
    // Accessors
    const std::string& GetEntityNameAtIndex( int iIndex ) const;
    int EntityCount() const;

private:
    std::vector< std::wstring > mAllEntityFiles;
    std::unordered_map< std::string, cEntity* > mEntities;
};

