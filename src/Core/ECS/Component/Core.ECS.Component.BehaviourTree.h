#pragma once

#include "Core.ECS.Core.Component.h"

#include <SFML/Graphics.hpp>
#include <tinyxml2.h>


namespace nCore { namespace nAI { class cBehaviourTree; } }


namespace nCore {
namespace nECS {
namespace nComponent {


class cBehaviourTree :
    public ::nCore::nECS::nCore::cComponentGeneric
{
public:
    typedef  cComponentGeneric  tSuperClass;

public:
    virtual  ~cBehaviourTree();
    cBehaviourTree();
    cBehaviourTree( ::nCore::nAI::cBehaviourTree*  iBehaviourTree );

    void Build();

public:
    // Copy
    virtual  cComponent* Clone() const override;

public:
    ::nCore::nAI::cBehaviourTree*  mBehaviourTree;

};


} // namespace nComponent
} // namespace nECS
} // namespace nCore

