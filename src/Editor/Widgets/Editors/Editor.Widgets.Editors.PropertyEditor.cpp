#include "Editor.Widgets.Editors.PropertyEditor.h"

#include "Editor.Models.ModelBase.h"

#include <QContextMenuEvent>
#include <QMenu>


cPropertyEditor::~cPropertyEditor()
{
}


cPropertyEditor::cPropertyEditor( QWidget * Parent ) :
    tSuperClass( Parent ),
    mModel( 0 )
{
    ui.setupUi( this );
}


void
cPropertyEditor::contextMenuEvent( QContextMenuEvent * iEvent )
{
    QModelIndex indexUnderMouse = ui.treeView->indexAt( ui.treeView->viewport()->mapFromGlobal( iEvent->globalPos() ) );
    if( !mModel )
        return;

    QStringList allowedActions = mModel->ContextualMenuAllowedActionForIndex( indexUnderMouse );
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
        mModel->ExecuteActionOnIndex( itemAction, indexUnderMouse );
    }

    // DELETION
    for( int i = 0; i < actions.count(); ++i )
        delete  actions[ i ];

    actions.clear();
}


void
cPropertyEditor::closeEvent( QCloseEvent* iEvent )
{
    tSuperClass::closeEvent( iEvent );
}


void
cPropertyEditor::ForceRefresh()
{
    mModel.get()->dataChanged( QModelIndex(), QModelIndex() );
}


void
cPropertyEditor::ShowProperties( const std::shared_ptr< ::nQt::nModels::cModelBase >& iModel )
{
    if( mModel.get() != iModel.get() )
    {
        mModel = iModel;
    }

    ui.treeView->setModel( mModel.get() );

    auto delegate = mModel->CreateModelDelegate();
    if( delegate )
    {
        delete  ui.treeView->itemDelegate();
        ui.treeView->setItemDelegate( delegate );
    }
}

