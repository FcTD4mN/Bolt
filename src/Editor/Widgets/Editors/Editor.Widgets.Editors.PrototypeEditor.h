#pragma once

#include "ui_PrototypeEditor.h"

#include "Core.Project.Project.h"

#include <QModelIndex>
#include <QWidget>

namespace nApplication { class cEditorApplication; }
namespace nCore  { namespace nECS { namespace nCore { class cEntity; } } }
namespace nQt { namespace nModels { class cProjectHierarchyModel; } }


class cPrototypeEditor :
    public QWidget
{
    Q_OBJECT

public:
    typedef QWidget tSuperClass;

public:
    ~cPrototypeEditor();
    cPrototypeEditor( QWidget *parent = Q_NULLPTR );

public:
    void  SetAllPrototypeListModel( QAbstractItemModel* iModel );

public slots:
    void  PrototypeEditionAsked( QModelIndex );
    void  PrototypeNameChanged( QString iOldName, QString iNewName );

    void  SavePrototype();
    void  SavePrototypeAs();

    void  AddNewPrototype();
    void  RemovePrototype();

    void  ProjectLoaded( ::nQt::nModels::cProjectHierarchyModel* iProject );

signals:
    void  showPrototypeProperties( const std::shared_ptr< ::nQt::nModels::cModelBase >& iModel );


private:
    void  ForceUpdateModel();

private:
    Ui::PrototypeEditor ui;
    ::nCore::nECS::nCore::cEntity* mEntity;
};


