#pragma once

#include <string>

class cComponent
{

public:
    // Contruction/Destruction
    virtual  ~cComponent() = 0;
    cComponent( const std::string& iName );

public:
    // Access/Get
    const  std::string&  Name() const;

protected:
    std::string mName;


};

