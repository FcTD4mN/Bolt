#include "Editor.BoltQtWidgets.EntityProperty.h"

#include "Core.ECS.Core.Entity.h"
#include "Core.ECS.Core.Component.h"

#include "Core.ECS.Utilities.EntityParser.h"
#include "Core.ECS.Utilities.ComponentRegistry.h"

#include "Editor.BoltQtModels.EntityModel.h"

#include <QTreeWidget>
#include <QComboBox>

cEntityProperty::~cEntityProperty()
{
    delete  mComboDelegate; // Might not be required, if treeView actually does it. If we crash here, just remove this line
}


cEntityProperty::cEntityProperty( QWidget * Parent ) :
    tSuperClass( Parent )
{
    ui.setupUi( this );
    mComboDelegate = new  cEntityPropertyDelegate;
    ui.treeView->setItemDelegate( mComboDelegate );
}


void
cEntityProperty::selectedEntitiesChanged( ::nECS::cEntity * iEntity )
{
    if( iEntity )
    {
        mModel = new ::nQt::nModels::cEntityModel( iEntity );
        ui.treeView->setModel( mModel );
        ui.editEntityName->setText( iEntity->ID().c_str() );
    }
    else
    {
        ui.treeView->setModel( 0 );
        ui.editEntityName->setText( "No entity to edit / Multiple selection" );
    }

    mComboDelegate->SetEntity( iEntity );
}


void
cEntityProperty::addEmptyComponent()
{
    mModel->AddEmptyComponent();
}


void
cEntityProperty::removeComponent()
{
    mModel->RemoveComponent( ui.treeView->currentIndex() );
}



// ==================================================================
// ==================================================================
// ==================================================================



cEntityPropertyDelegate::cEntityPropertyDelegate( QWidget * iParent ) :
    tSuperClass( iParent ),
    mEntity( 0 )
{
}


QWidget *
cEntityPropertyDelegate::createEditor( QWidget * iParent, const QStyleOptionViewItem & iOption, const QModelIndex & iIndex ) const
{
    if( iIndex.parent() == QModelIndex() )
        return  new QComboBox( iParent );

    return  tSuperClass::createEditor( iParent, iOption, iIndex );
}


void
cEntityPropertyDelegate::setEditorData( QWidget * iEditor, const QModelIndex & iIndex ) const
{
    if( mEntity && iIndex.parent() == QModelIndex() )
    {
        auto combo = dynamic_cast<QComboBox*>( iEditor );
        if( combo )
        {
            QString currentComponentName = iIndex.data( Qt::DisplayRole ).toString();
            combo->addItem( currentComponentName );

            for( int i = 0; i < ::nECS::cComponentRegistry::Instance()->GetComponentCount(); ++i )
            {
                auto component = ::nECS::cComponentRegistry::Instance()->GetComponentAtIndex( i );
                std::string compName = component->Name();

                if( mEntity->GetComponentByName( compName ) == nullptr ) // We can only see components that are not already in the entity
                {
                    if( component->Name() != currentComponentName.toStdString() )
                    {
                        combo->addItem( component->Name().c_str() );
                    }
                }
            }
        }
    }
    else
    {
        tSuperClass::setEditorData( iEditor, iIndex );
    }
}


void
cEntityPropertyDelegate::setModelData( QWidget * iEditor, QAbstractItemModel * iModel, const QModelIndex & iIndex ) const
{
    if( mEntity && iIndex.parent() == QModelIndex() )
    {
        auto combo = dynamic_cast<QComboBox*>( iEditor );
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
cEntityPropertyDelegate::SetEntity( ::nECS::cEntity * iEntity )
{
    mEntity = iEntity;
}
