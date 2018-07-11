#pragma once


#include <unordered_map>
#include <vector>


namespace nECS {


class cComponent;


class cComponentRegistry
{
public:
    struct sPairComponentFile
    {
        sPairComponentFile() : mComponent( 0 ), mFileName( L"" ){}

        cComponent*     mComponent;
        std::wstring    mFileName;
    };


public:
    // Contruction/Destruction
    ~cComponentRegistry();
    cComponentRegistry();

public:
    // Instance
    static  cComponentRegistry* Instance();

public:
    // Init/Finalize
    void  Initialize( const std::string& iProjectDir );
    void  Finalize();

public:
    // Registry functions
    void  RegisterComponent( cComponent* iComponent );
    void  UnregisterComponent( cComponent* iComponent );
    void  UnregisterComponentByName( const std::string& iName );
    cComponent * CreateComponentFromName( const std::string& iName );

    bool  IsComponentNameAValidComponentInRegistry( const std::string& iName ) const;

public:
    // EDITOR
    int  ComponentCount();
    cComponent* GetComponentAtIndex( int iIndex );
    cComponent* GetComponentByName( const std::string& iName );
    cComponent* GetComponentAssociatedToFileName( const std::wstring& iFileName );

    std::vector< std::string > GetComponentNamesSorted();

    std::wstring        GetComponentFileNameByComponentName( const std::string& iName );
    void                SetComponentFilenameUsingComponentName( const std::string& iEntityName, const std::wstring& iNewFilename );


    bool                IsNameAvailable( const std::string& iID );

private:
    std::string                                             mComponentDir;
    std::unordered_map< std::string, sPairComponentFile >   mComponents;

};


} // namespace ECS

