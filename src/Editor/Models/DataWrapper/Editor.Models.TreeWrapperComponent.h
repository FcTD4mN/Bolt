#pragma once

#include "Editor.Models.TreeWrapper.h"

#include <QtCore>
#include <vector>

namespace nCore  { namespace nECS { namespace nCore { class cEntity; } } }
namespace nCore  { namespace nECS { namespace nCore { class cComponent; } } }
namespace nCore  { namespace nECS { namespace nCore { class cComponentGeneric; } } }

namespace nQt {
namespace nModels {


class cTreeWrapperNodeComponentEditor :
    public cTreeWrapperNode
{
public:
    typedef cTreeWrapperNode tSuperClass;

public:
    virtual ~cTreeWrapperNodeComponentEditor();
    cTreeWrapperNodeComponentEditor( cTreeWrapperNode* iParent, ::nCore::nECS::nCore::cComponent* iComponent );

public:
    // Type
    virtual std::string Type() const override;
    virtual void AddChild() override; // The add row interface
    virtual  bool RemoveChildrenAtIndex( int iIndex, int iCount ) override;
    virtual  int DataCount() const override;
    virtual  QVariant DataAtColumn( int iColumn ) override;
    virtual  bool SetData( int iIndex, const QVariant& iData ) override;

public:
    ::nCore::nECS::nCore::cComponentGeneric* Component();

private:
    ::nCore::nECS::nCore::cComponent* mComponent;
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
    virtual ~cTreeWrapperNodeComponentEditorVariable();
    cTreeWrapperNodeComponentEditorVariable( cTreeWrapperNode* iParent, ::nCore::nECS::nCore::cComponentGeneric* iComponent, const std::string& iVarName );

public:
    // Type
    virtual std::string Type() const override;
    virtual void AddChild() override; // The add row interface

public:
    // Data
    virtual  bool SetData( int iIndex, const QVariant& iData ) override;

private:
    ::nCore::nECS::nCore::cComponentGeneric* mComponent;
    std::string mVarName;
};


} // nModels
} // nQT