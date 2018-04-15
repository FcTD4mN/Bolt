#pragma once

#include "Editor.BoltQtModels.TreeWrapper.h"

#include <QtCore>
#include <vector>

namespace nECS { class cComponent; }
namespace nBase { class cVariant; }

namespace nQt {
namespace nModels {


class cTreeWrapperNodeComponent :
    public cTreeWrapperNode
{
public:
    typedef cTreeWrapperNode tSuperClass;

public:
    ~cTreeWrapperNodeComponent();
    cTreeWrapperNodeComponent( cTreeWrapperNode* iParent, ::nECS::cComponent* iComponent );

public:
    // Type
    virtual std::string Type() const;

private:
    ::nECS::cComponent* mComponent;
};


class cTreeWrapperNodeVariable :
    public cTreeWrapperNode
{
public:
    typedef cTreeWrapperNode tSuperClass;

public:
    ~cTreeWrapperNodeVariable();
    cTreeWrapperNodeVariable( cTreeWrapperNode* iParent, ::nBase::cVariant* iVariant );

public:
    // Type
    virtual std::string Type() const;

private:
    ::nBase::cVariant* mVariant;
};


} // nModels
} // nQT