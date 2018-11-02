#include "Editor.Widgets.Editors.ComponentEditor.h"

#include "Core.Application.GlobalAccess.h"

#include "Core.Registries.ComponentRegistry.h"
#include "Core.ECS.Core.Component.h"

#include "Editor.Models.ComponentListModel.h"
#include "Editor.Models.ComponentModel.h"
#include "Editor.Models.TreeWrapperComponent.h"

#include "Editor.Delegates.ComponentProperties.h"

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
    auto registryInstance = ::nCore::nRegistries::cComponentRegistry::Instance();

    if( !mComponent )
        return;

    nStdFileSystem::path filename = registryInstance->GetItemFileByItemName( mComponent->Name() );
    registryInstance->UnregisterItemByName( mComponent->Name() );

    QString newName = ui.editComponentName->text();
    mComponent->Name( newName.toStdString() );

    registryInstance->RegisterItem( mComponent->Name(), mComponent );
    registryInstance->SetItemFileUsingItemName( mComponent->Name(), filename );

    mComponentListModel->dataChanged( mComponentListModel->index( 0, 0 ), mComponentListModel->index( registryInstance->ItemCount(), 0 ) );
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

        nStdFileSystem::path filePath = ::nCore::nRegistries::cComponentRegistry::Instance()->GetItemFileByItemName( compName );
        nStdFileSystem::path newFilePath;

        if( filePath.empty() )
        {
            nStdFileSystem::path pathAndFile( ::nCore::nApplication::cGlobalAccess::Instance()->ProjectFolder() + "/Assets/Components/" );
            pathAndFile += compName.c_str();

            QFileDialog fileAsking( this, tr( "Save your component" ), pathAndFile.string().c_str(), tr( "Component (*.comp)" ) );
            fileAsking.setDefaultSuffix( "comp" );

            if( fileAsking.exec() )
                newFilePath = fileAsking.selectedFiles().last().toStdString();
            else
                return;

            ::nCore::nRegistries::cComponentRegistry::Instance()->SetItemFileUsingItemName( compName, newFilePath );
        }
        else
        {
            // Removing the old file
            if( remove( filePath.string().c_str() ) != 0 )
                perror( "Delete failed\n" );
            else
                printf( "Delete success\n" );

            newFilePath = filePath;
        }

        // Creating the new file
        tinyxml2::XMLDocument doc;
        tinyxml2::XMLElement* elm = doc.NewElement( "component" );

        mComponent->SaveXML( elm, &doc );

        doc.InsertFirstChild( elm );

        tinyxml2::XMLError error = doc.SaveFile( newFilePath.string().c_str() );
        if( error )
            return;

        // Model changed, we don't care where, we update everything
        mComponentListModel->dataChanged( mComponentListModel->index( 0, 0 ), mComponentListModel->index( ::nCore::nRegistries::cComponentRegistry::Instance()->ItemCount(), 0 ) );
    }
}


void
cComponentEditor::SaveComponentAs()
{
    if( !mComponent )
        return;

    nStdFileSystem::path pathAndFile( ::nCore::nApplication::cGlobalAccess::Instance()->ProjectFolder() + "/Assets/Components/" );
    pathAndFile += mComponent->Name().c_str();

    QFileDialog fileAsking( this, tr( "Save your component" ), pathAndFile.string().c_str(), tr( "Component (*.comp)" ) );
    fileAsking.setDefaultSuffix( "comp" );

    nStdFileSystem::path fullFilePath;

    if( fileAsking.exec() )
        fullFilePath = fileAsking.selectedFiles().last().toStdString();
    else
        return;

    auto registry = ::nCore::nRegistries::cComponentRegistry::Instance();
    nStdFileSystem::path  entityCurrentFile = registry->GetItemFileByItemName( mComponent->Name() );

    // Creating the new file
    tinyxml2::XMLDocument doc;
    tinyxml2::XMLElement* elm = doc.NewElement( "component" );

    if( !entityCurrentFile.empty() )
    {
        ::nCore::nECS::nCore::cComponent*  entityAssociatedToRequiredFilename = registry->GetItemAssociatedToFile( fullFilePath );

        if( entityAssociatedToRequiredFilename )
            registry->UnregisterItemByName( entityAssociatedToRequiredFilename->Name() );

        ::nCore::nECS::nCore::cComponent* clone = mComponent->Clone();
        std::string newCompName = fullFilePath.stem().string();
        int i = 2;
        while( registry->IsItemNameAlreadyInRegistry( newCompName ) )
        {
            newCompName = fullFilePath.stem().string() + std::to_string( i );
            ++i;
        }
        clone->Name( newCompName );

        registry->RegisterItem( newCompName, clone );
        clone->SaveXML( elm, &doc );
        registry->SetItemFileUsingItemName( clone->Name(), entityCurrentFile );
    }
    else
    {
        mComponent->SaveXML( elm, &doc );
        registry->SetItemFileUsingItemName( mComponent->Name(), fullFilePath );
    }

    doc.InsertFirstChild( elm );

    tinyxml2::XMLError error = doc.SaveFile( fullFilePath.string().c_str() );
    if( error )
        return;

    // Model changed, we don't care where, we update everything
    auto model = ui.listViewAllComponents->model();
    model->dataChanged( model->index( 0, 0 ), model->index( registry->ItemCount(), 0 ) );
}


void
cComponentEditor::ComponentEditionAsked( QModelIndex iIndex )
{
    std::string name = iIndex.data( Qt::DisplayRole ).toString().toStdString();
    mComponent = ::nCore::nRegistries::cComponentRegistry::Instance()->GetItemByName( name );

    auto newModel = std::make_shared< ::nQt::nModels::cComponentModel >( mComponent );

    mDelegate->SetModel( newModel.get() );

    ui.editComponentName->setText( name.c_str() );
    ui.treeViewComponent->setModel( newModel.get() );
    ui.listViewAllComponents->setCurrentIndex( mComponentListModel->GetComponentIndex( mComponent ) );

    emit  showComponentProperties( newModel );
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


