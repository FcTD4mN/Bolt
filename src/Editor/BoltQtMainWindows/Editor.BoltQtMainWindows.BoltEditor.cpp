#include "Editor.BoltQtMainWindows.BoltEditor.h"

#include "Core.ECS.Core.Entity.h"
#include "Core.ECS.Core.World.h"
#include "Core.ECS.Utilities.EntityParser.h"
#include "Core.ECS.Utilities.ComponentRegistry.h"

#include "Core.ECS.Core.GlobalEntityMap.h"
#include "Core.Mapping.PhysicEntityGrid.h"

#include "Editor.Application.EditorApplication.h"

#include "Editor.BoltQtModels.EntityListModel.h"

#include <QtWidgets/QTableView>
#include <QFileDialog>

#include "tinyxml2.h"

namespace nQt {

cBoltEditor::~cBoltEditor()
{
    delete  mPrototypeListModel;
}


cBoltEditor::cBoltEditor( QWidget *parent ) :
    QMainWindow( parent )
{
    ui.setupUi( this );
}


void
cBoltEditor::Setup()
{
    mApp = ::nApplication::cEditorApplication::App();
    mApp->Initialize();

    ui.widget->SetEditorApp( mApp );

    mPrototypeListModel = new ::nQt::nModels::cEntityListModel( 0 );
    ui.listView->setModel( mPrototypeListModel );
    ui.PrototypeEditor->SetAllPrototypeListModel( mPrototypeListModel );

    connect(
        ui.listView, &QListView::clicked,
        ui.widget, &SFMLCanvas::CurrentPrototypeChanged
    );

    connect( ui.actionSave, &QAction::triggered, this, &cBoltEditor::SaveLevel );
    connect( ui.actionLoad, &QAction::triggered, this, &cBoltEditor::LoadLevel );
}


void
cBoltEditor::SaveLevel()
{
    QString filename = QFileDialog::getSaveFileName( this, "Save your level" );
    if( filename != "" )
    {
        tinyxml2::XMLDocument doc;
        tinyxml2::XMLElement* elm = doc.NewElement( "world" );

        mApp->World()->SaveXML( elm, &doc );

        doc.InsertFirstChild( elm );

        tinyxml2::XMLError error = doc.SaveFile( filename.toStdString().c_str() );
        if( error )
            return;
    }
}


void
cBoltEditor::LoadLevel()
{
    QString filename = QFileDialog::getOpenFileName( this, "Load your level" );
    if( filename != "" )
    {
        tinyxml2::XMLDocument doc;
        tinyxml2::XMLError error = doc.LoadFile( filename.toStdString().c_str() );

        mApp->World()->LoadXML( doc.FirstChildElement( "world" ) );
    }

    // Add all entities to the EMap
    for( int i = 0; i < mApp->World()->EntityCount(); ++i )
        ::nECS::cGlobalEntityMap::Instance()->mEntityGrid->AddEntity( mApp->World()->GetEntityAtIndex( i ) );
}


void
cBoltEditor::PrototypeEditionAsked( QModelIndex iIndex )
{
    ui.tabWidget->setCurrentIndex( 1 );
}


} //nQt
