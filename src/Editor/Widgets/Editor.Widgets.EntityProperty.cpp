//#include "Editor.Widgets.EntityProperty.h"
//
//#include "Core.ECS.Core.Entity.h"
//#include "Core.ECS.Core.Component.h"
//
//#include "Core.ECS.Utilities.EntityParser.h"
//#include "Core.ECS.Utilities.ComponentRegistry.h"
//
//#include "Editor.Models.EntityModel.h"
//
//#include <QComboBox>
//#include <QContextMenuEvent>
//#include <QMenu>
//#include <QTreeWidget>
//
//cEntityProperty::~cEntityProperty()
//{
//    delete  mComboDelegate; // Might not be required, if treeView actually does it. If we crash here, just remove this line
//}
//
//
//cEntityProperty::cEntityProperty( QWidget * Parent ) :
//    tSuperClass( Parent ),
//    mModel( 0 ),
//    mEntity( 0 )
//{
//    ui.setupUi( this );
//    mComboDelegate = new  cEntityPropertyDelegate2;
//    ui.treeView->setItemDelegate( mComboDelegate );
//}
//
//
//QString
//cEntityProperty::GetEntityName()
//{
//    return  ui.editEntityName->text();
//}
//
//
//void
//cEntityProperty::contextMenuEvent( QContextMenuEvent* iEvent )
//{
//    QModelIndex indexUnderMouse = ui.treeView->indexAt( ui.treeView->viewport()->mapFromGlobal( iEvent->globalPos() ) );
//    auto theModel = dynamic_cast< ::nQt::nModels::cEntityModel* >( ui.treeView->model() );
//    if( !theModel )
//        return;
//
//    QStringList allowedActions = theModel->ContextualMenuAllowedActionForIndex( indexUnderMouse );
//    QVector< QAction* > actions; //if action are not pointers, they can't be placed in the menu, we must keep them in a vector and release them after
//    QMenu menu( this );
//
//    for( auto action : allowedActions )
//    {
//        QAction* menuAction = 0;
//        menuAction = new QAction( action );
//        menuAction->setData( action ); // the name of the action
//        menu.addAction( menuAction );
//        actions.append( menuAction );
//    }
//
//    QAction* selectedItem = menu.exec( iEvent->globalPos() );
//    if( selectedItem )
//    {
//        QString  itemAction = selectedItem->data().toString();
//        theModel->ExecuteActionOnIndex( itemAction, indexUnderMouse );
//    }
//
//    // DELETION
//    for( int i = 0; i < actions.count(); ++i )
//        delete  actions[ i ];
//
//    actions.clear();
//}
//
//
//void
//cEntityProperty::selectedEntitiesChanged( ::nCore::nECS::nCore::cEntity * iEntity, ::nQt::nModels::cEntityModel* iModel )
//{
//    mEntity = iEntity;
//    mModel = iModel;
//
//    if( mEntity )
//    {
//        mEntityName = mEntity->ID();
//        ui.treeView->setModel( mModel );
//        ui.editEntityName->setText( mEntity->ID().c_str() );
//    }
//    else
//    {
//        ui.treeView->setModel( 0 );
//        ui.editEntityName->setText( "No entity to edit / Multiple selection" );
//    }
//
//    mComboDelegate->SetEntity( mEntity );
//}
//
//
//void
//cEntityProperty::addEmptyComponent()
//{
//    if( mModel )
//        mModel->AddEmptyComponent();
//}
//
//
//void
//cEntityProperty::removeComponent()
//{
//    if( mModel )
//        mModel->RemoveComponent( ui.treeView->currentIndex() );
//}
//
//
//void
//cEntityProperty::EntityIDChanged()
//{
//    std::string asStd = ui.editEntityName->text().toStdString();
//    if( asStd == mEntityName )
//        return;
//
//    bool available = ::nCore::nECS::nCore::cEntityParser::Instance()->IsIDAvailable( asStd );
//    bool result = false;
//
//    if( available )
//    {
//        result = mEntity->SetID( asStd );
//    }
//
//    if( !result )
//    {
//
//        ui.editEntityName->setStyleSheet( "QLineEdit { background: rgb(200, 50, 50); }" );
//    }
//    else
//    {
//        ui.editEntityName->setStyleSheet( "" );
//        emit  EntityNameChanged( mEntityName.c_str(), mEntity->ID().c_str() );
//        mEntityName = mEntity->ID();
//    }
//}
//
//
//
//// ==================================================================
//// ==================================================================
//// ==================================================================
//
//
//
//cEntityPropertyDelegate2::cEntityPropertyDelegate2( QWidget * iParent ) :
//    tSuperClass( iParent ),
//    mEntity( 0 )
//{
//}
//
//
//QWidget *
//cEntityPropertyDelegate2::createEditor( QWidget * iParent, const QStyleOptionViewItem & iOption, const QModelIndex & iIndex ) const
//{
//    if( iIndex.parent().data() == "Components" )
//        return  new QComboBox( iParent );
//
//    return  tSuperClass::createEditor( iParent, iOption, iIndex );
//}
//
//
//void
//cEntityPropertyDelegate2::setEditorData( QWidget * iEditor, const QModelIndex & iIndex ) const
//{
//    if( mEntity && iIndex.parent().data() == "Components" )
//    {
//        auto combo = dynamic_cast<QComboBox*>( iEditor );
//        if( combo )
//        {
//            QString currentComponentName = iIndex.data( Qt::DisplayRole ).toString();
//            combo->addItem( currentComponentName );
//
//            for( int i = 0; i < ::nCore::nECS::nUtilities::cComponentRegistry::Instance()->ItemCount(); ++i )
//            {
//                auto component = ::nCore::nECS::nUtilities::cComponentRegistry::Instance()->GetItemAtIndex( i );
//                std::string compName = component->Name();
//
//                if( mEntity->GetComponentByID( compName ) == nullptr ) // We can only see components that are not already in the entity
//                {
//                    if( component->Name() != currentComponentName.toStdString() )
//                    {
//                        combo->addItem( component->Name().c_str() );
//                    }
//                }
//            }
//        }
//    }
//    else
//    {
//        tSuperClass::setEditorData( iEditor, iIndex );
//    }
//}
//
//
//void
//cEntityPropertyDelegate2::setModelData( QWidget * iEditor, QAbstractItemModel * iModel, const QModelIndex & iIndex ) const
//{
//    if( mEntity && iIndex.parent().data() == "Components" )
//    {
//        auto combo = dynamic_cast<QComboBox*>( iEditor );
//        if( combo && combo->currentIndex() > 0 ) // index 0 means we selected the same component, so no need to change anything
//        {
//            iModel->setData( iIndex, combo->currentText() );
//        }
//    }
//    else
//    {
//        tSuperClass::setModelData( iEditor, iModel, iIndex );
//    }
//}
//
//
//void
//cEntityPropertyDelegate2::SetEntity( ::nCore::nECS::nCore::cEntity * iEntity )
//{
//    mEntity = iEntity;
//}
