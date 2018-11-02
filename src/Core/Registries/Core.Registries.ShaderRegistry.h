#pragma once


#include "Core.Registries.ItemFileRelatedRegistry.h"


namespace nCore { namespace nShader { class  cShader2D; } }


//CHECK:UNUSED


namespace nCore {
namespace nRegistries {


class cShaderRegistry :
    public ::nCore::nBase::cItemFileRelatedRegistry< ::nCore::nShader::cShader2D* >
{
private:
    // Contruction/Destruction
    ~cShaderRegistry();
    cShaderRegistry();

public:
    // Instance
    static  cShaderRegistry* Instance();

public:
    // Init/Finalize
    virtual  void  Initialize() override;
    virtual  void  Finalize() override;
};


} // namespace nRegistries
} // namespace nCore

