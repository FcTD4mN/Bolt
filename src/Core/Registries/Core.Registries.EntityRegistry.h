#pragma once


#include "Core.Registries.ItemFileRelatedRegistry.h"


#include <unordered_map>

namespace nCore { namespace nECS { namespace nCore { class cEntity; } } }
namespace nCore { namespace nECS { namespace nCore { class cWorld;  } } }


namespace nCore {
namespace nRegistries {


class cEntityRegistry :
    public ::nCore::nBase::cItemFileRelatedRegistry< ::nCore::nECS::nCore::cEntity* >
{
private:
    // Contruction/Destruction
    ~cEntityRegistry();
    cEntityRegistry();

public:
    // Instance
    static  cEntityRegistry* Instance();

private:
    void  ParseFolder();

public:
    ::nCore::nECS::nCore::cEntity*    CreateEntityFromFile( const std::string& iFile, ::nCore::nECS::nCore::cWorld* iWorld );
    ::nCore::nECS::nCore::cEntity*    CreateEntityFromPrototypeMap( const std::string& iEntityName );
    bool        IsIDAvailable( const std::string& iID );

public:
    // Init/Finalize
    virtual  void  Initialize() override;
    virtual  void  Finalize() override;

};


} // namespace nRegistries
} // namespace nCore

