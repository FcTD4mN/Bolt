#include "Editor.Models.TreeWrapperProject.h"

#include "Core.Base.Variant.h"

#include "Core.ECS.Core.Component.h"
#include "Core.ECS.Core.System.h"

#include "Core.Project.Project.h"
#include "Core.Screen.Screen.h"

#include "Core.Render.Layer.h"


namespace nQt {
namespace nModels {


cTreeWrapperNodeHierarchyBase::~cTreeWrapperNodeHierarchyBase()
{
}


cTreeWrapperNodeHierarchyBase::cTreeWrapperNodeHierarchyBase( cTreeWrapperNode * iParent ) :
    tSuperClass( iParent ),
    mIsAnAsset( false )
{
    mIcon = QIcon( "resources/Editor/icons/folder.png" );
}


bool
cTreeWrapperNodeHierarchyBase::IsAnAsset() const
{
    return  mIsAnAsset;
}


void
cTreeWrapperNodeHierarchyBase::IsAnAsset( bool iIsIt )
{
    mIsAnAsset = iIsIt;
}


QIcon
cTreeWrapperNodeHierarchyBase::Icon()
{
    return  mIcon;
}


// ======================================================================
// ======================================================================
// ======================================================================


cTreeWrapperNodeHierarchyProject::~cTreeWrapperNodeHierarchyProject()
{
}


 cTreeWrapperNodeHierarchyProject::cTreeWrapperNodeHierarchyProject( cTreeWrapperNode* iParent, ::nCore::nProject::cProject* iProject ) :
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


// ------ DATA


int
cTreeWrapperNodeHierarchyProject::DataCount() const
{
    return  1;
}


QVariant
cTreeWrapperNodeHierarchyProject::DataAtColumn( int iColumn )
{
    return  mProject->Name().c_str();
}


bool
cTreeWrapperNodeHierarchyProject::SetData( int iIndex, const QVariant & iData )
{
    mProject->Name( iData.toString().toStdString() );
    return  true;
}


void
cTreeWrapperNodeHierarchyProject::AppendData( const QVariant & iData )
{
    // Nothing
}


// ------ ACCESS


::nCore::nProject::cProject*
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

