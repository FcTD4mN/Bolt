#include "Editor.Delegates.BasicPencilTool.h"

#include "Editor.Models.BasicPencilToolModel.h"

#include <QPainter>
#include <QApplication>
#include <QMouseEvent>
#include <QColorDialog>
#include <QDialog>


cBasicPencilToolDelegate::~cBasicPencilToolDelegate()
{
}

cBasicPencilToolDelegate::cBasicPencilToolDelegate( QWidget * iParent ) :
    tSuperClass( iParent ),
    mBasicPencilToolModel( 0 )
{
}


void cBasicPencilToolDelegate::paint( QPainter* iPainter, const QStyleOptionViewItem& iOption, const QModelIndex & iIndex ) const
{
    if( iIndex.row() == 2 && iIndex.column() == 1 )
    {
        iPainter->setBrush( mBasicPencilToolModel->Color() );
        iPainter->drawRect( iOption.rect );
    }
    else
    {
        tSuperClass::paint( iPainter, iOption, iIndex );
    }
}


QWidget*
cBasicPencilToolDelegate::createEditor( QWidget * iParent, const QStyleOptionViewItem & iOption, const QModelIndex & iIndex ) const
{
    return  tSuperClass::createEditor( iParent, iOption, iIndex );
}


void
cBasicPencilToolDelegate::setEditorData( QWidget * iEditor, const QModelIndex & iIndex ) const
{
    tSuperClass::setEditorData( iEditor, iIndex );
}


void
cBasicPencilToolDelegate::setModelData( QWidget * iEditor, QAbstractItemModel * iModel, const QModelIndex & iIndex ) const
{
    tSuperClass::setModelData( iEditor, iModel, iIndex );
}


bool
cBasicPencilToolDelegate::editorEvent( QEvent* iEvent, QAbstractItemModel* iModel, const QStyleOptionViewItem& iOption, const QModelIndex& iIndex )
{
    if( iEvent->type() == QEvent::MouseButtonRelease )
    {
        if( iIndex.row() == 2 && iIndex.column() == 1 )
        {
            QColorDialog dial( mBasicPencilToolModel->Color() );
            if( dial.exec() )
                mBasicPencilToolModel->Color( dial.selectedColor() );

            return  true;
        }
    }

    return  tSuperClass::editorEvent( iEvent, iModel, iOption, iIndex );
}


void
cBasicPencilToolDelegate::BasicPencilToolModel( ::nQt::nModels::cBasicPencilToolModel*  iBasicPencilToolModel )
{
    mBasicPencilToolModel = iBasicPencilToolModel;
}
