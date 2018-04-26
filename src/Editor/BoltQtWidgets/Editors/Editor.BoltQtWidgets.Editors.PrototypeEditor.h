#pragma once

#include "ui_PrototypeEditor.h"

#include <QModelIndex>
#include <QWidget>

namespace nApplication { class cEditorApplication; }
namespace nECS { class cEntity; }


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

private:
    Ui::PrototypeEditor ui;
    ::nECS::cEntity* mEntity;
};


