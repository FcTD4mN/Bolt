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
        ::nQt::nModels::cEntityModel* model = new ::nQt::nModels::cEntityModel( iEntity );
        ui.treeView->setModel( model );
    }
    else
    {
        ui.treeView->setModel( 0 );
    }
}


void
cEntityProperty::selectedEntityChanged( QModelIndex iIndex )
{
    mEntity = ::nECS::cEntityParser::Instance()->GetPrototypeByName( iIndex.data().toString().toStdString() );

    ui.editEntityName->setText( mEntity->ID().c_str() );

    ::nQt::nModels::cEntityModel* model = new ::nQt::nModels::cEntityModel( mEntity );
    ui.treeView->setModel( model );
}

