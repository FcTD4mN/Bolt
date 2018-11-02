#pragma once

#include "ui_ScreenEditor.h"

#include "Core.ECS.Core.Entity.h" // Needed for qmetatype to compile, due to the signal selectionChanged

#include <QModelIndex>

namespace  nQt { namespace  nModels { class cEntityListModel; } }

class cScreenEditor :
    public QWidget
{
    Q_OBJECT

public:
    typedef QWidget tSuperClass;

public:
    ~cScreenEditor();
    cScreenEditor( QWidget *parent = Q_NULLPTR );

public:
    void SetProject( ::nCore::nProject::cProject* iProject );
    void SetPrototypeListModel( ::nQt::nModels::cEntityListModel* iModel );

public slots:
    void  ScreenEditionAsked( const QModelIndex& iIndex );
    void  CurrentPrototypeChanged( const QModelIndex& iIndex );
    void  ToggleGridVisible();
    void  SetSnapGridUp();

        // Project
    void  ProjectLoaded( ::nQt::nModels::cProjectHierarchyModel* iProject );


signals:
    void PrototypeEditionAsked( QModelIndex iModel );
    void  selectionChanged( const std::vector< ::nCore::nECS::nCore::cEntity* >& iSelectedEntities );
    void  forceRefresh();


private:
    Ui::ScreenEditor ui;
};