     mIcon = QIcon( "resources/Editor/icons/screen.png" );
}


std::string
cTreeWrapperNodeHierarchyScreen::Type() const
{
    return  "Screen";
}


// ------ DATA


int
cTreeWrapperNodeHierarchyScreen::DataCount() const
{
    return  1;
}


QVariant
cTreeWrapperNodeHierarchyScreen::DataAtColumn( int iColumn )
{
    return  mScreen->Name().c_str();
}


bool
cTreeWrapperNodeHierarchyScreen::SetData( int iIndex, const QVariant & iData )
{
    mScreen->Name( iData.toString().toStdString() );
    return  true;
}


void
cTreeWrapperNodeHierarchyScreen::AppendData( const QVariant & iData )
{
    // Nothing
}


// ------ ACCESS


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


cTreeWrapperNodeHierarchyLayer::cTreeWrapperNodeHierarchyLayer( cTreeWrapperNode* iParent, ::nCore::nRender::cLayer* iLayer ) :
    tSuperClass( iParent ),
    mLayer( iLayer )
{
    if( mLayer )
        AppendData( mLayer->Name().c_str() );
    else
        AppendData( "New Layer" );

    // This node builds its own children, it seems natural to do it this way,
    // most early treeNodes doesn't because we followed Qt example workflow essentially
    for( int k = 0; k < mLayer->EntityCount(); ++k )
    {
        ::nCore::nECS::nCore::cEntity* entity = mLayer->EntityAtIndex( k );
        cTreeWrapperNodeHierarchyEntity* entityNode = new cTreeWrapperNodeHierarchyEntity( this, entity );
    }

    mIcon = QIcon( "resources/Editor/icons/layer.png" );
}


std::string
cTreeWrapperNodeHierarchyLayer::Type() const
{
    return  "Layer";
}


// ------ DATA


int
cTreeWrapperNodeHierarchyLayer::DataCount() const
{
    return  1;
}


QVariant
cTreeWrapperNodeHierarchyLayer::DataAtColumn( int iColumn )
{
    return  mLayer->Name().c_str();
}


bool
cTreeWrapperNodeHierarchyLayer::SetData( int iIndex, const QVariant & iData )
{
    // Can't edit layer's name from the project tree, but from the property editor, so that there's only ONE model that does editing
    return  true;
}


void
cTreeWrapperNodeHierarchyLayer::AppendData( const QVariant & iData )
{
    // Nothing
}


// ------ ACCESS


::nCore::nRender::cLayer*
cTreeWrapperNodeHierarchyLayer::Layer()
{
    return  mLayer;
}


int
cTreeWrapperNodeHierarchyLayer::EntityNodeIndex( const ::nCore::nECS::nCore::cEntity * iEntity )
{
    int i = 0;
    for( auto child : mChildren )
    {
        auto entityNode = dynamic_cast< cTreeWrapperNodeHierarchyEntity* >( child );
        if( entityNode && entityNode->Entity().GetEntity() == iEntity )
            return  i;
        ++i;
    }

    return  -1;
}


// ===========================================================================
// ===========================================================================
// ===========================================================================


cTreeWrapperNodeHierarchyEntity::~cTreeWrapperNodeHierarchyEntity()
{
}


cTreeWrapperNodeHierarchyEntity::cTreeWrapperNodeHierarchyEntity( cTreeWrapperNode * iParent, ::nCore::nECS::nCore::cEntityHandle iEntity ) :
    tSuperClass( iParent ),
    mEntity( iEntity)
{
    if( !mEntity.IsHandleValid() )
        AppendData( "New Entity" );

    mIcon = QIcon( "resources/Editor/icons/entity.png" );
}


cTreeWrapperNodeHierarchyEntity::cTreeWrapperNodeHierarchyEntity( ::nCore::nECS::nCore::cEntityHandle iEntity ) :
    tSuperClass( 0 ),
    mEntity( iEntity)
{
    if( !mEntity.IsHandleValid() )
        AppendData( "New Entity" );

    mIcon = QIcon( "resources/Editor/icons/entity.png" );
}


std::string
cTreeWrapperNodeHierarchyEntity::Type() const
{
    return  "Entity";
}


// ------ DATA


int
cTreeWrapperNodeHierarchyEntity::DataCount() const
{
    return  1;
}


QVariant
cTreeWrapperNodeHierarchyEntity::DataAtColumn( int iColumn )
{
    auto entity = mEntity.GetEntity();
    if( !entity )
        return  "INVALID ENTITY";

    return  entity->ID().c_str();
}


bool
cTreeWrapperNodeHierarchyEntity::SetData( int iIndex, const QVariant & iData )
{
    // Can't edit entity's name from the project tree, but from the property editor, so that there's only ONE model that does editing
    return  true;
}


void
cTreeWrapperNodeHierarchyEntity::AppendData( const QVariant & iData )
{
    // Nothing
}


// ------ ACCESS


::nCore::nECS::nCore::cEntityHandle
cTreeWrapperNodeHierarchyEntity::Entity()
{
    return  mEntity;
}


// ===========================================================================
// ===========================================================================
// ===========================================================================


cTreeWrapperNodeHierarchyComponent::~cTreeWrapperNodeHierarchyComponent()
{
}


cTreeWrapperNodeHierarchyComponent::cTreeWrapperNodeHierarchyComponent( cTreeWrapperNode * iParent, ::nCore::nECS::nCore::cComponent* iComponent ) :
    tSuperClass( iParent ),
    mComponent( iComponent )
{
    if( !mComponent )
        AppendData( "New Component" );
}


cTreeWrapperNodeHierarchyComponent::cTreeWrapperNodeHierarchyComponent( ::nCore::nECS::nCore::cComponent* iComponent ) :
    tSuperClass( 0 ),
    mComponent( iComponent )
{
    if( !mComponent )
        AppendData( "New Component" );
}


std::string
cTreeWrapperNodeHierarchyComponent::Type() const
{
    return  "Component";
}


// ------ DATA


int
cTreeWrapperNodeHierarchyComponent::DataCount() const
{
    return  1;
}


QVariant
cTreeWrapperNodeHierarchyComponent::DataAtColumn( int iColumn )
{
    return  mComponent->Name().c_str();
}


bool
cTreeWrapperNodeHierarchyComponent::SetData( int iIndex, const QVariant & iData )
{
    // Can't edit component's name from the project tree, but from the property editor, so that there's only ONE model that does editing
    return  true;
}


void
cTreeWrapperNodeHierarchyComponent::AppendData( const QVariant & iData )
{
    // Nothing
}


// ------ ACCESS


::nCore::nECS::nCore::cComponent*
cTreeWrapperNodeHierarchyComponent::Component()
{
    return  mComponent;
}


// ===========================================================================
// ===========================================================================
// ===========================================================================


cTreeWrapperNodeHierarchySystem::~cTreeWrapperNodeHierarchySystem()
{
}


cTreeWrapperNodeHierarchySystem::cTreeWrapperNodeHierarchySystem( cTreeWrapperNode * iParent, ::nCore::nECS::nCore::cSystem* iSystem ) :
    tSuperClass( iParent ),
    mSystem( iSystem )
{
    if( mSystem )
        AppendData( mSystem->Name().c_str() );
    else
        AppendData( "New System" );

    mIcon = QIcon( "resources/Editor/icons/system.png" );
}


std::string
cTreeWrapperNodeHierarchySystem::Type() const
{
    return  "System";
}


// ------ ACCESS


::nCore::nECS::nCore::cSystem*
cTreeWrapperNodeHierarchySystem::System()
{
    return  mSystem;
}


void
cTreeWrapperNodeHierarchySystem::System( ::nCore::nECS::nCore::cSystem * iSystem )
{
    mSystem = iSystem;
}

} //nModels
} //nQt

