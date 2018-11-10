#include "Editor.MainWindows.BoltEditor.h"


// CORE
#include "Core.ECS.Core.Component.h"
#include "Core.ECS.Core.Entity.h"
#include "Core.ECS.Core.World.h"

#include "Core.Mapping.EntityMap.h"

#include "Core.Project.Project.h"

#include "Core.Screen.Screen.h"


// EDITORS
#include "Editor.Models.EntityListModel.h"
#include "Editor.Models.ProjectHierarchyModel.h"

#include "Editor.Shortcuts.ShortcutManager.h"

#include "Editor.Widgets.CoreSFMLCanvas.h"
#include "Editor.Widgets.Editors.ProjectEditor.h"
#include "Editor.Widgets.Editors.PropertyEditor.h"
#include "Editor.Widgets.Editors.ScreenEditor.h"
#include "Editor.Widgets.Editors.AnimationsComponentEditor.h"


// QT
#include <QTableView>
#include <QComboBox>
#include <QDockWidget>
#include <QFileDialog>


// Extlibs
#include "tinyxml2.h"


namespace nEditor::nMainWindows {


cBoltEditor::~cBoltEditor()
{
    delete  mPrototypeListModel;
}


cBoltEditor::cBoltEditor( QWidget *parent ) :
    QMainWindow( parent ),
    mPropertyEditor( 0 ),
    mProject( 0 )
{
    ui.setupUi( this );
}


void
cBoltEditor::Setup()
{
    mPrototypeListModel = new ::nQt::nModels::cEntityListModel( 0 );
    ui.screenEditor->SetPrototypeListModel( mPrototypeListModel );

    // SHORTCUTS
    auto newProj = SHORTCUT( "ProjectNew" );
    connect( newProj, &QShortcut::activated, ui.actionNew_Project, &QAction::trigger );
    auto openProj = SHORTCUT( "ProjectOpen" );
    connect( openProj, &QShortcut::activated, ui.actionOpen, &QAction::trigger );
    auto save = SHORTCUT( "ProjectSave" );
    connect( save, &QShortcut::activated, ui.actionSave, &QAction::trigger );
    auto saveAs = SHORTCUT( "ProjectSaveAs" );
    connect( saveAs, &QShortcut::activated, ui.actionSave_As, &QAction::trigger );
    auto gridToggle = SHORTCUT( "GridToggle" );
    connect( gridToggle, &QShortcut::activated, ui.actionToogle_Grid, &QAction::trigger );
    auto snapToggle = SHORTCUT( "GridSnapToggle" );
    connect( snapToggle, &QShortcut::activated, ui.actionSnapGrid, &QAction::trigger );


    // ANIMATION
    mAnimationsComponentEditorDock = new QDockWidget( this );
    mAnimationsComponentEditorDock->setWindowTitle( "Animations Editor" );
    mAnimationsComponentEditorDock->setFloating( true );
    mAnimationsComponentEditor = new cAnimationsComponentEditor( mAnimationsComponentEditorDock );
    mAnimationsComponentEditorDock->setWidget( mAnimationsComponentEditor );
    mAnimationsComponentEditorDock->setGeometry( QRect( 550, 300, 800, 300 ) );


    // PROJECT
    mProjectEditorDock = new QDockWidget( this );
    mProjectEditorDock->setWindowTitle( "Project Tree" );
    mProjectEditorDock->setFloating( true );
    mProjectEditor = new  cProjectEditor( mProjectEditorDock );
    mProjectEditorDock->setWidget( mProjectEditor );

    mProjectEditorDock->setGeometry( QRect( 100, 100, 400, 600 ) );


    // PROPERTY EDITOR
    mPropertyEditorDock = new QDockWidget( this );
    mPropertyEditorDock->setWindowTitle( "Property Editor" );
    mPropertyEditorDock->setFloating( true );
    mPropertyEditor = new  cPropertyEditor( mPropertyEditorDock );
    mPropertyEditorDock->setWidget( mPropertyEditor );

    mPropertyEditorDock->setGeometry( QRect( 550, 100, 300, 600 ) );



    // CONNECTIONS
        // MENUBAR // ACTIONS
    connect( ui.actionNew_Project, &QAction::triggered, this, &cBoltEditor::NewProject );
    connect( ui.actionOpen, &QAction::triggered, this, &cBoltEditor::OpenProject );
    connect( ui.actionToogle_Grid, &QAction::triggered, ui.screenEditor, &cScreenEditor::ToggleGridVisible );
    connect( ui.actionSnapGrid, &QAction::triggered, ui.screenEditor, &cScreenEditor::SetSnapGridUp );
    connect( ui.actionPropertyEditor, &QAction::triggered, this, &cBoltEditor::TogglePropertyEditor );
    connect( ui.actionAnimations_Editor, &QAction::triggered, this, &cBoltEditor::ToggleAnimationsComponentEditor );
    connect( ui.menuView, &QMenu::aboutToShow, this, &cBoltEditor::UpdateMenuInfos );

        // ANIMATION
    connect( mProjectEditor, &cProjectEditor::showEntityAnimation, mAnimationsComponentEditor, &cAnimationsComponentEditor::ShowAnimationsComponentFromEntity );
    connect( ui.actionSave, &QAction::triggered, mAnimationsComponentEditor, &cAnimationsComponentEditor::saveAnimation ); // This save MUST be done before project, otherwise the changes won't be saved

        // PROJECT
    connect( ui.actionSave, &QAction::triggered, mProjectEditor, &cProjectEditor::SaveProject );
    connect( ui.actionSave_As, &QAction::triggered, mProjectEditor, &cProjectEditor::SaveProjectAs );

    connect( this, &cBoltEditor::CurrentProjectChanged, mProjectEditor, &cProjectEditor::ProjectLoaded );
    connect( this, &cBoltEditor::CurrentProjectChanged, ui.screenEditor, &cScreenEditor::ProjectLoaded );

    connect( mProjectEditor, &cProjectEditor::screenEditionAsked, ui.screenEditor, &cScreenEditor::ScreenEditionAsked );

    connect( ui.screenEditor, &cScreenEditor::selectionChanged, mProjectEditor, &cProjectEditor::entitySelectionChanged );

        // PROPERTY EDITOR
    connect( mProjectEditor, &cProjectEditor::showItemProperty, mPropertyEditor, &cPropertyEditor::ShowProperties );
    connect( mProjectEditor, &cProjectEditor::showEntityProperties, mPropertyEditor, &cPropertyEditor::ShowProperties );
    connect( ui.screenEditor, &cScreenEditor::forceRefresh, mPropertyEditor, &cPropertyEditor::ForceRefresh );


    // QuickDebug

    mProject = new ::nCore::nProject::cProject( "resources/ProjectTest/ProjectTest.proj" );
    mProject->Initialize();
    mProject->LoadXML();
    for( int i = 0; i < mProject->ScreenCount(); ++i )
        mProject->ScreenAtIndex( i )->LoadXML();

    emit  CurrentProjectChanged( new  ::nQt::nModels::cProjectHierarchyModel( mProject ) );
}


void
cBoltEditor::NewProject()
{
    QString projectDir = QFileDialog::getExistingDirectory( this, "Choose a directory" );
    if( projectDir != "" )
    {
        if( mProject )
        {
            mProject->Finalize();
            delete  mProject;
        }

        nStdFileSystem::path projectPath = projectDir.toStdString();
        mProject = new ::nCore::nProject::cProject( "_UnnamedProject", projectPath.string() );
        mProject->MakeProjectDirectories();
        mProject->Initialize();

        emit  CurrentProjectChanged( new  ::nQt::nModels::cProjectHierarchyModel( mProject ) );
    }
}


void
cBoltEditor::OpenProject()
{
    QString project = QFileDialog::getOpenFileName( this, "Load your project" );
    if( project != "" )
    {
        if( mProject )
        {
            mProject->Finalize();
            delete  mProject;
        }

        mProject = new ::nCore::nProject::cProject( project.toStdString() );
        mProject->Initialize();
        mProject->LoadXML();

        emit  CurrentProjectChanged( new  ::nQt::nModels::cProjectHierarchyModel( mProject ) );
    }
}


void
cBoltEditor::ShowProperties( const std::shared_ptr< ::nQt::nModels::cModelBase >& iModel )
{
    mPropertyEditor->ShowProperties( iModel );
}


void
cBoltEditor::TogglePropertyEditor()
{
    mPropertyEditorDock->setVisible( !mPropertyEditorDock->isVisible() );
}


void
cBoltEditor::ToggleAnimationsComponentEditor()
{
    mAnimationsComponentEditorDock->setVisible( !mAnimationsComponentEditorDock->isVisible() );
}


void
cBoltEditor::UpdateMenuInfos()
{
    ui.actionPropertyEditor->setChecked( mPropertyEditorDock->isVisible() );
    ui.actionAnimations_Editor->setChecked( mAnimationsComponentEditorDock->isVisible() );
}



} //nEditor::nMainWindows


