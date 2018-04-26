#pragma once

#include "Editor.BoltQtModels.TreeWrapper.h"

#include <QtCore>
#include <vector>

namespace nECS { class cEntity; }
namespace nECS { class cComponent; }
namespace nECS { class cComponentGeneric; }

namespace nQt {
namespace nModels {


class cTreeWrapperNodeEntity :
    public cTreeWrapperNode
{
public:
    typedef cTreeWrapperNode tSuperClass;

public:
    ~cTreeWrapperNodeEntity();
    cTreeWrapperNodeEntity( cTreeWrapperNode* iParent, ::nECS::cEntity* iEntity );

public:
    // Type
    virtual std::string Type() const;

public:
    ::nECS::cEntity* Entity();

private:
    ::nECS::cEntity* mEntity;
};


// ----------------
// ----------------
// ----------------


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

public:
    ::nECS::cComponentGeneric* Component();

private:
    ::nECS::cComponent* mComponent;
};


// -----------------------------------------------------
// -----------------------------------------------------
// -----------------------------------------------------


class cTreeWrapperNodeVariable :
    public cTreeWrapperNode
{
public:
    typedef cTreeWrapperNode tSuperClass;

public:
    ~cTreeWrapperNodeVariable();
    cTreeWrapperNodeVariable( cTreeWrapperNode* iParent, ::nECS::cComponentGeneric* iComponent, int iVarIndex );

public:
    // Type
    virtual std::string Type() const;

public:
    // Data
    virtual  bool SetData( int iIndex, const QVariant& iData ) override;

private:
    ::nECS::cComponentGeneric* mComponent;
    int mVarIndex;
};


} // nModels
} // nQT