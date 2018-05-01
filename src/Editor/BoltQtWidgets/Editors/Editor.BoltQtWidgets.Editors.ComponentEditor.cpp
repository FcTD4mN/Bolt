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
    auto registryInstance = ::nECS::cComponentRegistry::Instance();

    if( !mComponent )
        return;

    std::wstring filename = registryInstance->GetComponentFileNameByComponentName( mComponent->Name() );
    registryInstance->UnregisterComponentByName( mComponent->Name() );

    QString newName = ui.editComponentName->text();
    mComponent->Name( newName.toStdString() );

    registryInstance->RegisterComponent( mComponent );
    registryInstance->SetComponentFilenameUsingComponentName( mComponent->Name(), filename );

    mComponentListModel->dataChanged( mComponentListModel->index( 0, 0 ), mComponentListModel->index( registryInstance->ComponentCount(), 0 ) );
}


void
cComponentEditor::SaveComponent()
{
    if( mComponent )
    {
        std::string compName = mComponent->Name();

        QMessageBox msg;
        msg.setIcon( QMessageBox::Critical );
        if( compName == "" )
        {
            msg.setText( "Component name is empty" );
            msg.exec();
            return;
        }

        std::wstring filename = ::nECS::cComponentRegistry::Instance()->GetComponentFileNameByComponentName( compName );
        std::string newFileName;

        if( filename == L"" )
        {
            QString pathAndFile( "./Resources/Core/Components/" );
            pathAndFile += compName.c_str();

            QFileDialog fileAsking( this, tr( "Save your component" ), pathAndFile, tr( "Component (*.comp)" ) );
            fileAsking.setDefaultSuffix( "comp" );

            if( fileAsking.exec() )
                newFileName = fileAsking.selectedFiles().last().toStdString();
            else
                return;

            std::wstring filenameAsWString( newFileName.begin(), newFileName.end() );
            ::nECS::cComponentRegistry::Instance()->SetComponentFilenameUsingComponentName( compName, filenameAsWString );
        }
        else
        {
            // Removing the old file
            std::string originalAsString = std::string( filename.begin(), filename.end() );

            if( remove( originalAsString.c_str() ) != 0 )
                perror( "Delete failed\n" );
            else
                printf( "Delete success\n" );

            newFileName = originalAsString;
        }

        // Creating the new file
        tinyxml2::XMLDocument doc;
        tinyxml2::XMLElement* elm = doc.NewElement( "component" );

        mComponent->SaveXML( elm, &doc );

        doc.InsertFirstChild( elm );

        tinyxml2::XMLError error = doc.SaveFile( newFileName.c_str() );
        if( error )
            return;

        // Model changed, we don't care where, we update everything
        mComponentListModel->dataChanged( mComponentListModel->index( 0, 0 ), mComponentListModel->index( ::nECS::cComponentRegistry::Instance()->ComponentCount(), 0 ) );
    }
}


void
cComponentEditor::SaveComponentAs()
{
    if( !mComponent )
        return;

    QString pathAndFile( "./Resources/Core/Components/" );
    pathAndFile += mComponent->Name().c_str();

    QFileDialog fileAsking( this, tr( "Save your component" ), pathAndFile, tr( "Component (*.component)" ) );
    fileAsking.setDefaultSuffix( "component" );

    std::string fullFilePath;

    if( fileAsking.exec() )
        fullFilePath = fileAsking.selectedFiles().last().toStdString();
    else
        return;

    // To get file name, and not the full path
    QFileInfo fileInfo( fullFilePath.c_str() );

    auto registry = ::nECS::cComponentRegistry::Instance();
    std::wstring  entityCurrentFileName = registry->GetComponentFileNameByComponentName( mComponent->Name() );

    // Creating the new file
    tinyxml2::XMLDocument doc;
    tinyxml2::XMLElement* elm = doc.NewElement( "component" );
    std::wstring filenameAsWString( fullFilePath.begin(), fullFilePath.end() );

    if( entityCurrentFileName != L"" )
    {
        ::nECS::cComponent*  entityAssociatedToRequiredFilename = registry->GetComponentAssociatedToFileName( filenameAsWString );

        if( entityAssociatedToRequiredFilename )
            registry->UnregisterComponentByName( entityAssociatedToRequiredFilename->Name() );

        ::nECS::cComponent* clone = mComponent->Clone();
        std::string newCompName = fileInfo.baseName().toStdString();
        int i = 2;
        while( registry->IsComponentNameAValidComponentInRegistry( newCompName ) )
        {
            newCompName = fileInfo.baseName().toStdString() + std::to_string( i );
            ++i;
        }
        clone->Name( newCompName );

        registry->RegisterComponent( clone );
        clone->SaveXML( elm, &doc );
        registry->SetComponentFilenameUsingComponentName( clone->Name(), filenameAsWString );
    }
    else
    {
        mComponent->SaveXML( elm, &doc );
        registry->SetComponentFilenameUsingComponentName( mComponent->Name(), filenameAsWString );
    }

    doc.InsertFirstChild( elm );

    tinyxml2::XMLError error = doc.SaveFile( fullFilePath.c_str() );
    if( error )
        return;

    // Model changed, we don't care where, we update everything
    auto model = ui.listViewAllComponents->model();
    model->dataChanged( model->index( 0, 0 ), model->index( registry->ComponentCount(), 0 ) );
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



