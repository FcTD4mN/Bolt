#pragma once

#include "Editor.Models.TreeWrapper.h"

#include "Core.ECS.Core.Entity.h"

#include <QtCore>
#include <vector>

namespace nCore  { namespace nECS { namespace nCore { class cComponent; } } }
namespace nCore  { namespace nECS { namespace nCore { class cComponentGeneric; } } }

namespace nQt {
namespace nModels {


class cTreeWrapperNodeEntity :
    public cTreeWrapperNode
{
public:
    typedef cTreeWrapperNode tSuperClass;

public:
    virtual ~cTreeWrapperNodeEntity();
    cTreeWrapperNodeEntity( cTreeWrapperNode* iParent, ::nCore::nECS::nCore::cEntityHandle iEntity );

public:
    // Type
    virtual std::string Type() const override;
    virtual  int DataCount() const override;
    virtual  QVariant DataAtColumn( int iColumn ) override;
    virtual  bool SetData( int iIndex, const QVariant& iData ) override;


public:
    ::nCore::nECS::nCore::cEntityHandle Entity();

private:
    ::nCore::nECS::nCore::cEntityHandle mEntity;
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
    virtual ~cTreeWrapperNodeComponent();
    cTreeWrapperNodeComponent( cTreeWrapperNode* iParent, ::nCore::nECS::nCore::cComponent* iComponent );

public:
    // Type
    virtual std::string Type() const;


public:
    ::nCore::nECS::nCore::cComponentGeneric* Component();

private:
    ::nCore::nECS::nCore::cComponent* mComponent;
};


// ----------------
// ----------------
// ----------------


class cTreeWrapperNodeTag :
    public cTreeWrapperNode
{
public:
    typedef cTreeWrapperNode tSuperClass;

public:
    virtual ~cTreeWrapperNodeTag();
    cTreeWrapperNodeTag( cTreeWrapperNode* iParent, ::nCore::nECS::nCore::cEntityHandle iEntity, int iTagIndex );

public:
    // Type
    virtual std::string Type() const;
    virtual  bool SetData( int iIndex, const QVariant& iData );

public:
    const std::string Tag();
    void  SetTagIndex( int iIndex );

private:
    ::nCore::nECS::nCore::cEntityHandle   mEntity;
    int                     mTagIndex;
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
    virtual ~cTreeWrapperNodeVariable();
    cTreeWrapperNodeVariable( cTreeWrapperNode* iParent, ::nCore::nECS::nCore::cComponentGeneric* iComponent, int iVarIndex );

public:
    // Type
    virtual std::string Type() const override;
    virtual  int DataCount() const override;
    virtual  QVariant DataAtColumn( int iColumn ) override;

public:
    // Data
    virtual  bool SetData( int iIndex, const QVariant& iData ) override;

private:
    ::nCore::nECS::nCore::cComponentGeneric* mComponent;
    int mVarIndex;
};


} // nModels
} // nQT