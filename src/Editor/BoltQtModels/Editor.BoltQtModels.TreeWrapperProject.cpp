#include "Editor.BoltQtModels.TreeWrapperProject.h"

#include "Core.Base.Variant.h"

#include "Core.ECS.Core.Entity.h"
#include "Core.ECS.Core.Component.h"
#include "Core.ECS.Core.System.h"

#include "Core.Project.Project.h"
#include "Core.Screen.Screen.h"

#include "Core.Render.Layer.h"

namespace nQt {
namespace nModels {


cTreeWrapperNodeHierarchyProject::~cTreeWrapperNodeHierarchyProject()
{
}


 cTreeWrapperNodeHierarchyProject::cTreeWrapperNodeHierarchyProject( cTreeWrapperNode* iParent, ::nProject::cProject* iProject ) :
    tSuperClass( iParent ),
    mProject( iProject )
{
     if( mProject )
        AppendData( mProject->Name().c_str() );
     else
        AppendData( "New Project" );
}


std::string
cTreeWrapperNodeHierarchyProject::Type() const
{
    return  "Project";
}


::nProject::cProject*
cTreeWrapperNodeHierarchyProject::Project()
{
    return  mProject;
}


// ======================================================================
// ======================================================================
// ======================================================================


cTreeWrapperNodeHierarchyScreen::~cTreeWrapperNodeHierarchyScreen()
{
}


 cTreeWrapperNodeHierarchyScreen::cTreeWrapperNodeHierarchyScreen( cTreeWrapperNode* iParent, ::nScreen::cScreen* iScreen ) :
    tSuperClass( iParent ),
    mScreen( iScreen )
{
     if( mScreen )
        AppendData( mScreen->Name().c_str() );
     else
        AppendData( "New Screen" );
}


std::string
cTreeWrapperNodeHierarchyScreen::Type() const
{
    return  "Screen";
}


::nScreen::cScreen *
cTreeWrapperNodeHierarchyScreen::Screen()
{
    return  mScreen;
}


// ======================================================================
// ======================================================================
// ======================================================================


cTreeWrapperNodeHierarchyLayer::~cTreeWrapperNodeHierarchyLayer()
{
}


cTreeWrapperNodeHierarchyLayer::cTreeWrapperNodeHierarchyLayer( cTreeWrapperNode* iParent, ::nRender::cLayer* iLayer ) :
    tSuperClass( iParent ),
    mLayer( iLayer )
{
    if( mLayer )
        AppendData( mLayer->Name().c_str() );
    else
        AppendData( "New Layer" );
}


std::string
cTreeWrapperNodeHierarchyLayer::Type() const
{
    return  "Layer";
}


::nRender::cLayer*
cTreeWrapperNodeHierarchyLayer::Layer()
{
    return  mLayer;
}


// ===========================================================================
// ===========================================================================
// ===========================================================================


cTreeWrapperNodeHierarchyEntity::~cTreeWrapperNodeHierarchyEntity()
{
}


cTreeWrapperNodeHierarchyEntity::cTreeWrapperNodeHierarchyEntity( cTreeWrapperNode * iParent, ::nECS::cEntity* iEntity ) :
    tSuperClass( iParent ),
    mEntity( iEntity)
{
    if( mEntity )
        AppendData( mEntity->ID().c_str() );
    else
        AppendData( "New Entity" );
}


cTreeWrapperNodeHierarchyEntity::cTreeWrapperNodeHierarchyEntity( ::nECS::cEntity* iEntity ) :
	tSuperClass(),
	mEntity( iEntity)
{
	if( mEntity )
		AppendData( mEntity->ID().c_str() );
	else
		AppendData( "New Entity" );
}


std::string
cTreeWrapperNodeHierarchyEntity::Type() const
{
    return  "Entity";
}


::nECS::cEntity*
cTreeWrapperNodeHierarchyEntity::Entity()
{
    return  mEntity;
}


// ===========================================================================
// ===========================================================================
// ===========================================================================


cTreeWrapperNodeHierarchySystem::~cTreeWrapperNodeHierarchySystem()
{
}


cTreeWrapperNodeHierarchySystem::cTreeWrapperNodeHierarchySystem( cTreeWrapperNode * iParent, ::nECS::cSystem* iSystem ) :
    tSuperClass( iParent ),
    mSystem( iSystem )
{
    if( mSystem )
        AppendData( mSystem->Name().c_str() );
    else
        AppendData( "New System" );
}


std::string
cTreeWrapperNodeHierarchySystem::Type() const
{
    return  "System";
}


::nECS::cSystem*
cTreeWrapperNodeHierarchySystem::System()
{
    return  mSystem;
}



} //nModels
} //nQt

