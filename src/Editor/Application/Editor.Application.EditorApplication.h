#pragma once

#include "Core.Application.Application.h"

namespace nECS { class cWorld; }

namespace nApplication {

class cEditorApplication :
    public cApplication
{
public:
    typedef  cApplication  tSuperClass;

public:
    cEditorApplication();

public:
    static cEditorApplication* App();

public:
    void Initialize();
    void Finalize();

public:
    //void Update( unsigned int iDeltaTime );
};

} //nApplication

