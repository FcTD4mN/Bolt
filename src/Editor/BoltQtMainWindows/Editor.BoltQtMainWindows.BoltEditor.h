#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_BoltEditor.h"

namespace  nApplication { class cEditorApplication; }
namespace  nQt { namespace  nModels { class cEntityListModel; } }

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
    void  SaveLevel();
    void  LoadLevel();
    void  PrototypeEditionAsked( QModelIndex );

private:
    Ui::BoltEditorClass ui;
    ::nQt::nModels::cEntityListModel*    mModel;
    ::nApplication::cEditorApplication*  mApp;
};

} //nQt
