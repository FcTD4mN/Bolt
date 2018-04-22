#pragma once


#include <string>
#include <vector>
#include <unordered_map>


namespace nECS {


class cEntity;
class cWorld;


class cEntityParser
{
public:
    struct sPairEntityFile
    {
        sPairEntityFile() : mEntity( 0 ), mFileName( L"VOID"){}

        cEntity* mEntity;
        std::wstring mFileName;
    };


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
    void  ReparseAll( cWorld* iWorld );

public:
    // TOMOVE
    void  WinParseEntityDir( std::vector< std::wstring >* oFileNames );

public:
    // Functions
    cEntity* CreateEntityFromFile( const std::string& iFile, cWorld* iWorld );
    cEntity* CreateEntityFromPrototypeMap( const std::string& iEntityName );

public:
    // Accessors--EDITOR mainly
    const std::string&  GetEntityNameAtIndex( int iIndex ) const;
    const std::wstring& GetEntityFileNameAtIndex( int iIndex ) const;

    cEntity*            GetPrototypeByName( const std::string& iName );
    const std::wstring& GetEntityFileNameByEntityName( const std::string& iName );

    unsigned int        EntityCount() const;
    bool                IsIDAvailable( const std::string& iID );

private:
    std::unordered_map< std::string, sPairEntityFile > mEntities;

};


} // namespace ECS

