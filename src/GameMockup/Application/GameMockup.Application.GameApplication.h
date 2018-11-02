#pragma once

#include "Core.Application.Application.h"

namespace nMapping { class cEntityGrid; }


namespace nGameMockup {
namespace nApplication {


class cApplication:
    public ::nCore::nApplication::cApplication
{
public:
    typedef  ::nCore::nApplication::cApplication  tSuperClass;

public:
    cApplication();

public:
    static  cApplication*  App();

public:
    virtual  void  Initialize() override final;
    virtual  void  Finalize() override final;

    virtual  void  BuildProject() override final;
};


} // namespace nApplication

} // namespace nGameMockup
