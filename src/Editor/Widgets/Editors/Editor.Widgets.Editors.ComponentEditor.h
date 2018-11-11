#pragma once

#include "ui_ComponentEditor.h"

#include <QModelIndex>
#include <QWidget>
#include <QStyledItemDelegate>

#include <memory>

namespace nApplication { class cEditorApplication; }

namespace nCore  { namespace nECS { namespace nCore { class cComponent; } } }
namespace nCore  { namespace nECS { namespace nCore { class cComponentGeneric; } } }

namespace nQt { namespace nModels { class cComponentListModel; } }
namespace nQt { namespace nModels { class cComponentModel; } }
namespace nQt { namespace nModels { class cModelBase; } }

class  cComponentEditorDelegate;


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
    void  ComponentNameChanged();

    void  SaveComponent();
    void  SaveComponentAs();

    void  AddNewVariable();
    void  RemoveVariable();

    void  AddNewComponent();
    void  RemoveComponent();

signals:
	void  showComponentProperties( const std::shared_ptr< ::nQt::nModels::cModelBase >& iModel );

private:
    Ui::ComponentEditor                     ui;
    ::nCore::nECS::nCore::cComponent*       mComponent;
    cComponentEditorDelegate*               mDelegate;
    ::nQt::nModels::cComponentListModel*    mComponentListModel;
};

