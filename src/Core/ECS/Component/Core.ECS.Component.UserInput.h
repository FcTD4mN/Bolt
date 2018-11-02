#pragma once


#include "Core.ECS.Core.Component.h"


#include <SFML/Graphics.hpp>


namespace nCore {
namespace nECS {
namespace nComponent {


class cUserInput :
    public ::nCore::nECS::nCore::cComponent
{
public:
    typedef  ::nCore::nECS::nCore::cComponent  tSuperClass;

public:
    virtual  ~cUserInput();
    cUserInput();
    cUserInput( const cUserInput& iUserInput );

public:
    // Copy
    virtual  ::nCore::nECS::nCore::cComponent* Clone() const override;

public:
    bool ContainsAction( const std::string& iAction ) const;

public:
    std::vector< std::string > mActions;
};


} // namespace nComponent
} // namespace nECS
} // namespace nCore

