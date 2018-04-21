#include "Editor.BoltQtWidgets.EntityProperty.h"

#include "Core.ECS.Utilities.EntityParser.h"
#include "Core.ECS.Core.Entity.h"
#include "Core.ECS.Core.Component.h"

#include "Editor.BoltQtModels.EntityModel.h"

#include <QtWidgets/QTreeWidget>

cEntityProperty::~cEntityProperty()
{
}


cEntityProperty::cEntityProperty( QWidget * Parent ) :
    tSuperClass( Parent )
{
    ui.setupUi( this );
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

