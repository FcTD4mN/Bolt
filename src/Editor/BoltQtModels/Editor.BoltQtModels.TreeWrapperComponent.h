#pragma once

#include "Editor.BoltQtModels.TreeWrapper.h"

#include <QtCore>
#include <vector>

namespace nECS { class cEntity; }
namespace nECS { class cComponent; }
namespace nECS { class cComponentGeneric; }

namespace nQt {
namespace nModels {


class cTreeWrapperNodeComponentEditor :
    public cTreeWrapperNode
{
public:
    typedef cTreeWrapperNode tSuperClass;

public:
    ~cTreeWrapperNodeComponentEditor();
    cTreeWrapperNodeComponentEditor( cTreeWrapperNode* iParent, ::nECS::cComponent* iComponent );

public:
    // Type
    virtual std::string Type() const override;
    virtual void AddChild() override; // The add row interface
    virtual  bool RemoveChildrenAtIndex( int iIndex, int iCount ) override;

public:
    ::nECS::cComponentGeneric* Component();

private:
    ::nECS::cComponent* mComponent;
};


// -----------------------------------------------------
// -----------------------------------------------------
// -----------------------------------------------------


class cTreeWrapperNodeComponentEditorVariable :
    public cTreeWrapperNode
{
public:
    typedef cTreeWrapperNode tSuperClass;

public:
    ~cTreeWrapperNodeComponentEditorVariable();
    cTreeWrapperNodeComponentEditorVariable( cTreeWrapperNode* iParent, ::nECS::cComponentGeneric* iComponent, const std::string& iVarName );

public:
    // Type
    virtual std::string Type() const override;
    virtual void AddChild() override; // The add row interface

public:
    // Data
    virtual  bool SetData( int iIndex, const QVariant& iData ) override;

private:
    ::nECS::cComponentGeneric* mComponent;
    std::string mVarName;
};


} // nModels
} // nQT