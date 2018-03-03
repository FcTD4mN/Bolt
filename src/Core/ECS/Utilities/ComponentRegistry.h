#pragma once

#include <unordered_map>

class cComponent;

class cComponentRegistry
{
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
    cComponent * CreateComponentFromName( const std::string& iName );

private:
    std::unordered_map< std::string, cComponent* > mComponents;
};

