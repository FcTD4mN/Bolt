#include "Editor.BoltQtWidgets.Editors.ProjectEditor.h"

#include "Core.Project.Project.h"

#include <QFileDialog>

cProjectEditor::~cProjectEditor()
{
}


cProjectEditor::cProjectEditor( QWidget * Parent ) :
    tSuperClass( Parent )
{
    ui.setupUi( this );

	connect( ui.spinBoxResWidth,	 SIGNAL( editingFinished() ), this, SLOT(ProjectResolutionChanged()) );
	connect( ui.spinBoxResHeight,	 SIGNAL( editingFinished() ), this, SLOT(ProjectResolutionChanged()) );
	connect( ui.spinBoxFramerate,	 SIGNAL( editingFinished() ), this, SLOT(ProjectFrameLimitChanged()) );
	connect( ui.lineEditProjectName, SIGNAL( editingFinished() ), this, SLOT(ProjectNameChanged()) );
}


void
cProjectEditor::AskFileAndSetProject()
{
	std::string newProjectFileName;
	QFileDialog fileAsking( this, tr( "Save your project" ), "", tr( "Project (*.proj)" ) );
	fileAsking.setDefaultSuffix( "proj" );

	if( !fileAsking.exec() )
		return;

	newProjectFileName = fileAsking.selectedFiles().last().toStdString();
	mProject->ProjectFilePath( newProjectFileName );
}


void
cProjectEditor::SaveProject()
{
	if( mProject )
	{
		if( mProject->ProjectFilePath() == "" )
			AskFileAndSetProject();

		mProject->SaveXML();
	}
}


void
cProjectEditor::SaveProjectAs()
{
	if( mProject )
	{
		AskFileAndSetProject();
		mProject->SaveXML();
	}
}


void
cProjectEditor::ProjectResolutionChanged()
{
	if( mProject )
		mProject->SetResolution( ui.spinBoxResWidth->value(), ui.spinBoxResHeight->value() );
}


void
cProjectEditor::ProjectFrameLimitChanged()
{
	if( mProject )
		mProject->SetLimitFramerate( ui.spinBoxFramerate->value() );
}


void
cProjectEditor::ProjectNameChanged()
{
	if( mProject )
		mProject->Name( ui.lineEditProjectName->text().toStdString() );
}


void
cProjectEditor::ProjectLoaded( ::nProject::cProject* iProject )
{
	mProject = iProject;
    ui.widget->ProjectLoaded( iProject );

	ui.lineEditProjectName->setText( mProject->Name().c_str() );
	ui.spinBoxResWidth->setValue( mProject->ResolutionWidth() );
	ui.spinBoxResHeight->setValue( mProject->ResolutionHeight() );
	ui.spinBoxFramerate->setValue( mProject->LimitFramerate() );
}


