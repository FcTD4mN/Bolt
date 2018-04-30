#pragma once

#include "ui_ComponentEditor.h"

#include <QModelIndex>
#include <QWidget>
#include <QStyledItemDelegate>

namespace nApplication { class cEditorApplication; }

namespace nECS { class cComponent; }
namespace nECS { class cComponentGeneric; }

namespace nQt { namespace nModels { class cComponentListModel; } }

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

private:
    Ui::ComponentEditor         ui;
    ::nECS::cComponent*         mComponent;
    cComponentEditorDelegate*   mDelegate;
    ::nQt::nModels::cComponentListModel*  mComponentListModel;
};


// ==================================================================
// ==================================================================
// ==================================================================


class  cComponentEditorDelegate :
    public  QStyledItemDelegate
{
public:
    typedef QStyledItemDelegate tSuperClass;

public:
    cComponentEditorDelegate( QWidget* iParent = 0 );

public:
    // Overrides
    QWidget * createEditor( QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index ) const override;
    void    setEditorData( QWidget *editor, const QModelIndex &index ) const override;
    void    setModelData( QWidget *editor, QAbstractItemModel *model, const QModelIndex &index ) const override;

public:
    void SetComponent( ::nECS::cComponentGeneric* iComponent );

private:
    ::nECS::cComponentGeneric* mComponent;
};


