#include "Editor.BoltQtModels.TreeWrapperEntity.h"

#include "Core.ECS.Core.Component.h"
#include "Core.Base.Variant.h"

namespace nQt {
namespace nModels {

// ======================================================================
// ============================================================ Hierarchy
// ======================================================================


cTreeWrapperNodeComponent::~cTreeWrapperNodeComponent()
{
}


 cTreeWrapperNodeComponent::cTreeWrapperNodeComponent( cTreeWrapperNode* iParent, ::nECS::cComponent* iComponent ) :
    tSuperClass( iParent ),
     mComponent( iComponent )
{
}


std::string
cTreeWrapperNodeComponent::Type() const
{
    return  "Component";
}


// ===========================================================================
// ===========================================================================
// ===========================================================================


cTreeWrapperNodeVariable::~cTreeWrapperNodeVariable()
{
}


cTreeWrapperNodeVariable::cTreeWrapperNodeVariable( cTreeWrapperNode * iParent, ::nBase::cVariant * iVariant ) :
    tSuperClass( iParent ),
    mVariant( iVariant )
{
}


std::string
cTreeWrapperNodeVariable::Type() const
{
    return  "Variable";
}

} //nModels
} //nQt

