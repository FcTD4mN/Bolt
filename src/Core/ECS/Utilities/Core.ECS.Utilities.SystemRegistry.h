#pragma once


#include <unordered_map>


namespace nECS {


class cSystem;


class cSystemRegistry
{
public:
    struct sPairSystemFile
    {
        sPairSystemFile() : mSystem( 0 ), mFileName( L"" ){}

        cSystem*        mSystem;
        std::wstring    mFileName;
    };


public:
    // Contruction/Destruction
    ~cSystemRegistry();
    cSystemRegistry();

public:
    // Instance
    static  cSystemRegistry* Instance();

public:
    // Init/Finalize
    void  Initialize( const std::string& iProjectDir );
    void  Finalize();

public:
    // Registry functions
    void  RegisterSystem( cSystem* iSystem );
    void  UnregisterSystem( cSystem* iSystem );
    void  UnregisterSystemByName( const std::string& iName );
    cSystem* GetSystemByName( const std::string& iName );

    bool  IsSystemNameAValidSystemInRegistry( const std::string& iName ) const;

public:
    // EDITOR
    int  SystemCount();
    cSystem* GetSystemAtIndex( int iIndex );
    cSystem* GetSystemAssociatedToFileName( const std::wstring& iFileName );

    std::vector< std::string > GetSystemNamesSorted();

    std::wstring        GetSystemFileNameBySystemName( const std::string& iName );
    void                SetSystemFilenameUsingSystemName( const std::string& iEntityName, const std::wstring& iNewFilename );


    bool                IsNameAvailable( const std::string& iID );

private:
    std::string                                        mSystemsDir;
    std::unordered_map< std::string, sPairSystemFile > mSystems;

};


} // namespace ECS

