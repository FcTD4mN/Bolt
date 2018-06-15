#include "Editor.BoltQtWidgets.Editors.ProjectEditor.h"


cProjectEditor::~cProjectEditor()
{
}


cProjectEditor::cProjectEditor( QWidget * Parent ) :
    tSuperClass( Parent )
{
    ui.setupUi( this );
}


void
cProjectEditor::ProjectLoaded( ::nProject::cProject* iProject )
{
    ui.widget->ProjectLoaded( iProject );
}


