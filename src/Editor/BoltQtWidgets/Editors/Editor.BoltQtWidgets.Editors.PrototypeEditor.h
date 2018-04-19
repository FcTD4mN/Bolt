#pragma once

#include "Editor.BoltQtWidgets.QSFMLCanvas.h"

#include "ui_PrototypeEditor.h"

#include <QtCore/QModelIndex>

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

private:
    Ui::PrototypeEditor ui;
    ::nECS::cEntity* mEntity;
};


