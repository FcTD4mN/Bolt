#include "Editor.BoltQtWidgets.ProjectHierarchyViewer.h"

#include "Core.Project.Project.h"

#include "Editor.BoltQtModels.ProjectHierarchyModel.h"

cProjectHierarchyViewer::~cProjectHierarchyViewer()
{
}


cProjectHierarchyViewer::cProjectHierarchyViewer( QWidget * Parent ) :
    tSuperClass( Parent )
{
    ui.setupUi( this );
	ui.treeView->setSelectionMode(QAbstractItemView::SingleSelection);
	ui.treeView->setDragEnabled(true);
	ui.treeView->setAcceptDrops(true);
	ui.treeView->setDropIndicatorShown(true);
}


void
cProjectHierarchyViewer::ProjectLoaded( ::nProject::cProject* iProject )
{
    ui.treeView->setModel( new  ::nQt::nModels::cProjectHierarchyModel( iProject ) );
}


