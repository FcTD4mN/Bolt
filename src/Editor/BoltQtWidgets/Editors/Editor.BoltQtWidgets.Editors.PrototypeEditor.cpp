#include "Editor.BoltQtWidgets.Editors.PrototypeEditor.h"

#include "Core.ECS.Utilities.EntityParser.h"
#include "Core.ECS.Core.Entity.h"
#include "Core.ECS.Core.Component.h"

#include "Editor.BoltQtModels.EntityModel.h"

#include <QtWidgets/QTreeWidget>

cPrototypeEditor::~cPrototypeEditor()
{
}


cPrototypeEditor::cPrototypeEditor( QWidget * Parent ) :
    tSuperClass( Parent )
{
    ui.setupUi( this );
}


void
cPrototypeEditor::SetAllPrototypeListModel( QAbstractItemModel * iModel )
{
    ui.listViewAllPrototypes->setModel( iModel );
}


void
cPrototypeEditor::PrototypeEditionAsked( QModelIndex iIndex )
{
    std::string name = iIndex.data( Qt::DisplayRole ).toString().toStdString();
    ::nECS::cEntity* entProto = ::nECS::cEntityParser::Instance()->GetPrototypeByName( name );

    ui.listViewAllPrototypes->setCurrentIndex( iIndex );
    ui.treeViewPrototype->selectedEntitiesChanged( entProto );
}

