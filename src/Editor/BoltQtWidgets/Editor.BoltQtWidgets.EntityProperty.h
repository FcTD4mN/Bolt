#pragma once

#include "Editor.BoltQtWidgets.QSFMLCanvas.h"

#include "ui_EntityPropertyWidget.h"

#include <QtCore/QModelIndex>

namespace nApplication { class cEditorApplication; }
namespace nECS { class cEntity; }
namespace  nQt { namespace  nModels { class cEntityModel; } }


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
    void selectedEntitiesChanged( ::nECS::cEntity* iEntity );
    void addEmptyComponent();
    void removeComponent();

private:
    Ui::EntityProperty ui;
    ::nECS::cEntity* mEntity;
    ::nQt::nModels::cEntityModel* mModel;
};


