#pragma once

#include <QStyledItemDelegate>

namespace nCore::nECS::nCore { class cEntity; }

class  cEntityPropertiesDelegate :
    public  QStyledItemDelegate
{
public:
    typedef QStyledItemDelegate tSuperClass;

public:
    cEntityPropertiesDelegate( QWidget* iParent = 0 );

public:
    // Overrides
    void        paint( QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index ) const override;

    QWidget *   createEditor( QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index ) const override;
    void        setEditorData( QWidget *editor, const QModelIndex &index ) const override;
    void        setModelData( QWidget *editor, QAbstractItemModel *model, const QModelIndex &index ) const override;

    bool        editorEvent( QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index ) override;

public:
    void        SetEntity( ::nCore::nECS::nCore::cEntity* iEntity );

private:
    ::nCore::nECS::nCore::cEntity* mEntity; //TODO: this should be model
};
