#pragma once

#include "Core.ECS.Core.Component.h"

#include <SFML/Graphics.hpp>
#include <tinyxml2.h>


namespace nAI { class cBehaviourTreeV2; }

namespace nECS {


class cBehaviourTree :
    public cComponentGeneric
{
public:
    typedef  cComponentGeneric  tSuperClass;

public:
    virtual  ~cBehaviourTree();
    cBehaviourTree();
    cBehaviourTree( ::nAI::cBehaviourTreeV2* iBehaviourTree );

    void Build();

public:
    // Copy
    virtual  cComponent* Clone() override;

public:
    ::nAI::cBehaviourTreeV2*    mBehaviourTree;
};


} // namespace nECS

