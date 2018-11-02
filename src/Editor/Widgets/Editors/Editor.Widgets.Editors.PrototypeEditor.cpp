#include "Editor.Widgets.Editors.PrototypeEditor.h"


#include "Core.Application.GlobalAccess.h"

#include "Core.Base.FileSystem.h"
#include "Core.Registries.EntityRegistry.h"
#include "Core.ECS.Core.Entity.h"
#include "Core.ECS.Core.Component.h"

#include "Editor.Models.EntityModel.h"
#include "Editor.Models.EntityListModel.h"

#include "Editor.Widgets.Editors.PropertyEditor.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QTreeWidget>


cPrototypeEditor::~cPrototypeEditor()
{
}


cPrototypeEditor::cPrototypeEditor( QWidget * Parent ) :
    tSuperClass( Parent ),
    mEntity( 0 )
{
    ui.setupUi( this );
}


void
cPrototypeEditor::SetAllPrototypeListModel( QAbstractItemModel * iModel )
{
    ui.listViewAllPrototypes->setModel( iModel );
}


void
cPrototypeEditor::PrototypeEditionAsked( QModelIndex iIndex )
{
    std::string name = iIndex.data( Qt::DisplayRole ).toString().toStdString();
    mEntity = ::nCore::nRegistries::cEntityRegistry::Instance()->GetItemByName( name );

    ui.listViewAllPrototypes->setCurrentIndex( iIndex );

    //auto entityModel = new ::nQt::nModels::cEntityModel( mEntity );
    auto entityModel = std::make_shared< ::nQt::nModels::cEntityModel >( mEntity );
    connect( entityModel.get(), &::nQt::nModels::cEntityModel::EntityNameChanged, this, &cPrototypeEditor::PrototypeNameChanged );

    emit  showPrototypeProperties( entityModel );
    ui.treeViewPrototype->ShowProperties( entityModel );
}


void
cPrototypeEditor::PrototypeNameChanged( QString iOldName, QString iNewName )
{
    auto parser = ::nCore::nRegistries::cEntityRegistry::Instance();
    auto filename = parser->GetItemFileByItemName( iOldName.toStdString() );
    parser->UnregisterItemByName( iOldName.toStdString() );
    parser->RegisterItem( mEntity->ID(), mEntity );
    parser->SetItemFileUsingItemName( mEntity->ID(), filename );

    ForceUpdateModel();
}


void
cPrototypeEditor::SavePrototype()
{
    if( mEntity )
    {
        std::string entityName = mEntity->ID();

        QMessageBox msg;
        msg.setIcon( QMessageBox::Critical );
        if( entityName == "" )
        {
            msg.setText( "Prototype name is empty" );
            msg.exec();
            return;
        }

        nStdFileSystem::path filePath = ::nCore::nRegistries::cEntityRegistry::Instance()->GetItemFileByItemName( entityName );
        nStdFileSystem::path newFilePath;

        if( filePath.empty() )
        {
            nStdFileSystem::path pathAndFile( ::nCore::nApplication::cGlobalAccess::Instance()->ProjectFolder() + "/Assets/Entities/" );
            pathAndFile += entityName.c_str();

            QFileDialog fileAsking( this, tr( "Save your entity" ), pathAndFile.string().c_str(), tr( "Entity (*.entity)" ) );
            fileAsking.setDefaultSuffix( "entity" );

            if( fileAsking.exec() )
                newFilePath = fileAsking.selectedFiles().last().toStdString();
            else
                return;

            ::nCore::nRegistries::cEntityRegistry::Instance()->SetItemFileUsingItemName( entityName, newFilePath );
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
        tinyxml2::XMLElement* elm = doc.NewElement( "entity" );

        mEntity->SaveXML( elm, &doc );

        doc.InsertFirstChild( elm );

        tinyxml2::XMLError error = doc.SaveFile( newFilePath.string().c_str() );
        if( error )
            return;

        // Model changed, we don't care where, we update everything
        ForceUpdateModel();
    }
}


void
cPrototypeEditor::SavePrototypeAs()
{
    nStdFileSystem::path pathAndFile( ::nCore::nApplication::cGlobalAccess::Instance()->ProjectFolder() + "/Assets/Entities/" );
    pathAndFile += mEntity->ID().c_str();

    QFileDialog fileAsking( this, tr( "Save your entity" ), pathAndFile.string().c_str(), tr( "Entity (*.entity)" ) );
    fileAsking.setDefaultSuffix( "entity" );

    nStdFileSystem::path fullFilePath;
    if( fileAsking.exec() )
        fullFilePath = fileAsking.selectedFiles().last().toStdString();
    else
        return;

    auto parser = ::nCore::nRegistries::cEntityRegistry::Instance();
    nStdFileSystem::path  entityCurrentFilePath = parser->GetItemFileByItemName( mEntity->ID() );

    // Creating the new file
    tinyxml2::XMLDocument doc;
    tinyxml2::XMLElement* elm = doc.NewElement( "entity" );

    if( !entityCurrentFilePath.empty() )
    {
        ::nCore::nECS::nCore::cEntity*  entityAssociatedToRequiredFilename = parser->GetItemAssociatedToFile( fullFilePath );

        if( entityAssociatedToRequiredFilename )
            parser->UnregisterItemByName( entityAssociatedToRequiredFilename->ID() );

        ::nCore::nECS::nCore::cEntity* clone = mEntity->Clone();
        std::string newEntName = fullFilePath.stem().string();
        int i = 2;
        while( parser->IsItemNameAlreadyInRegistry( newEntName ) )
        {
            newEntName = fullFilePath.stem().string() + std::to_string( i );
            ++i;
        }
        clone->SetID( newEntName );

        parser->RegisterItem( newEntName, clone );
        clone->SaveXML( elm, &doc );
        ::nCore::nRegistries::cEntityRegistry::Instance()->SetItemFileUsingItemName( clone->ID(), fullFilePath );
    }
    else
    {
        mEntity->SaveXML( elm, &doc );
        ::nCore::nRegistries::cEntityRegistry::Instance()->SetItemFileUsingItemName( mEntity->ID(), fullFilePath );
    }

    doc.InsertFirstChild( elm );

    tinyxml2::XMLError error = doc.SaveFile( fullFilePath.string().c_str() );
    if( error )
        return;

    // Model changed, we don't care where, we update everything
    ForceUpdateModel();
}


void
cPrototypeEditor::AddNewPrototype()
{
    auto modelList = dynamic_cast< ::nQt::nModels::cEntityListModel* >( ui.listViewAllPrototypes->model() );
    if( modelList )
        PrototypeEditionAsked( modelList->AddNewPrototype() );
}


void
cPrototypeEditor::RemovePrototype()
{
    // Removing the file
    auto model = dynamic_cast< ::nQt::nModels::cEntityListModel* >( ui.listViewAllPrototypes->model() );
    if( !model )
        return;

    model->RemovePrototype( ui.listViewAllPrototypes->currentIndex() );
    PrototypeEditionAsked( ui.listViewAllPrototypes->currentIndex() );
}


void
cPrototypeEditor::ProjectLoaded( ::nQt::nModels::cProjectHierarchyModel* iProject )
{
    ForceUpdateModel();
}


void
cPrototypeEditor::ForceUpdateModel()
{
    auto model = ui.listViewAllPrototypes->model();
    model->dataChanged( model->index( 0, 0 ), model->index( ::nCore::nRegistries::cEntityRegistry::Instance()->ItemCount(), 0 ) );
}


