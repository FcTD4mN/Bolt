#include "Editor.Delegates.ComponentProperties.h"

#include "Core.ECS.Core.Component.h"

#include "Editor.Models.ComponentModel.h"
#include "Editor.Models.TreeWrapperComponent.h"

#include <QComboBox>


cComponentEditorDelegate::cComponentEditorDelegate( QWidget * iParent ) :
    tSuperClass( iParent ),
    mModel( 0 )
{
}


QWidget *
cComponentEditorDelegate::createEditor( QWidget * iParent, const QStyleOptionViewItem & iOption, const QModelIndex & iIndex ) const
{
    auto item = mModel->ExtractTreeWrapper( iIndex );
    if( item->Type() == "Variable" && iIndex.column() == 1 )
        return  new QComboBox( iParent );

    return  tSuperClass::createEditor( iParent, iOption, iIndex );
}


void
cComponentEditorDelegate::setEditorData( QWidget * iEditor, const QModelIndex & iIndex ) const
{
    auto item = mModel->ExtractTreeWrapper( iIndex );
    if( item && item->Type() == "Variable" && iIndex.column() == 1 )
    {
        auto combo = dynamic_cast<QComboBox*>( iEditor );
        if( combo )
        {
            QString currentVariableTypeName = iIndex.data( Qt::DisplayRole ).toString();
            combo->addItem( currentVariableTypeName );

            if( currentVariableTypeName != "Number" )
                combo->addItem( "Number" );
            if( currentVariableTypeName != "String" )
                combo->addItem( "String" );
            if( currentVariableTypeName != "Boolean" )
                combo->addItem( "Boolean" );
        }
    }
    else
    {
        tSuperClass::setEditorData( iEditor, iIndex );
    }
}


void
cComponentEditorDelegate::setModelData( QWidget * iEditor, QAbstractItemModel * iModel, const QModelIndex & iIndex ) const
{
    auto item = mModel->ExtractTreeWrapper( iIndex );
    if( item && item->Type() == "Variable" && iIndex.column() == 1 )
    {
        auto combo = dynamic_cast<QComboBox*>( iEditor );
        if( combo && combo->currentIndex() > 0 ) // index 0 means we selected the same component, so no need to change anything
        {
            iModel->setData( iIndex, combo->currentText() );
        }
    }
    else
    {
        tSuperClass::setModelData( iEditor, iModel, iIndex );
    }
}


void
cComponentEditorDelegate::SetModel( ::nQt::nModels::cComponentModel * iModel )
{
    mModel = iModel;
}
