#pragma once

#include "ui_ComponentEditor.h"

#include <QModelIndex>
#include <QWidget>
#include <QStyledItemDelegate>

namespace nApplication { class cEditorApplication; }

namespace nECS { class cComponent; }
namespace nECS { class cComponentGeneric; }

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
    //void  ComponentNameChanged( QString iOldName, QString iNewName );

    //void  SaveComponent();
    //void  SaveComponentAs();

    void  AddNewVariable();
    void  RemoveVariable();

private:
    Ui::ComponentEditor         ui;
    ::nECS::cComponent*         mComponent;
    cComponentEditorDelegate*   mDelegate;
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


