#pragma once

#include "Core.Screen.Screen.h"

namespace nScreen {

class cPremierScreen:
    public cScreen
{
public:
    typedef  cScreen  tSuperClass;

public:
    // Contruction/Destruction
    virtual  ~cPremierScreen();
    cPremierScreen();

public:
    virtual  void  Initialize() override;

public:
    virtual  void  AdditionnalBuildScreen() override;
};

} //nScreen

