#include "Editor.Widgets.Editors.ProjectEditor.h"

#include "Core.Project.Project.h"

#include "Editor.Models.LayerModel.h"
#include "Editor.Models.ProjectHierarchyModel.h"
#include "Editor.Models.ProjectPropertiesModel.h"
#include "Editor.Models.EntityModel.h"
#include "Editor.Models.ComponentModel.h"
#include "Editor.Models.TreeWrapperProject.h"
#include "Editor.Models.SystemModel.h"


#include <QFileDialog>
#include <QModelIndex>

cProjectEditor::~cProjectEditor()
{
}


cProjectEditor::cProjectEditor( QWidget * Parent ) :
    tSuperClass( Parent )
{
    ui.setupUi( this );

    connect( ui.hierarchyViewer, &cProjectHierarchyViewer::prototypeEditionAsked, this, &cProjectEditor::PrototypeEditionAsked );
    connect( ui.hierarchyViewer, &cProjectHierarchyViewer::componentEditionAsked, this, &cProjectEditor::ComponentEditionAsked );
    connect( ui.hierarchyViewer, &cProjectHierarchyViewer::screenEditionAsked, this, &cProjectEditor::ScreenEditionAsked );

    connect( ui.hierarchyViewer, &cProjectHierarchyViewer::itemClicked, this, &cProjectEditor::ProjectItemClicked );
    connect( this, &cProjectEditor::entitySelectionChanged, ui.hierarchyViewer, &cProjectHierarchyViewer::EntitySelectionChanged );
    connect( ui.hierarchyViewer, &cProjectHierarchyViewer::showEntityProperties, this, &cProjectEditor::showEntityProperties );
}


void
cProjectEditor::AskFileAndSetProject()
{
    std::string newProjectFileName;
    QFileDialog fileAsking( this, tr( "Save your project" ), "", tr( "Project (*.proj)" ) );
    fileAsking.setDefaultSuffix( "proj" );

    if( !fileAsking.exec() )
        return;

    newProjectFileName = fileAsking.selectedFiles().last().toStdString();
    mProject->ProjectFilePath( newProjectFileName );
}


void
cProjectEditor::SaveProject()
{
    ui.hierarchyViewer->SaveProject();
}


void
cProjectEditor::SaveProjectAs()
{
    if( mProject )
    {
        AskFileAndSetProject();
        ui.hierarchyViewer->SaveProject();
    }
}


void
cProjectEditor::PrototypeEditionAsked( QModelIndex iIndex )
{
    emit  prototypeEditionAsked( iIndex );
}


void
cProjectEditor::ComponentEditionAsked( QModelIndex iIndex )
{
    emit  componentEditionAsked( iIndex );
}


void
cProjectEditor::ScreenEditionAsked( QModelIndex iIndex )
{
    emit  screenEditionAsked( iIndex );
}


void
cProjectEditor::ProjectItemClicked( QModelIndex iIndex )
{
    if( !iIndex.isValid() )
        return;

    auto item = static_cast< ::nQt::nModels::cTreeWrapperNode* >( iIndex.internalPointer() );
    if( item->Type() == "Layer" )
    {
        auto itemAsLayerNode = dynamic_cast< ::nQt::nModels::cTreeWrapperNodeHierarchyLayer* >( item );
        emit showItemProperty( std::make_shared< ::nQt::nModels::cLayerModel >( itemAsLayerNode->Layer() ) );
    }
    else if( item->Type() == "Project" )
    {
        auto itemAsNodeProject = dynamic_cast< ::nQt::nModels::cTreeWrapperNodeHierarchyProject* >( item );
        emit showItemProperty( std::make_shared< ::nQt::nModels::cProjectPropertiesModel >( itemAsNodeProject->Project() ) );
    }
    else if( item->Type() == "Entity" )
    {
        auto itemAsEntityNode = dynamic_cast< ::nQt::nModels::cTreeWrapperNodeHierarchyEntity* >( item );
        auto entity = itemAsEntityNode->Entity().GetEntity();
        if( entity )
        {
            emit showItemProperty( std::make_shared< ::nQt::nModels::cEntityModel >( entity ) );
            emit showEntityAnimation( entity );
        }
    }
    else if( item->Type() == "Component" )
    {
        auto itemAsComponentNode = dynamic_cast< ::nQt::nModels::cTreeWrapperNodeHierarchyComponent* >( item );
        emit showItemProperty( std::make_shared< ::nQt::nModels::cComponentModel >( itemAsComponentNode->Component() ) );
    }
    else if( item->Type() == "System" )
    {
        auto itemAsSystemNode = dynamic_cast<::nQt::nModels::cTreeWrapperNodeHierarchySystem*>( item );
        emit showItemProperty( std::make_shared< ::nQt::nModels::cSystemModel >( itemAsSystemNode->System() ) );
    }
}


void
cProjectEditor::ProjectLoaded( ::nQt::nModels::cProjectHierarchyModel* iProject )
{
    mProject = iProject->Project();
    ui.hierarchyViewer->ProjectLoaded( iProject );
}


