#include "Editor.Widgets.ProjectHierarchyViewer.h"


#include "Core.Registries.SystemRegistry.h"
#include "Core.ECS.Core.Entity.h"
#include "Core.ECS.Core.System.h"
#include "Core.ECS.Core.World.h"

#include "Core.Project.Project.h"

#include "Core.Screen.Screen.h"

#include "Editor.Models.ProjectHierarchyModel.h"
#include "Editor.Models.TreeWrapperProject.h"
#include "Editor.Models.EntityModel.h"

#include <QComboBox>
#include <QMenu>
#include <QContextMenuEvent>

#include <set>


cProjectHierarchyViewer::~cProjectHierarchyViewer()
{
    delete  mComboDelegate;
}


cProjectHierarchyViewer::cProjectHierarchyViewer( QWidget * Parent ) :
    tSuperClass( Parent ),
    mSelectionModel( 0 )
{
    ui.setupUi( this );
    ui.treeView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui.treeView->setDragEnabled(true);
    ui.treeView->setAcceptDrops(true);
    ui.treeView->setDropIndicatorShown(true);

    mComboDelegate = new  cProjectHierarchyDelegate();
    ui.treeView->setItemDelegate( mComboDelegate );
    ui.treeView->setSelectionMode( QAbstractItemView::ExtendedSelection );
}


void
cProjectHierarchyViewer::contextMenuEvent( QContextMenuEvent* iEvent )
{
    QModelIndex indexUnderMouse = ui.treeView->indexAt( ui.treeView->viewport()->mapFromGlobal( iEvent->globalPos() ) );

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
        delete  actions[i];

    actions.clear();
}


void
cProjectHierarchyViewer::SaveProject()
{
    if( mModel )
        mModel->SaveProject();
}


void
cProjectHierarchyViewer::PrototypeEditionAsked( QModelIndex iIndex )
{
    emit  prototypeEditionAsked( iIndex );
}


void
cProjectHierarchyViewer::ComponentEditionAsked( QModelIndex iIndex )
{
    emit  componentEditionAsked( iIndex );
}


void
cProjectHierarchyViewer::ScreenEditionAsked( QModelIndex iIndex )
{
    emit  screenEditionAsked( iIndex );
}


void
cProjectHierarchyViewer::EntitySelectionChanged( const std::vector< ::nCore::nECS::nCore::cEntity* >& iEntities )
{
    mSelectionModel->clear();

    for( auto entity : iEntities )
    {
        QModelIndex index = mModel->GetEntityModelIndex( entity );
        mSelectionModel->select( index, QItemSelectionModel::Select );
    }

    ::nCore::nECS::nCore::cEntity* entityToShow = 0;
    if( iEntities.size() == 1 )
        entityToShow = iEntities[ 0 ];

    emit showEntityProperties( std::make_shared< ::nQt::nModels::cEntityModel >( entityToShow ) );
    // TODO: emit a show entityAnimation thing here
}


void
cProjectHierarchyViewer::ProjectLoaded( ::nQt::nModels::cProjectHierarchyModel* iProject )
{
    mModel = iProject;
    ui.treeView->setModel( mModel );

    delete  mSelectionModel;
    mSelectionModel = new QItemSelectionModel( mModel );
    ui.treeView->setSelectionModel( mSelectionModel );

    connect( mSelectionModel, &QItemSelectionModel::currentChanged, this, &cProjectHierarchyViewer::itemClicked );

    mComboDelegate->SetModel( mModel );

    connect( mModel, &::nQt::nModels::cProjectHierarchyModel::prototypeEditionAsked, this, &cProjectHierarchyViewer::PrototypeEditionAsked );
    connect( mModel, &::nQt::nModels::cProjectHierarchyModel::componentEditionAsked, this, &cProjectHierarchyViewer::ComponentEditionAsked);
    connect( mModel, &::nQt::nModels::cProjectHierarchyModel::screenEditionAsked, this, &cProjectHierarchyViewer::ScreenEditionAsked);
}



// ==================================================================
// ==================================================================
// ==================================================================



cProjectHierarchyDelegate::cProjectHierarchyDelegate( QWidget * iParent ) :
    tSuperClass( iParent ),
    mSystem( 0 )
{
}


QWidget *
cProjectHierarchyDelegate::createEditor( QWidget * iParent, const QStyleOptionViewItem & iOption, const QModelIndex & iIndex ) const
{
    if( iIndex.parent().data().toString() == "Systems" )
        return  new QComboBox( iParent );

    return  tSuperClass::createEditor( iParent, iOption, iIndex );
}


void
cProjectHierarchyDelegate::setEditorData( QWidget * iEditor, const QModelIndex & iIndex ) const
{
    if( iIndex.parent().data().toString() == "Systems" )
    {
        auto combo = dynamic_cast< QComboBox* >( iEditor );
        if( combo )
        {
            auto treeNode = mProjectModel->ExtractTreeWrapper( iIndex );
            auto screenNode = dynamic_cast< ::nQt::nModels::cTreeWrapperNodeHierarchyScreen* >( treeNode->Parent()->Parent() );

            if( !screenNode )
                tSuperClass::setEditorData( iEditor, iIndex );

            combo->addItem( "Select a system" );

            auto systemReg = ::nCore::nRegistries::cSystemRegistry::Instance();
            for( int i = 0; i < systemReg->ItemCount(); ++i )
            {
                std::string systemName = systemReg->GetItemAtIndex( i )->Name().c_str();
                if( !screenNode->Screen()->World()->HasSystem( systemName ) )
                    combo->addItem( systemName.c_str() );
            }
        }
    }
    else
    {
        tSuperClass::setEditorData( iEditor, iIndex );
    }

}


void
cProjectHierarchyDelegate::setModelData( QWidget * iEditor, QAbstractItemModel * iModel, const QModelIndex & iIndex ) const
{
    if( iIndex.parent().data().toString() == "Systems" )
    {
        auto combo = dynamic_cast< QComboBox* >( iEditor );
        if( combo && combo->currentIndex() > 0 ) // index 0 means we selected the same component, so no need to change anything
        {
            iModel->setData( iIndex, combo->currentText() );
        }
    }
    else
    {
        tSuperClass::setModelData( iEditor, iModel, iIndex );
    }
}


void
cProjectHierarchyDelegate::SetModel( ::nQt::nModels::cProjectHierarchyModel * iModel)
{
    mProjectModel = iModel;
}




