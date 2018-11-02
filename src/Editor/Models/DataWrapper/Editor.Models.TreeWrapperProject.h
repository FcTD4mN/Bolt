#pragma once

#include "Editor.Models.TreeWrapper.h"

#include "Core.ECS.Core.Entity.h"

#include <QtCore>
#include <QIcon>
#include <vector>

namespace nCore  { namespace nECS { namespace nCore { class cComponent; } } }
namespace nECS { class cSystem; }
namespace nCore { namespace nProject { class cProject; } }
namespace nCore { namespace nRender { class cLayer; } }
namespace nScreen { class cScreen; }

namespace nQt {
namespace nModels {



class cTreeWrapperNodeHierarchyBase :
    public cTreeWrapperNode
{
public:
    typedef cTreeWrapperNode tSuperClass;

public:
    virtual ~cTreeWrapperNodeHierarchyBase();
    cTreeWrapperNodeHierarchyBase( cTreeWrapperNode* iParent );

public:
    bool  IsAnAsset() const;
    void  IsAnAsset( bool iIsIt );

    QIcon Icon();

protected:
    bool  mIsAnAsset;
    QIcon mIcon;
};


// ----------------
// ----------------
// ----------------


class cTreeWrapperNodeHierarchyProject :
    public cTreeWrapperNodeHierarchyBase
{
public:
    typedef cTreeWrapperNodeHierarchyBase tSuperClass;

public:
    ~cTreeWrapperNodeHierarchyProject();
    cTreeWrapperNodeHierarchyProject( cTreeWrapperNode* iParent, ::nCore::nProject::cProject* iProject );

public:
    // Type
    virtual std::string Type() const override;

public:
    // Data
    virtual  int DataCount() const override;
    virtual  QVariant DataAtColumn( int iColumn ) override;
    virtual  bool SetData( int iIndex, const QVariant& iData ) override;
    virtual  void AppendData( const QVariant& iData ) override;

public:
    // Access/Get
    ::nCore::nProject::cProject* Project();

private:
    ::nCore::nProject::cProject* mProject;
};


// ----------------
// ----------------
// ----------------


class cTreeWrapperNodeHierarchyScreen :
    public cTreeWrapperNodeHierarchyBase
{
public:
    typedef cTreeWrapperNodeHierarchyBase tSuperClass;

public:
    ~cTreeWrapperNodeHierarchyScreen();
    cTreeWrapperNodeHierarchyScreen( cTreeWrapperNode* iParent, ::nScreen::cScreen* iScreen );

public:
    // Type
    virtual std::string Type() const override;

public:
    // Data
    virtual  int DataCount() const override;
    virtual  QVariant DataAtColumn( int iColumn ) override;
    virtual  bool SetData( int iIndex, const QVariant& iData ) override;
    virtual  void AppendData( const QVariant& iData ) override;

public:
    // Access/Get
    ::nScreen::cScreen* Screen();

private:
    ::nScreen::cScreen* mScreen;
};


// -----------------------------------------------------
// -----------------------------------------------------
// -----------------------------------------------------


class cTreeWrapperNodeHierarchyLayer :
    public cTreeWrapperNodeHierarchyBase
{
public:
    typedef cTreeWrapperNodeHierarchyBase tSuperClass;

public:
    ~cTreeWrapperNodeHierarchyLayer();
    cTreeWrapperNodeHierarchyLayer( cTreeWrapperNode* iParent, ::nCore::nRender::cLayer* iLayer );

public:
    // Type
    virtual std::string Type() const override;

public:
    // Data
    virtual  int DataCount() const override;
    virtual  QVariant DataAtColumn( int iColumn ) override;
    virtual  bool SetData( int iIndex, const QVariant& iData ) override;
    virtual  void AppendData( const QVariant& iData ) override;

public:
    // Access/Get
    ::nCore::nRender::cLayer* Layer();

public:
    int  EntityNodeIndex( const ::nCore::nECS::nCore::cEntity* iEntity );

private:
    ::nCore::nRender::cLayer* mLayer;
};


// -----------------------------------------------------
// -----------------------------------------------------
// -----------------------------------------------------


class cTreeWrapperNodeHierarchyEntity :
    public cTreeWrapperNodeHierarchyBase
{
public:
    typedef cTreeWrapperNodeHierarchyBase tSuperClass;

public:
    ~cTreeWrapperNodeHierarchyEntity();
    cTreeWrapperNodeHierarchyEntity( cTreeWrapperNode* iParent, ::nCore::nECS::nCore::cEntityHandle iEntity );
    cTreeWrapperNodeHierarchyEntity( ::nCore::nECS::nCore::cEntityHandle iEntity );

public:
    // Type
    virtual std::string Type() const override;

public:
    // Data
    virtual  int DataCount() const override;
    virtual  QVariant DataAtColumn( int iColumn ) override;
    virtual  bool SetData( int iIndex, const QVariant& iData ) override;
    virtual  void AppendData( const QVariant& iData ) override;

public:
    // Access/Get
    ::nCore::nECS::nCore::cEntityHandle Entity();

private:
    ::nCore::nECS::nCore::cEntityHandle mEntity;
};


// -----------------------------------------------------
// -----------------------------------------------------
// -----------------------------------------------------


class cTreeWrapperNodeHierarchyComponent :
    public cTreeWrapperNodeHierarchyBase
{
public:
    typedef cTreeWrapperNodeHierarchyBase tSuperClass;

public:
    ~cTreeWrapperNodeHierarchyComponent();
    cTreeWrapperNodeHierarchyComponent( cTreeWrapperNode* iParent, ::nCore::nECS::nCore::cComponent* iComponent );
    cTreeWrapperNodeHierarchyComponent( ::nCore::nECS::nCore::cComponent* iComponent );

public:
    // Type
    virtual std::string Type() const override;

public:
    // Data
    virtual  int DataCount() const override;
    virtual  QVariant DataAtColumn( int iColumn ) override;
    virtual  bool SetData( int iIndex, const QVariant& iData ) override;
    virtual  void AppendData( const QVariant& iData ) override;

public:
    // Access/Get
    ::nCore::nECS::nCore::cComponent* Component();

private:
    ::nCore::nECS::nCore::cComponent* mComponent;
};


// -----------------------------------------------------
// -----------------------------------------------------
// -----------------------------------------------------


class cTreeWrapperNodeHierarchySystem :
    public cTreeWrapperNodeHierarchyBase
{
public:
    typedef cTreeWrapperNodeHierarchyBase tSuperClass;

public:
    ~cTreeWrapperNodeHierarchySystem();
    cTreeWrapperNodeHierarchySystem( cTreeWrapperNode* iParent, ::nCore::nECS::nCore::cSystem* iSystem );

public:
    // Type
    virtual std::string Type() const;

public:
    // Access/Get
    ::nCore::nECS::nCore::cSystem*    System();
    void                System( ::nCore::nECS::nCore::cSystem* iSystem );

private:
    ::nCore::nECS::nCore::cSystem* mSystem;
};


} // nModels
} // nQT