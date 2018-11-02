#pragma once

#include <QStyledItemDelegate>

namespace nQt::nModels { class cComponentModel; }

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
    void SetModel( ::nQt::nModels::cComponentModel* iModel );

private:
    ::nQt::nModels::cComponentModel* mModel;
};
