#pragma once

#include "Core.ECS.Core.Component.h"


namespace nCore {
namespace nECS {
namespace nComponent {


class cText :
    public ::nCore::nECS::nCore::cComponentGeneric
{
public:
    typedef  ::nCore::nECS::nCore::cComponentGeneric  tSuperClass;

public:
    virtual  ~cText();
    cText();
    cText( const std::string& iVector );
    cText( const cText& iRHS );

    void Build( const std::string& iString );

public:
    // Copy
    virtual  ::nCore::nECS::nCore::cComponent* Clone() const override;

public:
    // Access / Set
    const std::string& Text();
    void Text( const std::string& iText );
};


} // namespace nComponent
} // namespace nECS
} // namespace nCore

