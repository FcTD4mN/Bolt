#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_BoltEditor.h"

namespace  nApplication { class cEditorApplication; }
namespace  nQt { namespace  nModels { class cEntityListModel; } }

namespace  nProject { class cProject; }

namespace  nQt {

class cBoltEditor :
    public QMainWindow
{
    Q_OBJECT

public:
    ~cBoltEditor();
    cBoltEditor(QWidget *parent = Q_NULLPTR);

    void Setup();

public slots:
    void  NewProject();
    void  OpenProject();
    void  PrototypeEditionAsked( QModelIndex );

signals:
    void  CurrentProjectChanged( ::nProject::cProject* iProject );

private:
    Ui::BoltEditorClass ui;
    ::nQt::nModels::cEntityListModel*    mPrototypeListModel;
    ::nApplication::cEditorApplication*  mApp;
};

} //nQt
