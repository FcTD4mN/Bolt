#include "Editor.Models.ProjectHierarchyModel.h"

#include "Core.Application.GlobalAccess.h"

#include "Core.Registries.ComponentRegistry.h"
#include "Core.Registries.EntityRegistry.h"
#include "Core.Registries.SystemRegistry.h"
#include "Core.ECS.Core.Entity.h"
#include "Core.ECS.Core.Component.h"
#include "Core.ECS.Core.System.h"
#include "Core.ECS.Core.World.h"

#include "Core.Project.Project.h"
#include "Core.Screen.Screen.h"

#include "Core.Render.Layer.h"
#include "Core.Render.LayerEngine.h"

#include "Editor.Models.TreeWrapperProject.h"

#include <QMessageBox>
#include <QFileDialog>

namespace  nQt {
namespace  nModels {


cProjectHierarchyModel::~cProjectHierarchyModel()
{
}


 cProjectHierarchyModel::cProjectHierarchyModel( ::nCore::nProject::cProject* iProject, QObject* iParent ) :
    tSuperClass( iParent ),
    mProject( iProject )
{
     BuildData();
}


// --------------------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------ Interface Overrides
// --------------------------------------------------------------------------------------------------------------


Qt::ItemFlags
cProjectHierarchyModel::flags( const QModelIndex & iIndex ) const
{
    if( !iIndex.isValid() )
        return 0;

    auto node = dynamic_cast< cTreeWrapperNodeHierarchyBase* >( ExtractTreeWrapper( iIndex ) );
    if( node )
    {
        if( node->Type() == "Entity" )
            return  QAbstractItemModel::flags( iIndex ) | Qt::ItemIsDragEnabled;

        if( node->Type() == "Layer" )
            return  QAbstractItemModel::flags( iIndex ) | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled;

        if( node->Type() == "System" && !node->IsAnAsset() )
            return  QAbstractItemModel::flags( iIndex ) | Qt::ItemIsDragEnabled | Qt::ItemIsEditable;

        if( node->Type() == "Screen" )
            return  QAbstractItemModel::flags( iIndex ) | Qt::ItemIsEditable;

        if( node->DataAtColumn( 0 ) == "Systems" ) // System "folder"
            return  QAbstractItemModel::flags( iIndex ) | Qt::ItemIsDropEnabled;

        if( node->DataAtColumn( 0 ) == "Layers" ) // System "folder"
            return  QAbstractItemModel::flags( iIndex ) | Qt::ItemIsDropEnabled;
    }

    return QAbstractItemModel::flags( iIndex );
}


QVariant
cProjectHierarchyModel::data( const QModelIndex & iIndex, int iRole ) const
{
    if( iRole == Qt::DecorationRole )
    {
        auto itemNode = dynamic_cast< cTreeWrapperNodeHierarchyBase* >( ExtractTreeWrapper( iIndex ) );
        if( itemNode )
            return  itemNode->Icon();
    }
    else
    {
        return  tSuperClass::data( iIndex, iRole );
    }

    return  QVariant();
}


void
cProjectHierarchyModel::BuildData()
{
    if( mRootItem )
        return;

    mRootItem = new cTreeWrapperNodeHierarchyBase( 0 );
    mRootItem->AppendData( "Project Hierarchy Tree" );

    cTreeWrapperNodeHierarchyProject* projectNode = new cTreeWrapperNodeHierarchyProject( mRootItem, mProject );

    if( !mProject )
        return;

    // MAIN PROJECT STRUCTURE ====
    // ===========================
    cTreeWrapperNodeHierarchyBase* screenRoot = new cTreeWrapperNodeHierarchyBase( projectNode );
    screenRoot->AppendData( "Screens" );

    for( int i = 0; i < mProject->ScreenCount(); ++i )
    {
        ::nScreen::cScreen* screen = mProject->ScreenAtIndex( i );
        cTreeWrapperNodeHierarchyScreen* screenNode = new cTreeWrapperNodeHierarchyScreen( screenRoot, screen );

        ::nCore::nRender::cLayerEngine* layerEngine = screen->World()->LayerEngine();

    cTreeWrapperNodeHierarchyBase* layerRoot = new cTreeWrapperNodeHierarchyBase( screenNode );
        layerRoot->AppendData( "Layers" );
        for( int j = 0; j < layerEngine->LayerCount(); ++j )
        {
            ::nCore::nRender::cLayer* layer = layerEngine->LayerAtIndex( j );
            cTreeWrapperNodeHierarchyLayer* layerNode = new cTreeWrapperNodeHierarchyLayer( layerRoot, layer );

            //for( int k = 0; k < layer->EntityCount(); ++k )
            //{
            //    ::nCore::nECS::nCore::cEntity* entity = layer->EntityAtIndex( k );
            //    cTreeWrapperNodeHierarchyEntity* entityNode = new cTreeWrapperNodeHierarchyEntity( layerNode, entity );
            //}
        }

    cTreeWrapperNodeHierarchyBase* systemRoot = new cTreeWrapperNodeHierarchyBase( screenNode );
        systemRoot->AppendData( "Systems" );
        ::nCore::nECS::nCore::cWorld* world = screen->World();
        for( int j = 0; j < world->SystemCount(); ++j )
        {
            ::nCore::nECS::nCore::cSystem* system = world->GetSystemAtIndex( j );
            cTreeWrapperNodeHierarchySystem* systemNode = new cTreeWrapperNodeHierarchySystem( systemRoot, system );
        }
    }

    // ASSETS ====================
    // ===========================
    cTreeWrapperNodeHierarchyBase* assetsRoot = new cTreeWrapperNodeHierarchyBase( projectNode );
    assetsRoot->AppendData( "Assets" );
    assetsRoot->IsAnAsset( true );


    cTreeWrapperNodeHierarchyBase* assetEntityRoot = new cTreeWrapperNodeHierarchyBase( assetsRoot );
    assetEntityRoot->AppendData( "Entities" );
    assetEntityRoot->IsAnAsset( true );
    auto entityRegistry = ::nCore::nRegistries::cEntityRegistry::Instance();
    for( int i = 0; i < entityRegistry->ItemCount(); ++i )
    {
    auto entreety = new cTreeWrapperNodeHierarchyEntity( assetEntityRoot, entityRegistry->GetItemAtIndex( i ) );
    entreety->IsAnAsset( true );
    }


    cTreeWrapperNodeHierarchyBase* assetComponentRoot = new cTreeWrapperNodeHierarchyBase( assetsRoot );
    assetComponentRoot->AppendData( "Components" );
    assetComponentRoot->IsAnAsset( true );
    auto componentRegistry = ::nCore::nRegistries::cComponentRegistry::Instance();
    for( int i = 0; i < componentRegistry->ItemCount(); ++i )
    {
    auto componentNode =  new cTreeWrapperNodeHierarchyComponent( assetComponentRoot, componentRegistry->GetItemAtIndex( i ) );
    componentNode->IsAnAsset( true );
    }


    cTreeWrapperNodeHierarchyBase* assetSystemRoot = new cTreeWrapperNodeHierarchyBase( assetsRoot );
    assetSystemRoot->AppendData( "Systems" );
    assetSystemRoot->IsAnAsset( true );
    auto systemRegistry = ::nCore::nRegistries::cSystemRegistry::Instance();
    for( int i = 0; i < systemRegistry->ItemCount(); ++i )
    {
    auto systemNode = new cTreeWrapperNodeHierarchySystem( assetSystemRoot, systemRegistry->GetItemAtIndex( i ) );
    systemNode->IsAnAsset( true );
    }


    cTreeWrapperNodeHierarchyBase* assetShadersRoot = new cTreeWrapperNodeHierarchyBase( assetsRoot );
    assetShadersRoot->AppendData( "Shaders" );
    assetShadersRoot->IsAnAsset( true );

    cTreeWrapperNodeHierarchyBase* assetImageRoot = new cTreeWrapperNodeHierarchyBase( assetsRoot );
    assetImageRoot->AppendData( "Images" );
    assetImageRoot->IsAnAsset( true );
}


bool
cProjectHierarchyModel::setData( const QModelIndex & index, const QVariant & value, int role )
{
    if( role != Qt::EditRole )
        return false;

    cTreeWrapperNode *item = ExtractTreeWrapper( index );

    if( item->Type() == "System" )
    {
        auto systemNode = dynamic_cast< cTreeWrapperNodeHierarchySystem* >( item );
        if( systemNode )
        {
            auto newSystem = ::nCore::nRegistries::cSystemRegistry::Instance()->CreateSystemFromName( value.toString().toStdString() );

            auto screenNode = dynamic_cast< cTreeWrapperNodeHierarchyScreen* >( item->Parent()->Parent() );
            auto world = screenNode->Screen()->World();

            if( systemNode->System() != 0 )
            world->RemoveSystem( systemNode->System() );

            world->AddSystem( newSystem );
            systemNode->System( newSystem );
        }
    }

    bool result = item->SetData( index.column(), value );
    if( result )
        emit dataChanged( index, index );

    return result;
}


bool
cProjectHierarchyModel::insertRows( int iIndex, int iCount, const QModelIndex & iModelIndex )
{
    auto treeNode = ExtractTreeWrapper( iModelIndex );

    if( treeNode->DataAtColumn( 0 ) == "Layers" )
    {
        auto  screenNode    = dynamic_cast< cTreeWrapperNodeHierarchyScreen* >( treeNode->Parent() );

        ::nScreen::cScreen* screen = screenNode->Screen();
        auto layerEngine = screen->World()->LayerEngine();

        layerEngine->AddLayer();

        beginInsertRows( iModelIndex, layerEngine->LayerCount() -1, layerEngine->LayerCount() -1 );
        new cTreeWrapperNodeHierarchyLayer( treeNode, layerEngine->LayerAtIndex( layerEngine->LayerCount() - 1 ) );
        endInsertRows();

        return  true;
    }
    else if( treeNode->Type() == "Layer" )
    {
        auto  screenNode    = dynamic_cast< cTreeWrapperNodeHierarchyScreen* >( treeNode->Parent()->Parent() );

        ::nScreen::cScreen* screen = screenNode->Screen();
        auto layerEngine = screen->World()->LayerEngine();

        layerEngine->AddLayerAtIndex( iIndex );

        beginInsertRows( iModelIndex.parent(), iIndex, iIndex );
        auto newNode = new cTreeWrapperNodeHierarchyLayer( 0, layerEngine->LayerAtIndex( iIndex ) );
        treeNode->Parent()->InsertChild( newNode, iIndex );
        endInsertRows();

        return  true;
    }

    return  false;
}


bool
cProjectHierarchyModel::RemoveEntity( ::nCore::nECS::nCore::cEntity * iEntity )
{
    QModelIndex entityIndex = GetEntityModelIndex( iEntity );
    auto entityItem = ExtractTreeWrapper( entityIndex );
    auto layerParent = entityItem->Parent();

    removeRow( entityItem->IndexInParent(), entityIndex.parent() );
    iEntity->Destroy();

    return false;
}


bool
cProjectHierarchyModel::RemoveComponent( QModelIndex & iIndex )
{
    //TODO
    //cTreeWrapperNode* item = ExtractTreeWrapper( iIndex );
    //cTreeWrapperNode* parent = item->Parent();

    //if( parent && parent->Type() == "BaseNode" )
    //{
    //    beginRemoveRows( iIndex.parent(), iIndex.row(), iIndex.row() );

    //    if( item->DataAtColumn( 0 ) != "New Component" )
    //        mEntity->RemoveComponentAtIndex( iIndex.row() );

    //    parent->RemoveChildrenAtIndex( iIndex.row(), 1 );

    //    endRemoveRows();

    //    return  true;
    //}

    return  false;
}


QMimeData*
cProjectHierarchyModel::mimeData( const QModelIndexList & indexes ) const
{
    if( indexes.size() == 0 )
    return  0;

    QMimeData* mimeData = new QMimeData();
    QByteArray encodedData;

    QDataStream stream(&encodedData, QIODevice::WriteOnly);

    foreach( const QModelIndex &index, indexes)
    {
    if( index.isValid() )
    {
        auto node = ExtractTreeWrapper( index );
        if( node )
        {
        QVariant pointerLong = (long long)(node);
        stream << pointerLong;
        }
    }
    }

    mimeData->setData("application/treewrappernode", encodedData);

    return mimeData;
}


QStringList
cProjectHierarchyModel::mimeTypes() const
{
    QStringList output;
    output.push_back( "application/treewrappernode" );
    return  output;
}


bool
cProjectHierarchyModel::canDropMimeData( const QMimeData * data, Qt::DropAction action, int row, int column, const QModelIndex & parent ) const
{
    QByteArray  encodedData = data->data("application/treewrappernode");
    QDataStream stream( &encodedData, QIODevice::ReadOnly );

    auto parentNode = dynamic_cast< cTreeWrapperNodeHierarchyBase* >( ExtractTreeWrapper( parent ) );
    if( !parentNode )
    return  false;

    while ( !stream.atEnd() )
    {
    // Getting the item droped's node first
    QVariant data;
    stream >> data;
    auto treeNode = (cTreeWrapperNode*)( data.toLongLong() );

    // Then, we accept if the target is acceptable
    if( parentNode->Type() == "Layer" )
        return  treeNode->Type() == "Entity";

        if( treeNode->Type() == "System" )
            return  parentNode->DataAtColumn( 0 ) == "Systems" && !parentNode->IsAnAsset();

        if( treeNode->Type() == "Layer" )
            return  parentNode->DataAtColumn( 0 ) == "Layers" && !parentNode->IsAnAsset();
    }

    return  false;
}


bool
cProjectHierarchyModel::dropMimeData( const QMimeData * data, Qt::DropAction action, int row, int column, const QModelIndex & iNewParent )
{
    QByteArray  encodedData = data->data( "application/treewrappernode" );
    QDataStream stream( &encodedData, QIODevice::ReadOnly );

    auto newParentNode = dynamic_cast< cTreeWrapperNodeHierarchyBase* >( ExtractTreeWrapper( iNewParent ) );
    if( !newParentNode )
    return  false;

    while ( !stream.atEnd() )
    {
        // Getting the item droped's node first
        QVariant data;
        stream >> data;
        auto treeNode = (cTreeWrapperNodeHierarchyBase*)( data.toLongLong() );

        // Then, we do accordingly to type

        // ENTITIES & LAYERS
        if( newParentNode->Type() == "Layer" && !newParentNode->IsAnAsset() )
        {
            // Dragging an entity in the same layer has no effect ( zorder is from ZDepth component )
            if( treeNode->Parent() == newParentNode )
            return  false;

            auto  screenNode    = dynamic_cast< cTreeWrapperNodeHierarchyScreen* >( newParentNode->Parent()->Parent() );
            auto  theScreen     = screenNode->Screen();
            auto  entityNode    = dynamic_cast< cTreeWrapperNodeHierarchyEntity* >( treeNode );

            ::nCore::nECS::nCore::cEntity* theEntityToAdd = entityNode->Entity().GetEntity();
            if( theEntityToAdd && treeNode->IsAnAsset() )
                theEntityToAdd = theEntityToAdd->Clone();

            // Then add into the new one
            int index = theScreen->World()->AddEntityAndPutInLayer( theEntityToAdd, newParentNode->IndexInParent() );
            if( index < 0 )
                return  false; // False means the model won't handle anything automatically = won't remove the original dragged item, as we didn't manage to put it in a new layer

            // Update the tree : we don't have to do the remove, it's done automatically
            beginInsertRows( iNewParent, index, index );
            auto newNode = new cTreeWrapperNodeHierarchyEntity( theEntityToAdd );
            newParentNode->InsertChild( newNode, index );
            endInsertRows();

            return  !treeNode->IsAnAsset(); // Model will automatically handle old values and call a removerows where needed if the entity is not an asset
        }

        // DRAGGING LAYER
        else if( newParentNode->DataAtColumn( 0 ) == "Layers" )
        {
            auto  layerNode     = dynamic_cast< cTreeWrapperNodeHierarchyLayer* >( treeNode );
            auto  screenNode    = dynamic_cast< cTreeWrapperNodeHierarchyScreen* >( newParentNode->Parent() );
            ::nScreen::cScreen* screen = screenNode->Screen();
            auto layerEngine = screen->World()->LayerEngine();

            layerEngine->MoveLayerToIndex( layerNode->Layer(), row );

            // Index correction, as we remove first the systemNode from its old position, the insertion might shift
            int insertionIndex = row >= 0 ? row : 0;
            int oldIndexSystem = layerNode->IndexInParent();
            if( oldIndexSystem < row )
                --insertionIndex;

            // Now we remove from tree wrapper, and then insert it again, with correction of index if required
            removeRow( oldIndexSystem, iNewParent ); // Here, parent is the same for the system, as we drag and drop within the System sub category

            beginInsertRows( iNewParent, insertionIndex, insertionIndex );
            auto newNode = new cTreeWrapperNodeHierarchyLayer( 0, layerNode->Layer() );
            newParentNode->InsertChild( newNode, insertionIndex );
            endInsertRows();
        }

        // SYSTEMS
        else if( newParentNode->DataAtColumn( 0 ) == "Systems" && !newParentNode->IsAnAsset() )
        {
            auto  screenNode    = dynamic_cast< cTreeWrapperNodeHierarchyScreen* >( newParentNode->Parent() );
            auto  systemNode    = dynamic_cast< cTreeWrapperNodeHierarchySystem* >( treeNode );

            ::nCore::nECS::nCore::cSystem* system = systemNode->System();
            ::nScreen::cScreen* screen = screenNode->Screen();

            // Index correction, as we remove first the systemNode from its old position, the insertion might shift
            int insertionIndex = row >= 0 ? row : 0;
            int oldIndexSystem = systemNode->IndexInParent();
            if( oldIndexSystem < row )
                --insertionIndex;

            if( system != NULL )
            {
                // First remove from world
                screen->World()->RemoveSystemByName( system->Name() );

                if( treeNode->IsAnAsset() )
                    system = system->Clone();
                // Insert at new location
                screen->World()->InsertSystem( system, insertionIndex );
            }

            // We check if the system is already in
            bool nodeAlreadyExists = false;
            for( int i = 0; i < newParentNode->ChildrenCount(); ++i )
            {
                if( newParentNode->ChildAtRow( i )->DataAtColumn( 0 ).toString().toStdString() == system->Name() )
                {
                    nodeAlreadyExists = true;
                    oldIndexSystem = i;
                    break;
                }
            }

            // Now we remove from tree wrapper, and then insert it again, with correction of index if required
            if( nodeAlreadyExists )
                removeRow( oldIndexSystem, iNewParent ); // Here, parent is the same for the system, as we drag and drop within the System sub category

            beginInsertRows( iNewParent, insertionIndex, insertionIndex );
            auto newNode = new cTreeWrapperNodeHierarchySystem( 0, system );
            newParentNode->InsertChild( newNode, insertionIndex );
            endInsertRows();

            return  false;
        }
    }

    return  false;
}


Qt::DropActions
cProjectHierarchyModel::supportedDropActions() const
{
    return  Qt::MoveAction | Qt::CopyAction;
}


QStringList
cProjectHierarchyModel::ContextualMenuAllowedActionForIndex( QModelIndex iIndex )
{
    QStringList outputList;

    auto treeNode = dynamic_cast< cTreeWrapperNodeHierarchyBase* >( ExtractTreeWrapper( iIndex ) );

    if( !treeNode->IsAnAsset() )
    {
        // ELEMENTS NODE ========
        if( treeNode->Type() == "Screen" )
        {
            outputList.push_back( "Delete" ); // OK
            outputList.push_back( "Edit" ); // OK
        }
        else if( treeNode->Type() == "Layer" ) // OK
        {
            outputList.push_back( "Create" ); // OK
            outputList.push_back( "Delete" ); // OK
        }
        else if( treeNode->Type() == "System" )
        {
            outputList.push_back( "Remove" ); // OK
        }

        // ROOT NODES ========
        else if( treeNode->DataAtColumn( 0 ) == "Systems" )
        {
            outputList.push_back( "Add" ); // OK
        }
        else if( treeNode->DataAtColumn( 0 ) == "Screens" )
        {
            outputList.push_back( "Create" ); // OK
        }
        else if( treeNode->DataAtColumn( 0 ) == "Layers" )
        {
            outputList.push_back( "Create" ); // OK
        }
    }
    else
    {
        // ASSETS ========
        if( treeNode->Type() == "Component" )
        {
            outputList.push_back( "Save" ); // OK
            //outputList.push_back( "SaveAs" ); // TODO
        }
        else if( treeNode->Type() == "Entity" )
        {
            outputList.push_back( "Save" ); // OK
            //outputList.push_back( "SaveAs" ); // TODO
        }
        else if( treeNode->DataAtColumn( 0 ) == "Entities" )
        {
            outputList.push_back( "New Entity" ); // OK
        }
        else if( treeNode->DataAtColumn( 0 ) == "Components" )
        {
            outputList.push_back( "New Component" ); // OK
        }
    }

    return  outputList;
}


void
cProjectHierarchyModel::ExecuteActionOnIndex( const QString& iAction, const QModelIndex& iIndex )
{
    auto treeNode = dynamic_cast< cTreeWrapperNodeHierarchyBase* >( ExtractTreeWrapper( iIndex ) );

    if( !treeNode->IsAnAsset() )
    {
        // ===== SCREENS
        if( treeNode->DataAtColumn( 0 ) == "Screens" && iAction == "Create" )
        {
            auto screenDir = ::nCore::nApplication::cGlobalAccess::Instance()->ProjectFolder() + "/Screens";
            QFileDialog fileAsking( 0, tr( "Save your component" ), screenDir.c_str(), tr( "Screen (*.screen)" ) );
            fileAsking.setDefaultSuffix( "comp" );

            nStdFileSystem::path fullFilePath;

            if( fileAsking.exec() )
            fullFilePath = fileAsking.selectedFiles().last().toStdString();
            else
            return;

            auto  projectNode = dynamic_cast< cTreeWrapperNodeHierarchyProject* >( treeNode->Parent() );
            auto  theProject = projectNode->Project();
            auto  newScreen = new ::nScreen::cScreen( fullFilePath.stem().string() );
            newScreen->FilePath( fullFilePath );
            newScreen->Initialize();
            theProject->AddScreen( newScreen );

            beginInsertRows( iIndex.parent(), theProject->ScreenCount()-1, theProject->ScreenCount()-1 );

            auto newNode = new cTreeWrapperNodeHierarchyScreen( 0, newScreen );
            treeNode->InsertChild( newNode, theProject->ScreenCount()-1 );

            auto* layerRoot = new cTreeWrapperNodeHierarchyBase( newNode );
            layerRoot->AppendData( "Layers" );
            auto* systemRoot = new cTreeWrapperNodeHierarchyBase( newNode );
            systemRoot->AppendData( "Systems" );

            endInsertRows();
        }
        else if( treeNode->Type() == "Screen" && iAction == "Delete" )
        {
            auto  projectNode = dynamic_cast< cTreeWrapperNodeHierarchyProject* >( treeNode->Parent()->Parent() );
            auto  theProject = projectNode->Project();
            theProject->RemoveScreenAtIndex( iIndex.row() );
            removeRow( treeNode->IndexInParent(), iIndex.parent() );

        }
        else if( treeNode->Type() == "Screen" && iAction == "Edit" )
        {
            emit  screenEditionAsked( iIndex );
        }

        // ===== LAYERS
        else if( treeNode->DataAtColumn( 0 ) == "Layers" && iAction == "Create" )
        {
            insertRow( treeNode->ChildrenCount() - 1, iIndex );
        }
        else if( treeNode->Type() == "Layer" && iAction == "Create" )
        {
            insertRow( iIndex.row(), iIndex );
        }
        else if( treeNode->Type() == "Layer" && iAction == "Delete" )
        {
            QMessageBox warning( QMessageBox::Warning, "Warning", "Deleting this layer will destroy all entities within. Continue ?", QMessageBox::Yes | QMessageBox::No );
            if( warning.exec() == QMessageBox::Yes )
            {
                auto  screenNode    = dynamic_cast< cTreeWrapperNodeHierarchyScreen* >( treeNode->Parent()->Parent() );
                ::nScreen::cScreen* screen = screenNode->Screen();

                removeRow( treeNode->IndexInParent(), iIndex.parent() );
                screen->World()->LayerEngine()->DeleteLayerAtIndex( iIndex.row() );
                screen->World()->PurgeEntities();
            }
        }

        // ===== SYSTEMS
        else if( treeNode->DataAtColumn( 0 ) == "Systems" )
        {
            auto  screenNode    = dynamic_cast< cTreeWrapperNodeHierarchyScreen* >( treeNode->Parent() );
            ::nCore::nECS::nCore::cWorld* world = screenNode->Screen()->World();

            beginInsertRows( iIndex.parent(), world->SystemCount(), world->SystemCount() );

            auto newNode = new cTreeWrapperNodeHierarchySystem( 0, 0 );
            treeNode->InsertChild( newNode, world->SystemCount() );
            newNode->AppendData( "NewSystem" );

            endInsertRows();
        }
        else if( treeNode->Type() == "System" && iAction == "Remove" )
        {
            auto  screenNode    = dynamic_cast< cTreeWrapperNodeHierarchyScreen* >( treeNode->Parent()->Parent() );
            auto  systemNode    = dynamic_cast< cTreeWrapperNodeHierarchySystem* >( treeNode );

            ::nCore::nECS::nCore::cSystem* system = systemNode->System();
            ::nScreen::cScreen* screen = screenNode->Screen();

            screen->World()->RemoveSystem( system );
            removeRow( systemNode->IndexInParent(), iIndex.parent() );
        }
    }
    // ASSETS ========
    else
    {
        if( treeNode->Type() == "Component" && iAction == "Save" )
        {
            auto nodeAsComponent = dynamic_cast< cTreeWrapperNodeHierarchyComponent* >( treeNode );
            SaveComponent( nodeAsComponent->Component() );
        }
        else if( treeNode->Type() == "Component" && iAction == "SaveAs" )
        {
            auto nodeAsComponent = dynamic_cast< cTreeWrapperNodeHierarchyComponent* >( treeNode );
            SaveComponentAs( nodeAsComponent->Component() );
        }
        else if( treeNode->Type() == "Entity" && iAction == "Save" )
        {
            auto nodeAsEntity = dynamic_cast< cTreeWrapperNodeHierarchyEntity* >( treeNode );
            SavePrototype( nodeAsEntity->Entity().GetEntity() );
        }
        else if( treeNode->Type() == "Entity" && iAction == "SaveAs" )
        {
            auto nodeAsEntity = dynamic_cast< cTreeWrapperNodeHierarchyEntity* >( treeNode );
            SavePrototypeAs( nodeAsEntity->Entity().GetEntity() );
        }
        else if( treeNode->DataAtColumn( 0 ) == "Entities" && iAction == "New Entity" )
        {
            ::nCore::nECS::nCore::cEntity* newEntity = new ::nCore::nECS::nCore::cEntity();

            beginInsertRows( iIndex, rowCount( iIndex ), rowCount( iIndex ) );

            // Registering the entity
            ::nCore::nRegistries::cEntityRegistry::Instance()->RegisterItem( newEntity->ID(), newEntity );

            // Already associating a file
            nStdFileSystem::path newEntityFile( ::nCore::nApplication::cGlobalAccess::Instance()->ProjectFolder() + "/Assets/Entities/" );
            newEntityFile += newEntity->ID() + ".entity";
            ::nCore::nRegistries::cEntityRegistry::Instance()->SetItemFileUsingItemName( newEntity->ID(), newEntityFile );

            // Creating the node
            auto newEntityNode = new cTreeWrapperNodeHierarchyEntity( treeNode, newEntity );
            newEntityNode->IsAnAsset( true );

            endInsertRows();
        }
        else if( treeNode->DataAtColumn( 0 ) == "Components" && iAction == "New Component" )
        {
            ::nCore::nECS::nCore::cComponentGeneric* newComp = new ::nCore::nECS::nCore::cComponentGeneric( "NewComponent" );

            beginInsertRows( iIndex, rowCount( iIndex ), rowCount( iIndex ) );

            // Registering the component
            ::nCore::nRegistries::cComponentRegistry::Instance()->RegisterItem( newComp->ID(), newComp );

            // Already associating a file
            nStdFileSystem::path newCompFile( ::nCore::nApplication::cGlobalAccess::Instance()->ProjectFolder() + "/Assets/Components/" );
            newCompFile += newComp->ID() + ".comp";
            ::nCore::nRegistries::cComponentRegistry::Instance()->SetItemFileUsingItemName( newComp->ID(), newCompFile );

            // Creating the node
            auto newComponentNode = new cTreeWrapperNodeHierarchyComponent( treeNode, newComp );
            newComponentNode->IsAnAsset( true );

            endInsertRows();
        }
    }
}


QModelIndex
cProjectHierarchyModel::GetEntityModelIndex( const::nCore::nECS::nCore::cEntity * iEntity )
{
    int  entityLayerIndex = iEntity->Layer()->LayerIndex();

    QModelIndex parentLayerIndex = GetLayerModelIndexAtIndex( GetScreenModelIndexAtIndex( mProject->CurrentScreenIndex() ), entityLayerIndex );
    auto parentLayerItem = dynamic_cast< cTreeWrapperNodeHierarchyLayer* >( ExtractTreeWrapper( parentLayerIndex ) );

    return  GetEntityModelIndexAtIndex( parentLayerIndex, parentLayerItem->EntityNodeIndex( iEntity ) );
}


void
cProjectHierarchyModel::AddEntityToCurrentScreenInLayer( ::nCore::nECS::nCore::cEntity * iEntity, int iIndex )
{
    QModelIndex layerAtIndex = GetLayerModelIndexAtIndex( GetScreenModelIndexAtIndex( mProject->CurrentScreenIndex() ), iIndex );

    if( !layerAtIndex.isValid() ) // This most likely means we have no layers at all, so we add one, as you need at least one to hold entities anyway
    {
        // We create a layer
        insertRow( 0, index( 0, 0, GetScreenModelIndexAtIndex( mProject->CurrentScreenIndex() ) ) );
        // We get a valid index
        layerAtIndex = GetLayerModelIndexAtIndex( GetScreenModelIndexAtIndex( mProject->CurrentScreenIndex() ), iIndex );
    }

    // Then we get the screen to add the entity in
    QModelIndex screen = GetScreenModelIndexAtIndex( mProject->CurrentScreenIndex() );
    auto screenNode = dynamic_cast<::nQt::nModels::cTreeWrapperNodeHierarchyScreen* >( ExtractTreeWrapper( screen ) );

    beginInsertRows( layerAtIndex, iIndex, iIndex );

    // Adding in data
    screenNode->Screen()->World()->AddEntityAndPutInLayer( iEntity, iIndex );
    // Creating tree node
    new ::nQt::nModels::cTreeWrapperNodeHierarchyEntity( ExtractTreeWrapper( layerAtIndex ), iEntity );

    // Creating tree nodes
    endInsertRows();
}


void
cProjectHierarchyModel::CloneEntity( ::nCore::nECS::nCore::cEntity * iEntity )
{
    auto clonedEntity = iEntity->Clone();
    int  entityLayerIndex = clonedEntity->Layer()->LayerIndex();

    QModelIndex parentLayerIndex = GetLayerModelIndexAtIndex( GetScreenModelIndexAtIndex( mProject->CurrentScreenIndex() ), entityLayerIndex );

    beginInsertRows( parentLayerIndex, entityLayerIndex, entityLayerIndex );

    auto layerNode = dynamic_cast< ::nQt::nModels::cTreeWrapperNodeHierarchyLayer* >( ExtractTreeWrapper( parentLayerIndex ) );
    new ::nQt::nModels::cTreeWrapperNodeHierarchyEntity( layerNode, clonedEntity );

    endInsertRows();
}


::nCore::nProject::cProject*
cProjectHierarchyModel::Project()
{
    return  mProject;
}


QModelIndex
cProjectHierarchyModel::GetProjectModelIndex()
{
    return  index( 0, 0, QModelIndex() );
}


QModelIndex
cProjectHierarchyModel::GetScreenModelIndexAtIndex( int iIndex )
{
    return  index( iIndex, 0, index( 0, 0, GetProjectModelIndex() ) );
}


QModelIndex
cProjectHierarchyModel::GetLayerModelIndexAtIndex( QModelIndex iScreenModelIndex, int iIndex )
{
    return  index( iIndex, 0, index( 0, 0, iScreenModelIndex ) );
}


QModelIndex
cProjectHierarchyModel::GetEntityModelIndexAtIndex( QModelIndex iLayerModelIndex, int iIndex )
{
    return  index( iIndex, 0, iLayerModelIndex );
}


// ----------------------------------------------------------
// ----------------------------------------------------------


void
cProjectHierarchyModel::SaveProject()
{
    if( !mProject )
        return;

    if( mProject->ProjectFilePath().extension() != ".proj" ) // Or we could do like : if( ProjectFilePath is a directory ), meaning, we didn't specify a project file yet
        _AskFileAndSetProject();

    mProject->SaveXML();

    // We save all file related stuff :
    // -Entities prototypes
    // -Components
    AssetsEntitiesEnumerator( [ this ]( ::nCore::nECS::nCore::cEntity* iEntity ) { SavePrototype( iEntity ); } );
    AssetsComponentsEnumerator( [ this ]( ::nCore::nECS::nCore::cComponent* iComponent ) { SaveComponent( iComponent ); } );
}


void
cProjectHierarchyModel::SaveComponent( const ::nCore::nECS::nCore::cComponent* iComponent )
{
    if( iComponent )
    {
        std::string compID = iComponent->ID();

        QMessageBox msg;
        msg.setIcon( QMessageBox::Critical );
        if( compID == "" )
        {
            msg.setText( "Component name is empty" );
            msg.exec();
            return;
        }

        nStdFileSystem::path filePath = ::nCore::nRegistries::cComponentRegistry::Instance()->GetItemFileByItemName( iComponent->ID() );
        nStdFileSystem::path newFilePath;

        if( filePath == "void" ) // This allows to skip the c++ integrated components
        {
            return;
        }
        else if( filePath.empty() )
        {
            nStdFileSystem::path pathAndFile( ::nCore::nApplication::cGlobalAccess::Instance()->ProjectFolder() + "/Assets/Components/" );
            pathAndFile += compID.c_str();

            QFileDialog fileAsking( 0, tr( "Save your component" ), pathAndFile.string().c_str(), tr( "Component (*.comp)" ) );
            fileAsking.setDefaultSuffix( "comp" );

            if( fileAsking.exec() )
                newFilePath = fileAsking.selectedFiles().last().toStdString();
            else
                return;

            ::nCore::nRegistries::cComponentRegistry::Instance()->SetItemFileUsingItemName( iComponent->ID(), newFilePath );
        }
        else
        {
            // Removing the old file
            if( remove( filePath.string().c_str() ) != 0 )
                perror( "Delete failed\n" );
            else
                printf( "Delete success\n" );

            newFilePath = ::nCore::nApplication::cGlobalAccess::Instance()->ProjectFolder() + "/Assets/Components/";
            newFilePath += compID.c_str();
            newFilePath += ".comp";

            ::nCore::nRegistries::cComponentRegistry::Instance()->SetItemFileUsingItemName( iComponent->ID(), newFilePath );
        }

        // Creating the new file
        tinyxml2::XMLDocument doc;
        tinyxml2::XMLElement* elm = doc.NewElement( "component" );

        iComponent->SaveXML( elm, &doc );

        doc.InsertFirstChild( elm );

        tinyxml2::XMLError error = doc.SaveFile( newFilePath.string().c_str() );
        if( error )
            return;
    }
}


void
cProjectHierarchyModel::SaveComponentAs( const ::nCore::nECS::nCore::cComponent* iComponent )
{
    return; // i don't think this is correct :
    // here we check if the comp we save as hasn't already a file, in which case we remove the already existing comp
    // if it has no file associated we simply save, but this is wrong
    // it could have no associated file, and we choose to save it under an existing comp file, then we must erase the existing one as well
    // so this should be adressed after gamejam, right now there are other things to do, saving as is bonus atm

    if( !iComponent )
        return;

    nStdFileSystem::path pathAndFile( ::nCore::nApplication::cGlobalAccess::Instance()->ProjectFolder() + "/Assets/Components/" );
    pathAndFile += iComponent->ID().c_str();

    QFileDialog fileAsking( 0, tr( "Save your component" ), pathAndFile.string().c_str(), tr( "Component (*.comp)" ) );
    fileAsking.setDefaultSuffix( "comp" );

    nStdFileSystem::path fullFilePath;

    if( fileAsking.exec() )
        fullFilePath = fileAsking.selectedFiles().last().toStdString();
    else
        return;

    auto registry = ::nCore::nRegistries::cComponentRegistry::Instance();
    nStdFileSystem::path  entityCurrentFile = registry->GetItemFileByItemName( iComponent->ID() );

    // Creating the new file
    tinyxml2::XMLDocument doc;
    tinyxml2::XMLElement* elm = doc.NewElement( "component" );

    // If the newly chosen file is an already existing file ( another existing entity ), we override it
    if( !entityCurrentFile.empty() )
    {
        ::nCore::nECS::nCore::cComponent*  componentAssociatedToRequiredFilename = registry->GetItemAssociatedToFile( fullFilePath );

        if( componentAssociatedToRequiredFilename )
            registry->UnregisterItemByName( componentAssociatedToRequiredFilename->ID() );

        ::nCore::nECS::nCore::cComponent* clone = iComponent->Clone();
        std::string newCompID = fullFilePath.stem().string();

        // We compute a unique name
        int i = 2;
        while( registry->IsItemNameAlreadyInRegistry( newCompID ) )
        {
            newCompID = fullFilePath.stem().string() + std::to_string( i );
            ++i;
        }
        clone->ID( newCompID );

        registry->RegisterItem( newCompID, clone );
        clone->SaveXML( elm, &doc );
        registry->SetItemFileUsingItemName( clone->ID(), entityCurrentFile );
    }
    // Otherwise we simply save it
    else
    {
        iComponent->SaveXML( elm, &doc );
        registry->SetItemFileUsingItemName( iComponent->ID(), fullFilePath );
    }

    doc.InsertFirstChild( elm );

    tinyxml2::XMLError error = doc.SaveFile( fullFilePath.string().c_str() );
    if( error )
        return;
}


void
cProjectHierarchyModel::SavePrototype( const ::nCore::nECS::nCore::cEntity* iEntity )
{
    if( iEntity )
    {
        std::string entityName = iEntity->ID();

        QMessageBox msg;
        msg.setIcon( QMessageBox::Critical );
        if( entityName == "" )
        {
            msg.setText( "Prototype name is empty" );
            msg.exec();
            return;
        }

        nStdFileSystem::path filePath = ::nCore::nRegistries::cEntityRegistry::Instance()->GetItemFileByItemName( entityName );
        nStdFileSystem::path newFilePath;

        if( filePath.empty() )
        {
            nStdFileSystem::path pathAndFile( ::nCore::nApplication::cGlobalAccess::Instance()->ProjectFolder() + "/Assets/Entities/" );
            pathAndFile += entityName.c_str();

            QFileDialog fileAsking( 0, tr( "Save your entity" ), pathAndFile.string().c_str(), tr( "Entity (*.entity)" ) );
            fileAsking.setDefaultSuffix( "entity" );

            if( fileAsking.exec() )
                newFilePath = fileAsking.selectedFiles().last().toStdString();
            else
                return;

            ::nCore::nRegistries::cEntityRegistry::Instance()->SetItemFileUsingItemName( entityName, newFilePath );
        }
        else
        {
            // Removing the old file
            if( remove( filePath.string().c_str() ) != 0 )
                perror( "Delete failed\n" );
            else
                printf( "Delete success\n" );

            newFilePath = ::nCore::nApplication::cGlobalAccess::Instance()->ProjectFolder() + "/Assets/Entities/";
            newFilePath += entityName.c_str();
            newFilePath += ".entity";
        }

        // Creating the new file
        tinyxml2::XMLDocument doc;
        tinyxml2::XMLElement* elm = doc.NewElement( "entity" );

        iEntity->SaveXML( elm, &doc );

        doc.InsertFirstChild( elm );

        tinyxml2::XMLError error = doc.SaveFile( newFilePath.string().c_str() );
        if( error )
            return;
    }
}


void
cProjectHierarchyModel::SavePrototypeAs( const ::nCore::nECS::nCore::cEntity* iEntity )
{
    // Same as component save as
    return;
    nStdFileSystem::path pathAndFile( ::nCore::nApplication::cGlobalAccess::Instance()->ProjectFolder() + "/Assets/Entities/" );
    pathAndFile += iEntity->ID().c_str();

    QFileDialog fileAsking( 0, tr( "Save your entity" ), pathAndFile.string().c_str(), tr( "Entity (*.entity)" ) );
    fileAsking.setDefaultSuffix( "entity" );

    nStdFileSystem::path fullFilePath;
    if( fileAsking.exec() )
        fullFilePath = fileAsking.selectedFiles().last().toStdString();
    else
        return;

    auto parser = ::nCore::nRegistries::cEntityRegistry::Instance();
    nStdFileSystem::path  entityCurrentFilePath = parser->GetItemFileByItemName( iEntity->ID() );

    // Creating the new file
    tinyxml2::XMLDocument doc;
    tinyxml2::XMLElement* elm = doc.NewElement( "entity" );

    if( !entityCurrentFilePath.empty() )
    {
        ::nCore::nECS::nCore::cEntity*  entityAssociatedToRequiredFilename = parser->GetItemAssociatedToFile( fullFilePath );

        if( entityAssociatedToRequiredFilename )
            parser->UnregisterItemByName( entityAssociatedToRequiredFilename->ID() );

        ::nCore::nECS::nCore::cEntity* clone = iEntity->Clone();
        std::string newEntName = fullFilePath.stem().string();
        int i = 2;
        while( parser->IsItemNameAlreadyInRegistry( newEntName ) )
        {
            newEntName = fullFilePath.stem().string() + std::to_string( i );
            ++i;
        }
        clone->SetID( newEntName );

        parser->RegisterItem( newEntName, clone );
        clone->SaveXML( elm, &doc );
        ::nCore::nRegistries::cEntityRegistry::Instance()->SetItemFileUsingItemName( clone->ID(), fullFilePath );
    }
    else
    {
        iEntity->SaveXML( elm, &doc );
        ::nCore::nRegistries::cEntityRegistry::Instance()->SetItemFileUsingItemName( iEntity->ID(), fullFilePath );
    }

    doc.InsertFirstChild( elm );

    tinyxml2::XMLError error = doc.SaveFile( fullFilePath.string().c_str() );
    if( error )
        return;
}


void
cProjectHierarchyModel::_AskFileAndSetProject()
{
    std::string newProjectFileName;
    QFileDialog fileAsking( 0, tr( "Save your project" ), mProject->ProjectDirectory().string().c_str(), tr( "Project (*.proj)" ) );
    fileAsking.setDefaultSuffix( "proj" );

    if( !fileAsking.exec() )
        return;

    newProjectFileName = fileAsking.selectedFiles().last().toStdString();
    mProject->ProjectFilePath( newProjectFileName );
}


cTreeWrapperNode*
cProjectHierarchyModel::_FindNodeWithinNode( const QVariant& iNodeFirstColumnData, cTreeWrapperNode * iNodeToSearch )
{
    cTreeWrapperNode* assetsNode = 0;

    for( int i = 0; i < iNodeToSearch->ChildrenCount(); ++i )
    {
        auto child = iNodeToSearch->ChildAtRow( i );
        if( child->DataAtColumn( 0 ) == iNodeFirstColumnData )
        {
            assetsNode = child;
            break;
        }
    }

    return  assetsNode;
}


// --------------------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------- Enumerators
// --------------------------------------------------------------------------------------------------------------


void
cProjectHierarchyModel::AssetsEntitiesEnumerator( std::function<void( ::nCore::nECS::nCore::cEntity* )> iFunction )
{
    // Root item has only one child, being the project node
    cTreeWrapperNode* assetsNode = _FindNodeWithinNode( "Assets", mRootItem->ChildAtRow( 0 ) );

    if( assetsNode )
    {
        cTreeWrapperNode* entityPrototypesNode = _FindNodeWithinNode( "Entities", assetsNode );
        if( entityPrototypesNode )
        {
            for( int i = 0; i < entityPrototypesNode->ChildrenCount(); ++i )
            {
                auto entityPrototype = dynamic_cast<cTreeWrapperNodeHierarchyEntity*>( entityPrototypesNode->ChildAtRow( i ) );
                iFunction( entityPrototype->Entity().GetEntity() );
            }
        }
    }
}


void
cProjectHierarchyModel::AssetsComponentsEnumerator( std::function<void( ::nCore::nECS::nCore::cComponent* )> iFunction )
{
    // Root item has only one child, being the project node
    cTreeWrapperNode* assetsNode = _FindNodeWithinNode( "Assets", mRootItem->ChildAtRow( 0 ) );

    if( assetsNode )
    {
        cTreeWrapperNode* entityPrototypesNode = _FindNodeWithinNode( "Components", assetsNode );
        if( entityPrototypesNode )
        {
            for( int i = 0; i < entityPrototypesNode->ChildrenCount(); ++i )
            {
                auto componentNode = dynamic_cast<cTreeWrapperNodeHierarchyComponent*>( entityPrototypesNode->ChildAtRow( i ) );
                iFunction( componentNode->Component() );
            }
        }
    }
}


} //nQt
} //nModels
