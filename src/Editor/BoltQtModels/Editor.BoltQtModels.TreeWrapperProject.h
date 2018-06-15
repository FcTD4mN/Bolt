#pragma once

#include "Editor.BoltQtModels.TreeWrapper.h"

#include <QtCore>
#include <vector>

namespace nECS { class cEntity; }
namespace nECS { class cSystem; }
namespace nProject { class cProject; }
namespace nRender { class cLayer; }
namespace nScreen { class cScreen; }

namespace nQt {
namespace nModels {


class cTreeWrapperNodeHierarchyProject :
    public cTreeWrapperNode
{
public:
    typedef cTreeWrapperNode tSuperClass;

public:
    ~cTreeWrapperNodeHierarchyProject();
    cTreeWrapperNodeHierarchyProject( cTreeWrapperNode* iParent, ::nProject::cProject* iProject );

public:
    // Type
    virtual std::string Type() const;

public:
    // Access/Get
    ::nProject::cProject* Project();

private:
    ::nProject::cProject* mProject;
};


// ----------------
// ----------------
// ----------------


class cTreeWrapperNodeHierarchyScreen :
    public cTreeWrapperNode
{
public:
    typedef cTreeWrapperNode tSuperClass;

public:
    ~cTreeWrapperNodeHierarchyScreen();
    cTreeWrapperNodeHierarchyScreen( cTreeWrapperNode* iParent, ::nScreen::cScreen* iScreen );

public:
    // Type
    virtual std::string Type() const;

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
    public cTreeWrapperNode
{
public:
    typedef cTreeWrapperNode tSuperClass;

public:
    ~cTreeWrapperNodeHierarchyLayer();
    cTreeWrapperNodeHierarchyLayer( cTreeWrapperNode* iParent, ::nRender::cLayer* iLayer );

public:
    // Type
    virtual std::string Type() const;

public:
    // Access/Get
    ::nRender::cLayer* Layer();

private:
    ::nRender::cLayer* mLayer;
};


// -----------------------------------------------------
// -----------------------------------------------------
// -----------------------------------------------------


class cTreeWrapperNodeHierarchyEntity :
    public cTreeWrapperNode
{
public:
    typedef cTreeWrapperNode tSuperClass;

public:
    ~cTreeWrapperNodeHierarchyEntity();
    cTreeWrapperNodeHierarchyEntity( cTreeWrapperNode* iParent, ::nECS::cEntity* iEntity );

public:
    // Type
    virtual std::string Type() const;

public:
    // Access/Get
    ::nECS::cEntity* Entity();

private:
    ::nECS::cEntity* mEntity;
};


// -----------------------------------------------------
// -----------------------------------------------------
// -----------------------------------------------------


class cTreeWrapperNodeHierarchySystem :
    public cTreeWrapperNode
{
public:
    typedef cTreeWrapperNode tSuperClass;

public:
    ~cTreeWrapperNodeHierarchySystem();
    cTreeWrapperNodeHierarchySystem( cTreeWrapperNode* iParent, ::nECS::cSystem* iSystem );

public:
    // Type
    virtual std::string Type() const;

public:
    // Access/Get
    ::nECS::cSystem* System();

private:
    ::nECS::cSystem* mSystem;
};


} // nModels
} // nQT