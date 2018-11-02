#pragma once

#include "ui_ProjectEditor.h"

#include "Core.ECS.Core.Entity.h" // Needed for qmetatype to compile, due to the signal entitySelectionChanged

#include <QWidget>

namespace nCore { namespace nProject { class cProject; } }
namespace nQt { namespace nModels { class cProjectHierarchyModel; } }
namespace nQt { namespace nModels { class cModelBase; } }

class cProjectEditor :
    public QWidget
{
    Q_OBJECT

public:
    typedef QWidget tSuperClass;

public:
    ~cProjectEditor();
    cProjectEditor( QWidget *parent = Q_NULLPTR );

private:
    void  AskFileAndSetProject();

public  slots:
    void  ProjectLoaded( ::nQt::nModels::cProjectHierarchyModel* iProject );
    void  SaveProject();
    void  SaveProjectAs();

    void PrototypeEditionAsked( QModelIndex );
    void ComponentEditionAsked( QModelIndex );
    void ScreenEditionAsked( QModelIndex );

    void ProjectItemClicked( QModelIndex );

signals:
    void prototypeEditionAsked( QModelIndex );
    void componentEditionAsked( QModelIndex );
    void screenEditionAsked( QModelIndex );

    void  showItemProperty( const std::shared_ptr< ::nQt::nModels::cModelBase >& Model );
    void  entitySelectionChanged( const std::vector< ::nCore::nECS::nCore::cEntity* >& iSelectedEntities );
    void  showEntityProperties( const std::shared_ptr< ::nQt::nModels::cModelBase >& iModel );
    void  showEntityAnimation( ::nCore::nECS::nCore::cEntity* iEntity );

private:
    Ui::ProjectEditor ui;
    ::nCore::nProject::cProject* mProject;
};

