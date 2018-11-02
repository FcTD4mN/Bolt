#include "Editor.Widgets.Editors.ScreenEditor.h"

#include "Editor.Models.EntityListModel.h"


cScreenEditor::~cScreenEditor()
{
}


cScreenEditor::cScreenEditor( QWidget * Parent ) :
    tSuperClass( Parent )
{
    ui.setupUi( this );
    connect( ui.listView, &QListView::doubleClicked, this, &cScreenEditor::PrototypeEditionAsked );
    connect( ui.coresfmlcanvas, &CoreSFMLCanvas::selectionChanged, this, &cScreenEditor::selectionChanged );
    connect( ui.listView, &QListView::clicked, ui.coresfmlcanvas, &CoreSFMLCanvas::CurrentPrototypeChanged );
}


void
cScreenEditor::SetPrototypeListModel( ::nQt::nModels::cEntityListModel * iModel )
{
    ui.listView->setModel( iModel );
}


void
cScreenEditor::ScreenEditionAsked( const QModelIndex & iIndex )
{
    ui.coresfmlcanvas->ScreenEditionAsked( iIndex );
}


void
cScreenEditor::CurrentPrototypeChanged( const QModelIndex & iIndex )
{
    ui.coresfmlcanvas->CurrentPrototypeChanged( iIndex );
}


void
cScreenEditor::ToggleGridVisible()
{
    ui.coresfmlcanvas->ToggleGridVisible();
}


void
cScreenEditor::SetSnapGridUp()
{
    ui.coresfmlcanvas->SetSnapGridUp();
}


void
cScreenEditor::ProjectLoaded( ::nQt::nModels::cProjectHierarchyModel * iProject )
{
    ui.coresfmlcanvas->ProjectLoaded( iProject );
}

