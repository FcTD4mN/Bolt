#include "Editor.BoltQtMainWindows.BoltEditor.h"

#include "Core.ECS.Core.Entity.h"
#include "Core.ECS.Core.World.h"
#include "Core.ECS.Utilities.EntityParser.h"
#include "Core.ECS.Utilities.ComponentRegistry.h"

#include "Core.ECS.Core.GlobalEntityMap.h"
#include "Core.Mapping.PhysicEntityGrid.h"

#include "Editor.Application.EditorApplication.h"

#include "Editor.BoltQtModels.EntityListModel.h"

#include "Editor.BoltQtWidgets.SFMLCanvas.h"

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

    connect( ui.actionNew_Project, &QAction::triggered, this, &cBoltEditor::NewProject );
    connect( ui.actionOpen, &QAction::triggered, this, &cBoltEditor::OpenProject );
    connect( ui.actionToogle_Grid, &QAction::triggered, ui.widget, &SFMLCanvas::ToggleGridVisible );
    connect( ui.actionSnapGrid, &QAction::triggered, ui.widget, &SFMLCanvas::SetSnapGridUp );

    connect( this, &cBoltEditor::CurrentProjectChanged, ui.PrototypeEditor, &cPrototypeEditor::ProjectLoaded );
    connect( this, &cBoltEditor::CurrentProjectChanged, ui.projectEditor, &cProjectEditor::ProjectLoaded );
}


void
cBoltEditor::NewProject()
{
    QString projectDir = QFileDialog::getExistingDirectory( this, "Choose a directory" );
    if( projectDir != "" )
    {
        QDir directory( projectDir );
        QString projectName = "ProjectTestEditor";

        if( !directory.exists( projectName ) )
        {
            directory.mkdir( projectName );
            directory.mkdir( projectName + "/Assets" );
            directory.mkdir( projectName + "/Assets/Entities" );
            directory.mkdir( projectName + "/Assets/Components" );
            directory.mkdir( projectName + "/Assets/Shaders" );
            directory.mkdir( projectName + "/Assets/Systems" );
            directory.mkdir( projectName + "/Screens" );

            mApp->NewProject( projectDir.toStdString() + projectName.toStdString() + "/" + projectName.toStdString() + ".proj" );
            emit  CurrentProjectChanged( mApp->Project() );
        }
    }
}


void
cBoltEditor::OpenProject()
{
    QString project = QFileDialog::getOpenFileName( this, "Load your project" );
    if( project != "" )
    {
        mApp->LoadProject( project.toStdString().c_str() );
        emit  CurrentProjectChanged( mApp->Project() );
    }
}


void
cBoltEditor::PrototypeEditionAsked( QModelIndex iIndex )
{
    ui.tabWidget->setCurrentIndex( 1 );
}


} //nQt


