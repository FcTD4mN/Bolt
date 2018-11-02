#pragma once

#include "Core.Registries.ItemFileRelatedRegistry.h"

#include <unordered_map>


namespace nCore { namespace nECS { namespace nCore { class cComponent; } } }


namespace nCore {
namespace nRegistries {


class cComponentRegistry :
    public ::nCore::nBase::cItemFileRelatedRegistry< ::nCore::nECS::nCore::cComponent* >
{
private:
    // Contruction/Destruction
    ~cComponentRegistry();
    cComponentRegistry();

public:
    // Instance
    static  cComponentRegistry* Instance();

public:
    ::nCore::nECS::nCore::cComponent* CreateComponentFromName( const std::string& iName );

public:
    // Init/Finalize
    virtual  void  Initialize() override;
    virtual  void  Finalize() override;

};


} // namespace nRegistries
} // namespace nCore

