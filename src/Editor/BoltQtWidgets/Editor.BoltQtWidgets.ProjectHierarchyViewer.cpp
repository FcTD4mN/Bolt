#include "Editor.BoltQtWidgets.ProjectHierarchyViewer.h"

#include "Core.Project.Project.h"

#include "Editor.BoltQtModels.ProjectHierarchyModel.h"

#include <QMenu>
#include <QContextMenuEvent>

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
cProjectHierarchyViewer::contextMenuEvent( QContextMenuEvent* iEvent )
{
	QModelIndex indexUnderMouse = ui.treeView->indexAt( ui.treeView->viewport()->mapFromGlobal( iEvent->globalPos() ) );
	auto theModel =  dynamic_cast< ::nQt::nModels::cProjectHierarchyModel* >( ui.treeView->model() );
	if( !theModel )
		return;

	QStringList allowedActions = theModel->ContextualMenuAllowedActionForIndex( indexUnderMouse );
	QVector< QAction* > actions; //if action are not pointers, they can't be placed in the menu, we must keep them in a vector and release them after
	QMenu menu( this );

	for( auto action : allowedActions )
	{
		QAction* menuAction = 0;
		menuAction = new QAction( action );
		menuAction->setData( action ); // the name of the action
		menu.addAction( menuAction );
		actions.append( menuAction );
	}

	QAction* selectedItem = menu.exec( iEvent->globalPos() );
	if( selectedItem )
	{
		QString  itemAction = selectedItem->data().toString();
		theModel->ExecuteActionOnIndex( itemAction, indexUnderMouse );
	}

	// DELETION
	for( int i = 0; i < actions.count(); ++i )
		delete  actions[i];

	actions.clear();
}


void
cProjectHierarchyViewer::ProjectLoaded( ::nProject::cProject* iProject )
{
    ui.treeView->setModel( new  ::nQt::nModels::cProjectHierarchyModel( iProject ) );
}


