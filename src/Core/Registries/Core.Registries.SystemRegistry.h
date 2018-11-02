#pragma once

#include "Core.Registries.ItemFileRelatedRegistry.h"

#include <unordered_map>


namespace nCore { namespace nECS { namespace nCore { class cSystem; } } }


namespace nCore {
namespace nRegistries {


class cSystemRegistry :
    public ::nCore::nBase::cItemFileRelatedRegistry< ::nCore::nECS::nCore::cSystem* >
{
private:
    // Contruction/Destruction
    ~cSystemRegistry();
    cSystemRegistry();

public:
    // Instance
    static  cSystemRegistry* Instance();

    ::nCore::nECS::nCore::cSystem* CreateSystemFromName( const std::string& iName );

public:
    // Init/Finalize
    virtual  void  Initialize() override;
    virtual  void  Finalize() override;

};


} // namespace nUtilities
} // namespace nRegistries

