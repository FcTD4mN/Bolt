#pragma once


#include <unordered_map>


namespace nECS {


class cComponent;


class cComponentRegistry
{
public:
    struct sPairComponentFile
    {
        sPairComponentFile() : mComponent( 0 ), mFileName( L"" ){}

        cComponent*  mComponent;
        std::wstring        mFileName;
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
    void  Initialize();
    void  Finalize();

public:
    // Registry functions
    void  RegisterComponent( cComponent* iComponent );
    void  UnregisterComponent( cComponent* iComponent );
    void  UnregisterComponentByName( const std::string& iName );
    cComponent * CreateComponentFromName( const std::string& iName );

public:
    // EDITOR
    int  ComponentCount();
    cComponent* GetComponentAtIndex( int iIndex );
    cComponent* GetComponentByName( const std::string& iName );

    std::vector< std::string > GetComponentNamesSorted();

    const std::wstring& GetComponentFileNameByComponentName( const std::string& iName );


    bool                IsNameAvailable( const std::string& iID );

private:
    std::unordered_map< std::string, sPairComponentFile > mComponents;

};


} // namespace ECS

