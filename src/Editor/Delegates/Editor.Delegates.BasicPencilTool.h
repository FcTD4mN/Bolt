#pragma once


#include "Editor.Widgets.ColorSwatch.h"

#include <QCheckBox>
#include <QStyledItemDelegate>


namespace nQt::nModels { class cBasicPencilToolModel; }



/*
This is probably useless, as treeview and delegate require a click to enter in edit mode thing
I'd like a form thing better, where you have the edition gadgets always up and running
So we'll need a form maker, that can read data type from a model, create the right gadgets and map them
*/


class  cBasicPencilToolDelegate :
    public  QStyledItemDelegate
{
public:
    typedef QStyledItemDelegate tSuperClass;

public:
    ~cBasicPencilToolDelegate();
    cBasicPencilToolDelegate( QWidget* iParent = 0 );

public:
    // QStyledItemDelegate Overrides
    void        paint( QPainter* iPainter, const QStyleOptionViewItem& iOption, const QModelIndex& iIndex ) const override;

    QWidget*    createEditor( QWidget* iParent, const QStyleOptionViewItem& iOption, const QModelIndex& iIndex ) const override;
    void        setEditorData( QWidget* iEditor, const QModelIndex& iIndex ) const override;
    void        setModelData( QWidget* iEditor, QAbstractItemModel* iModel, const QModelIndex& iIndex ) const override;

    bool        editorEvent( QEvent* iEvent, QAbstractItemModel* iModel, const QStyleOptionViewItem& iOption, const QModelIndex& iIndex ) override;

public:
    void        BasicPencilToolModel( ::nQt::nModels::cBasicPencilToolModel*  iBasicPencilToolModel );

private:
    ::nQt::nModels::cBasicPencilToolModel*  mBasicPencilToolModel;
};
