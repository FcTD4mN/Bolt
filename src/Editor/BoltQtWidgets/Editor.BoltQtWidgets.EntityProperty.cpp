#include "Editor.BoltQtWidgets.EntityProperty.h"

#include "Core.ECS.Utilities.EntityParser.h"
#include "Core.ECS.Core.Entity.h"
#include "Core.ECS.Core.Component.h"

#include <QtWidgets/QTreeWidget>

cEntityProperty::~cEntityProperty()
{
}


cEntityProperty::cEntityProperty( QWidget * Parent ) :
    tSuperClass( Parent )
{
    ui.setupUi( this );
    QStringList headerLabels;
    headerLabels.push_back( "Name" );
    headerLabels.push_back( "Value" );
    ui.treeWidget->setHeaderLabels( headerLabels );
}


void
cEntityProperty::selectedEntityChanged( QModelIndex iIndex )
{
    mEntity = ::nECS::cEntityParser::Instance()->GetPrototypeByName( iIndex.data().toString().toStdString() );

    ui.editEntityName->setText( mEntity->ID().c_str() );
    ui.treeWidget->clear();

    for( int i = 0; i < mEntity->GetComponentCount(); ++i )
    {
        QTreeWidgetItem* components = new QTreeWidgetItem( ui.treeWidget );
        components->setText( 0, mEntity->GetComponentAtIndex( i )->Name().c_str() );
    }
}

