#include "Editor.Models.EntityModel.h"

#include "Core.ECS.Core.Entity.h"
#include "Core.ECS.Core.Component.h"

#include "Core.Registries.ComponentRegistry.h"

#include "Editor.Models.TreeWrapper.h"
#include "Editor.Models.TreeWrapperEntity.h"

#include "Editor.Delegates.EntityProperties.h"


namespace  nQt {
namespace  nModels {


cEntityModel::~cEntityModel()
{
}


cEntityModel::cEntityModel( ::nCore::nECS::nCore::cEntity* iEntity, QObject* iParent ) :
    tSuperClass( iParent ),
    mEntity( iEntity )
{
    BuildData();
}


cEntityModel::cEntityModel( cEntityModel & iRef ) :
    mEntity( iRef.mEntity )
{
    BuildData();
}


// --------------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------- cModelBase
// --------------------------------------------------------------------------------------------------------------


Qt::ItemFlags
cEntityModel::flags( const QModelIndex & iIndex ) const
{
    if( !iIndex.isValid() )
        return 0;

    auto item = ExtractTreeWrapper( iIndex );

    if( item->Type() == "BaseNode" && item->DataAtColumn( 0 ) == "EditAnimations" && iIndex.column() == 1 )
        return  Qt::ItemIsEditable | QAbstractItemModel::flags( iIndex );

    if( item->Type() == "BaseNode" )
        return  QAbstractItemModel::flags( iIndex );

    // Can't edit variable's names
    if( item->Type() == "Variable" && iIndex.column() == 0 )
        return  QAbstractItemModel::flags( iIndex );

    // Can't edit component's value column
    if( item->Type() == "Component" && iIndex.column() == 1 )
        return  QAbstractItemModel::flags( iIndex );

    // Can't edit entity property's left column
    if( item->Type() == "Entity" && iIndex.column() == 0 )
        return  QAbstractItemModel::flags( iIndex );

    return Qt::ItemIsEditable | QAbstractItemModel::flags( iIndex );
}


bool
cEntityModel::setData( const QModelIndex & index, const QVariant & value, int role )
{
    if( role != Qt::EditRole )
        return false;

    cTreeWrapperNode *item = ExtractTreeWrapper( index );

    // Is Qt really that rigid and annoying with models ?
    // Setting a new component will result in removing the whole component node and replacing it with a new one
    // This means, it'll add rows in addition to setting the data.
    // But only here can i send all the beginRemoveRow bullshit
    if( index.column() == 0 && item->Type() == "Component" )
    {
        // First we remove all variables from current component, we do this explicitely like this to keep the viw up to date
        if( item->ChildrenCount() > 0 )
        {
            beginRemoveRows( index, 0, item->ChildrenCount() );

            item->RemoveChildrenAtIndex( 0, item->ChildrenCount() );

            endRemoveRows();
        }

        if( item->DataAtColumn( 0 ) != "New Component" )
            mEntity->RemoveComponentAtIndex( index.row() ); // Removing the component we are replacing from entity

        auto component = ::nCore::nRegistries::cComponentRegistry::Instance()->CreateComponentFromName( value.toString().toStdString() );
        mEntity->AddComponent( component );

        auto genericComp = dynamic_cast< ::nCore::nECS::nCore::cComponentGeneric* >( component );
        if( genericComp )
        {
            beginInsertRows( index, 0, genericComp->VarCount() );
            for( int i = 0; i < genericComp->VarCount(); ++i )
                new cTreeWrapperNodeVariable( item, genericComp, i );
            endInsertRows();
        }
        else
        {
            // Here, we need to address specific cases
            if( component->Name() == "animations" )
            {
                auto animationNode = new cTreeWrapperNode( item );
                animationNode->AppendData( "EditAnimations" );
                animationNode->AppendData( "compAnimations" );
            }
        }
    }

    QString oldEntityName = item->DataAtColumn( 1 ).toString();

    bool result = item->SetData( index.column(), value );

    if( item->Type() == "Entity" && item->DataAtColumn( 0 ) == "ID" )
    {
        emit  EntityNameChanged( oldEntityName, value.toString() );
    }

    if( result )
        emit dataChanged( index, index );

    return result;
}


bool
cEntityModel::insertRows( int iIndex, int iCount, const QModelIndex & parent )
{
    cTreeWrapperNode *parentItem = ExtractTreeWrapper( parent );
    bool success;

    // We can only add components in this model
    if( parentItem->Type() == "BaseNode" ) // If we have the root entity node
    {
        beginInsertRows( parent, iIndex, iIndex + iCount - 1 );

            for( int i = 0; i < iCount; ++i )
            {
                cTreeWrapperNodeComponent* comp = new cTreeWrapperNodeComponent( parentItem, 0 );
                parentItem->AddChild( comp );
            }

        endInsertRows();
    }


    success = true;

    return success;
}


// --------------------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------- Component controls
// --------------------------------------------------------------------------------------------------------------


bool
cEntityModel::AddEmptyComponent( const QModelIndex& iIndex )
{
    if( !mEntity )
        return  true;

    auto item = ExtractTreeWrapper( iIndex );
    if( item->Type() != "BaseNode" )
        return  false;

    QModelIndex baseNode = QModelIndex();
    beginInsertRows( iIndex, item->ChildrenCount(), item->ChildrenCount() );

    new cTreeWrapperNodeComponent( item, 0 );

    endInsertRows();

    return false;
}


bool
cEntityModel::RemoveComponent( const QModelIndex & iIndex )
{
    cTreeWrapperNode* item = ExtractTreeWrapper( iIndex );
    cTreeWrapperNode* parent = item->Parent();

    if( parent && parent->Type() == "BaseNode" )
    {
        beginRemoveRows( iIndex.parent(), iIndex.row(), iIndex.row() );

        if( item->DataAtColumn( 0 ) != "New Component" )
            mEntity->RemoveComponentAtIndex( iIndex.row() );

        parent->RemoveChildrenAtIndex( iIndex.row(), 1 );

        endRemoveRows();

        return  true;
    }

    return  false;
}


bool
cEntityModel::AddEmptyTag( const QModelIndex& iIndex )
{
    if( !mEntity )
        return  true;

    auto item = ExtractTreeWrapper( iIndex );

    beginInsertRows( iIndex, rowCount( iIndex ), rowCount( iIndex ) );

    mEntity->AddTag( "NewTag" );
    cTreeWrapperNodeTag* compNode = new cTreeWrapperNodeTag( item, mEntity->GetHandle(), mEntity->GetTagCount() - 1 );

    endInsertRows();

    return false;
}


bool
cEntityModel::RemoveTag( const QModelIndex & iIndex )
{
    cTreeWrapperNode* item = ExtractTreeWrapper( iIndex );
    cTreeWrapperNode* parent = item->Parent();
    auto itemAsTagNode = dynamic_cast< cTreeWrapperNodeTag* >( item );

    if( item->Type() == "Tag" )
    {
        beginRemoveRows( iIndex.parent(), iIndex.row(), iIndex.row() );

        mEntity->RemoveTag( itemAsTagNode->Tag() );
        parent->RemoveChildrenAtIndex( iIndex.row(), 1 );
        for( int i = iIndex.row(); i < parent->ChildrenCount() ; ++i )
        {
            auto tagNode = dynamic_cast< cTreeWrapperNodeTag* >( parent->ChildAtRow( i ) );
            tagNode->SetTagIndex( i );
        }

        endRemoveRows();

        return  true;
    }

    return  false;
}


void
cEntityModel::UpdateModelByComponentName( const QString & iName )
{
    // We update the model, so that all guis can be sync'ed
    // This method is used when modifying component durectly using entity
    // This seems easier to use than using setData all the way ...

    // First we look for the index holding the component under iName
    for( int i = 0; i < rowCount( QModelIndex() ); ++i )
    {
        QModelIndex ind = index( i, 0, QModelIndex() );
        if( ind.data( Qt::DisplayRole ).toString() == iName )
        {
            // Then we update data in the wrapper
            auto nodeToUpdate = dynamic_cast< cTreeWrapperNodeComponent* >( ExtractTreeWrapper( ind ) );
            auto componentToUpdate = nodeToUpdate->Component();
            if( nodeToUpdate )
            {
                for( int j = 0; j < componentToUpdate->VarCount(); ++j )
                {
                    ::nCore::nBase::cVariant* var = componentToUpdate->GetVarAtIndex( j );
                    nodeToUpdate->ChildAtRow( j )->SetData( 1, var->ToString().c_str() );
                }
            }

            auto topLeft = index( 0, 0, ind );
            auto bottomRight = index( rowCount( ind ) - 1, columnCount( ind ) - 1, ind );
            emit  dataChanged( topLeft, bottomRight );
            break;
        }
    }
}


// --------------------------------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------- ContextualMenu
// --------------------------------------------------------------------------------------------------------------


QStringList
cEntityModel::ContextualMenuAllowedActionForIndex( QModelIndex iIndex )
{
    QStringList outputList;

    auto treeNode = dynamic_cast< cTreeWrapperNode* >( ExtractTreeWrapper( iIndex ) );

    // TAGS
    if( treeNode->Type() == "BaseNode" && treeNode->DataAtColumn( 0 ) == "Tags" )
    {
        outputList.push_back( "Add" );
    }
    else if( treeNode->Type() == "Tag" )
    {
        outputList.push_back( "Delete" );
    }

    // COMPONENTS
    else if( treeNode->Type() == "BaseNode" && treeNode->DataAtColumn( 0 ) == "Components" )
    {
        outputList.push_back( "Add" );
    }
    else if( treeNode->Type() == "Component" )
    {
        outputList.push_back( "Delete" );
    }

    return  outputList;
}


void
cEntityModel::ExecuteActionOnIndex( const QString & iAction, const QModelIndex & iIndex )
{
    auto treeNode = dynamic_cast< cTreeWrapperNode* >( ExtractTreeWrapper( iIndex ) );

    if( treeNode->Type() == "BaseNode" && treeNode->DataAtColumn( 0 ) == "Tags" && iAction == "Add" )
    {
        AddEmptyTag( iIndex );
    }
    else if( treeNode->Type() == "Tag" && iAction == "Delete" )
    {
        RemoveTag( iIndex );
    }


    else if( treeNode->Type() == "BaseNode" && treeNode->DataAtColumn( 0 ) == "Components" && iAction == "Add" )
    {
        AddEmptyComponent( iIndex );
    }
    else if( treeNode->Type() == "Component" && iAction == "Delete" )
    {
        RemoveComponent( iIndex );
    }
}


QStyledItemDelegate *
cEntityModel::CreateModelDelegate()
{
    auto theDelegate = new cEntityPropertiesDelegate();
    theDelegate->SetEntity( mEntity );
    return  theDelegate;
}


void
cEntityModel::BuildData()
{
    if( mRootItem )
        return;

    mRootItem = new cTreeWrapperNode( 0 );
    mRootItem->AppendData( "Name" );
    mRootItem->AppendData( "Value" );

    if( !mEntity )
        return;

    cTreeWrapperNodeEntity* nameRoot = new  cTreeWrapperNodeEntity( mRootItem, mEntity->GetHandle() );

    cTreeWrapperNode* componentRootNode = new  cTreeWrapperNode( mRootItem );
    componentRootNode->AppendData( "Components" );
    componentRootNode->AppendData( "" );

    for( unsigned int i = 0; i < mEntity->GetComponentCount(); ++i )
    {
        ::nCore::nECS::nCore::cComponent* comp = mEntity->GetComponentAtIndex( i );
        cTreeWrapperNode* compNode = new cTreeWrapperNodeComponent( componentRootNode, comp );

        auto compAsGen = dynamic_cast<::nCore::nECS::nCore::cComponentGeneric*>( comp );
        if( compAsGen )
        {
            for( int j = 0; j < compAsGen->VarCount(); ++j )
            {
                ::nCore::nBase::cVariant* var = compAsGen->GetVarAtIndex( j );
                cTreeWrapperNode* varNode = new cTreeWrapperNodeVariable( compNode, compAsGen, j );
            }
        }
        else
        {
            // Here, we need to address specific cases
            auto animationComp = mEntity->GetComponentByName( "animations" );
            if( animationComp )
            {
                auto animationNode = new cTreeWrapperNode( compNode );
                animationNode->AppendData( "EditAnimations" );
                animationNode->AppendData( "compAnimations" );
            }
        }
    }

    cTreeWrapperNode* tagRootNode = new  cTreeWrapperNode( mRootItem );
    tagRootNode->AppendData( "Tags" );
    tagRootNode->AppendData( "" );

    for( unsigned int i = 0; i < mEntity->GetTagCount(); ++i )
    {
        new  cTreeWrapperNodeTag( tagRootNode, mEntity->GetHandle(), i );
    }
}

} //nQt
} //nModels
