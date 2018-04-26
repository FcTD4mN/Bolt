#pragma once

#include "ui_ComponentEditor.h"

#include <QModelIndex>
#include <QWidget>

namespace nApplication { class cEditorApplication; }

namespace nECS { class cComponent; }
namespace nECS { class cComponentGeneric; }


class cComponentEditor :
    public QWidget
{
    Q_OBJECT

public:
    typedef QWidget tSuperClass;

public:
    ~cComponentEditor();
    cComponentEditor( QWidget *parent = Q_NULLPTR );

public:
    void  SetAllComponentListModel( QAbstractItemModel* iModel );

public slots:
    void  ComponentEditionAsked( QModelIndex );
    //void  ComponentNameChanged( QString iOldName, QString iNewName );

    //void  SaveComponent();
    //void  SaveComponentAs();

    //void  AddNewComponent();
    //void  RemoveComponent();

private:
    Ui::ComponentEditor         ui;
    ::nECS::cComponent*  mComponent;
};


