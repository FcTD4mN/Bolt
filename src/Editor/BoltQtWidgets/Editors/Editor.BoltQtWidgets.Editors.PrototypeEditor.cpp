#include "Editor.BoltQtWidgets.Editors.PrototypeEditor.h"

#include "Core.ECS.Utilities.EntityParser.h"
#include "Core.ECS.Core.Entity.h"
#include "Core.ECS.Core.Component.h"

#include "Editor.BoltQtModels.EntityModel.h"
#include "Editor.Application.EditorApplication.h"

#include <QTreeWidget>
#include <QMessageBox>

cPrototypeEditor::~cPrototypeEditor()
{
}


cPrototypeEditor::cPrototypeEditor( QWidget * Parent ) :
    tSuperClass( Parent ),
    mEntity( 0 ),
    mOriginalFileName( L"" )
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
    mEntity = ::nECS::cEntityParser::Instance()->GetPrototypeByName( name );
    mOriginalFileName = ::nECS::cEntityParser::Instance()->GetEntityFileNameByEntityName( name );

    ui.listViewAllPrototypes->setCurrentIndex( iIndex );
    ui.treeViewPrototype->selectedEntitiesChanged( mEntity );
}


void
cPrototypeEditor::SavePrototype()
{
    if( mEntity )
    {
        std::string entityName = mEntity->ID();

        QMessageBox msg;
        msg.setIcon( QMessageBox::Critical );
        if( !::nECS::cEntityParser::Instance()->IsIDAvailable( entityName ) )
        {
            msg.setText( "Prototype name already used, can't save under this name" );
            msg.exec();
            return;
        }
        if( entityName == "" )
        {
            msg.setText( "Prototype name is empty" );
            msg.exec();
            return;
        }

        // Removing the old file
        std::string originalAsString;
        originalAsString = std::string( mOriginalFileName.begin(), mOriginalFileName.end() );

        if( remove( originalAsString.c_str() ) != 0 )
            perror( "Delete failed\n" );
        else
            printf( "Delete success\n" );

        // Creating the new file
        std::string newFileName = "resources/Core/Entities/" + entityName + ".entity";
        tinyxml2::XMLDocument doc;
        tinyxml2::XMLElement* elm = doc.NewElement( "entity" );

        mEntity->SaveXML( elm, &doc );

        doc.InsertFirstChild( elm );

        tinyxml2::XMLError error = doc.SaveFile( newFileName.c_str() );
        if( error )
            return;

        // Reparse all it's easier than trying to update the hash and stuff + there might be new files etc
        ::nECS::cEntityParser::Instance()->ReparseAll( ::nApplication::cEditorApplication::App()->World() );

        // Model changed, we don't care where, we update everything
        auto model = ui.listViewAllPrototypes->model();
        model->dataChanged( model->index( 0, 0 ), model->index( ::nECS::cEntityParser::Instance()->EntityCount(), 0 ) );
    }
}

