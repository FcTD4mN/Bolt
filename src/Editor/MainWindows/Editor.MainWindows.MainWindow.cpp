#include "Editor.MainWindows.MainWindow.h"

#ifdef USE_RIVET

#include "Core.Project.Project.h"

#include "Editor.Widgets.MainCaption.h"
#include "Editor.Widgets.MainContent.h"
#include "Editor.Widgets.MainCaptionMenuBar.h"
#include "Editor.Widgets.Editors.ProjectEditor.h"

#include "Editor.Models.EntityListModel.h"
#include "Editor.Models.ProjectHierarchyModel.h"


#include <QDir>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>


namespace nEditor {
namespace nMainWindows {


//--------------------------------------------------------------------------------------
//----------------------------------------------------------- Construction / Destruction


cMainWindow::~cMainWindow()
{
    Destroy();
}


cMainWindow::cMainWindow( QWidget*  parent ) :
    tSuperClass( parent ),
    mMainCaptionWidget( NULL ),
    mMainContentWidget( NULL ),
    mProject( NULL ),
    mEntityListModel( NULL ),
    mProjectHierarchyModel( NULL )
{
    tSelf::Init();
    tSelf::Build();
    tSelf::Compose();
}


//--------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------- Slots


void
cMainWindow::NewProjectDialog()
{
    QFile projectFile =  QFileDialog::getSaveFileName( this, tr( "Select location" ) );
    QFileInfo nfo( projectFile );
    if( nfo.suffix().toStdString() != "proj" )
    {
        projectFile.setFileName( projectFile.fileName() + ".proj" );
        nfo.setFile( projectFile );
    }

    QDir parentProjectDir = nfo.dir();

    if( parentProjectDir.exists() )
    {
        QString projectName = nfo.fileName();
        QString baseDirName = nfo.baseName();
        QString projectDirStr = parentProjectDir.absolutePath() + "/" + baseDirName;
        QDir projectDir( projectDirStr );

        if( projectDir.exists() )
        {
            // We should never end up here
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this, "Project directory already exists", "Overwrite ?", QMessageBox::Yes|QMessageBox::No);
            if ( reply == QMessageBox::No )
                return;
        }
        else
        {
            parentProjectDir.mkdir( baseDirName );
        }

        if( mProject )
        {
            mProject->Finalize();
            delete  mProject;
        }

        nStdFileSystem::path projectPath = projectDir.absolutePath().toStdString();
        mProject = new ::nCore::nProject::cProject( baseDirName.toStdString(), projectPath.string() );
        mProject->MakeProjectDirectories();
        mProject->Initialize();

        if( mProjectHierarchyModel )
        {
            delete  mProjectHierarchyModel;
        }

        mProjectHierarchyModel = new  ::nQt::nModels::cProjectHierarchyModel( mProject );
        mMainContentWidget->AccessibleChildren().mProjectTreeEditor->ProjectLoaded( mProjectHierarchyModel );
    }
}


void
cMainWindow::OpenProjectDialog()
{

}


//--------------------------------------------------------------------------------------
//------------------------------------------------------------------------ GUI utilities


void
cMainWindow::Init()
{
    mMainCaptionWidget = new ::nEditor::nWidgets::cMainCaption( NULL );
    mMainContentWidget = new ::nEditor::nWidgets::cMainContent( NULL );

    //CHECK: not sure what this is for.
    mEntityListModel = new ::nQt::nModels::cEntityListModel( NULL );
}


void
cMainWindow::Build()
{
    setMinimumSize( 600, 400 );
    tSuperClass::SetCaptionWidget( mMainCaptionWidget );
    tSuperClass::SetCenterWidget( mMainContentWidget );

    auto project_editor = mMainContentWidget->AccessibleChildren().mProjectTreeEditor;
    project_editor->setObjectName( "cProjectEditor" );

    auto menu = mMainCaptionWidget->MenuBar();
    QObject::connect( menu->mActionNew, SIGNAL( triggered() ), this, SLOT( NewProjectDialog() ) );
    QObject::connect( menu->mActionOpen, SIGNAL( triggered() ), this, SLOT( OpenProjectDialog() ) );

    /*
    connect( ui.actionToogle_Grid, &QAction::triggered, ui.screenEditor, &cScreenEditor::ToggleGridVisible );
    connect( ui.actionSnapGrid, &QAction::triggered, ui.screenEditor, &cScreenEditor::SetSnapGridUp );
    connect( ui.actionPropertyEditor, &QAction::triggered, this, &cBoltEditor::TogglePropertyEditor );
    connect( ui.menuView, &QMenu::aboutToShow, this, &cBoltEditor::UpdateMenuInfos );
    */
}


void
cMainWindow::Compose()
{
    // NOTHING ATM
}


void
cMainWindow::Destroy()
{
    delete  mMainCaptionWidget;
    mMainCaptionWidget = 0;

    delete  mMainContentWidget;
    mMainContentWidget = 0;
}


} // nMainWindows
} // nEditor

#endif // USE_RIVET
