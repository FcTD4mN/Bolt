#include "Editor.BoltQtWidgets.Editors.ComponentEditor.h"

#include "Core.ECS.Utilities.ComponentRegistry.h"
#include "Core.ECS.Core.Component.h"

#include "Editor.Application.EditorApplication.h"
#include "Editor.BoltQtModels.ComponentListModel.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QTreeWidget>


cComponentEditor::~cComponentEditor()
{
}


cComponentEditor::cComponentEditor( QWidget * Parent ) :
    tSuperClass( Parent ),
    mComponent( 0 )
{
    ui.setupUi( this );
    ::nQt::nModels::cComponentListModel* model = new  ::nQt::nModels::cComponentListModel();
    ui.listViewAllComponents->setModel( model );
}


void
cComponentEditor::SetAllComponentListModel( QAbstractItemModel * iModel )
{
    ui.listViewAllComponents->setModel( iModel );
}


void
cComponentEditor::ComponentEditionAsked( QModelIndex iIndex )
{
    std::string name = iIndex.data( Qt::DisplayRole ).toString().toStdString();
    mComponent = ::nECS::cComponentRegistry::Instance()->GetComponentByName( name );

    ui.editComponentName->setText( name.c_str() );
}


