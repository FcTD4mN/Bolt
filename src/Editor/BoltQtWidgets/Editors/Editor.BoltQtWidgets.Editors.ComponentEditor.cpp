#include "Editor.BoltQtWidgets.Editors.ComponentEditor.h"

#include "Core.ECS.Utilities.ComponentRegistry.h"
#include "Core.ECS.Core.Component.h"

#include "Editor.Application.EditorApplication.h"
#include "Editor.BoltQtModels.ComponentListModel.h"
#include "Editor.BoltQtModels.ComponentModel.h"

#include <QComboBox>
#include <QFileDialog>
#include <QMessageBox>
#include <QTreeWidget>


cComponentEditor::~cComponentEditor()
{
}


cComponentEditor::cComponentEditor( QWidget * Parent ) :
    tSuperClass( Parent ),
    mComponent( 0 )
{
    ui.setupUi( this );
    mComponentListModel = new  ::nQt::nModels::cComponentListModel();
    ui.listViewAllComponents->setModel( mComponentListModel );

    mDelegate = new  cComponentEditorDelegate;
    ui.treeViewComponent->setItemDelegate( mDelegate );

}


void
cComponentEditor::SetAllComponentListModel( QAbstractItemModel * iModel )
{
    ui.listViewAllComponents->setModel( iModel );
}


void
cComponentEditor::ComponentNameChanged()
{
    QString newName = ui.editComponentName->text();
    mComponent->Name( newName.toStdString() );
    mComponentListModel->dataChanged( mComponentListModel->index( 0, 0 ), mComponentListModel->index( ::nECS::cComponentRegistry::Instance()->ComponentCount(), 0 ) );
}


void
cComponentEditor::ComponentEditionAsked( QModelIndex iIndex )
{
    std::string name = iIndex.data( Qt::DisplayRole ).toString().toStdString();
    mComponent = ::nECS::cComponentRegistry::Instance()->GetComponentByName( name );
    mDelegate->SetComponent( dynamic_cast< ::nECS::cComponentGeneric* >( mComponent ) );

    ui.editComponentName->setText( name.c_str() );
    ui.treeViewComponent->setModel( new  ::nQt::nModels::cComponentModel( mComponent ) );
    ui.listViewAllComponents->setCurrentIndex( mComponentListModel->GetComponentIndex( mComponent ) );
}


void
cComponentEditor::AddNewVariable()
{
    auto model = dynamic_cast< ::nQt::nModels::cComponentModel* >( ui.treeViewComponent->model() );
    if( model )
        model->AddNewVariable();
}


void
cComponentEditor::RemoveVariable()
{
    auto model = dynamic_cast< ::nQt::nModels::cComponentModel* >( ui.treeViewComponent->model() );
    if( !model )
        return;

    model->RemoveVariable( ui.treeViewComponent->currentIndex() );
}


void
cComponentEditor::AddNewComponent()
{
    ComponentEditionAsked( mComponentListModel->AddNewComponent() );
}


void
cComponentEditor::RemoveComponent()
{
    mComponentListModel->RemoveComponent( ui.listViewAllComponents->currentIndex() );
    ComponentEditionAsked( ui.listViewAllComponents->currentIndex() );
}



// ==================================================================
// ==================================================================
// ==================================================================



cComponentEditorDelegate::cComponentEditorDelegate( QWidget * iParent ) :
    tSuperClass( iParent ),
    mComponent( 0 )
{
}


QWidget *
cComponentEditorDelegate::createEditor( QWidget * iParent, const QStyleOptionViewItem & iOption, const QModelIndex & iIndex ) const
{
    if( iIndex.parent() == QModelIndex() && iIndex.column() == 1 )
        return  new QComboBox( iParent );

    return  tSuperClass::createEditor( iParent, iOption, iIndex );
}


void
cComponentEditorDelegate::setEditorData( QWidget * iEditor, const QModelIndex & iIndex ) const
{
    if( mComponent && iIndex.parent() == QModelIndex() && iIndex.column() == 1 )
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
    if( mComponent && iIndex.parent() == QModelIndex() && iIndex.column() == 1 )
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
cComponentEditorDelegate::SetComponent( ::nECS::cComponentGeneric * iComponent)
{
    mComponent = iComponent;
}



