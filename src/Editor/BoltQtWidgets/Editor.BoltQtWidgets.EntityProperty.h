#pragma once

#include "Editor.BoltQtWidgets.QSFMLCanvas.h"

#include "ui_EntityPropertyWidget.h"

#include <QtCore/QModelIndex>

namespace nApplication { class cEditorApplication; }
namespace nECS { class cEntity; }


class cEntityProperty :
    public QWidget
{
    Q_OBJECT

public:
    typedef QWidget tSuperClass;

public:
    ~cEntityProperty();
    cEntityProperty( QWidget *parent = Q_NULLPTR );

public slots :
    void selectedEntityChanged( QModelIndex iIndex );

private:
    Ui::EntityProperty ui;
    ::nECS::cEntity* mEntity;
};


