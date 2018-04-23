#include "Editor.BoltQtModels.EntityModel.h"

#include "Core.ECS.Core.Entity.h"
#include "Core.ECS.Core.Component.h"

#include "Core.ECS.Utilities.ComponentRegistry.h"

#include "Editor.BoltQtModels.TreeWrapper.h"
#include "Editor.BoltQtModels.TreeWrapperEntity.h"


namespace  nQt {
namespace  nModels {


cEntityModel::~cEntityModel()
{
    delete  mRootItem;
}


cEntityModel::cEntityModel( ::nECS::cEntity* iEntity, QObject* iParent ) :
    tSuperClass( iParent ),
    mEntity( iEntity )
{
    BuildData();
}

// --------------------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------ Interface Overrides
// --------------------------------------------------------------------------------------------------------------


int
cEntityModel::rowCount( const QModelIndex& iParent ) const
{
    cTreeWrapperNode* parentItem = ExtractTreeWrapper( iParent );
    return  parentItem->ChildrenCount();
}


int
cEntityModel::columnCount( const QModelIndex& iParent ) const
{
    return  mRootItem->DataCount();
}


QVariant
cEntityModel::data( const QModelIndex& iIndex, int iRole ) const
{
    if( !iIndex.isValid() )
        return  QVariant();

    if( iRole != Qt::DisplayRole && iRole != Qt::EditRole )
        return  QVariant();

    cTreeWrapperNode* item = ExtractTreeWrapper( iIndex );
    return  item->DataAtColumn( iIndex.column() );
}


QVariant
cEntityModel::headerData( int iSection, Qt::Orientation iOrientation, int iRole ) const
{
    if( iOrientation == Qt::Horizontal && iRole == Qt::DisplayRole )
        return mRootItem->DataAtColumn( iSection );

    return  QVariant();
}


QModelIndex
cEntityModel::index( int row, int column, const QModelIndex & iParent ) const
{
    if( iParent.isValid() && iParent.column() != 0 )
        return  QModelIndex();

    cTreeWrapperNode* parentItem = ExtractTreeWrapper( iParent );
    cTreeWrapperNode* child = parentItem->ChildAtRow( row );

    if( child )
        return  createIndex( row, column, child );

    return  QModelIndex();
}


QModelIndex
cEntityModel::parent( const QModelIndex& iIndex ) const
{
    if( !iIndex.isValid() )
        return QModelIndex();

    cTreeWrapperNode* item = ExtractTreeWrapper( iIndex );
    cTreeWrapperNode* parentItem = item->Parent();
    if( parentItem == mRootItem )
        return QModelIndex();

    return  createIndex( item->IndexInParent(), 0, parentItem );
}


Qt::ItemFlags
cEntityModel::flags( const QModelIndex & iIndex ) const
{
    if( !iIndex.isValid() )
        return 0;

    auto item = ExtractTreeWrapper( iIndex );

    // Can't edit variable's names
    if( item->Type() == "Variable" && iIndex.column() == 0 )
        return  QAbstractItemModel::flags( iIndex );

    // Can't edit component's value column
    if( item->Type() == "Component" && iIndex.column() == 1 )
        return  QAbstractItemModel::flags( iIndex );

    return Qt::ItemIsEditable | QAbstractItemModel::flags( iIndex );
}


cTreeWrapperNode*
cEntityModel::ExtractTreeWrapper( const QModelIndex& iIndex ) const
{
    if( !iIndex.isValid() )
        return  mRootItem;

    cTreeWrapperNode* item = static_cast< cTreeWrapperNode* >( iIndex.internalPointer() );
    if( item )
        return  item;

    return  mRootItem;
}


void
cEntityModel::BuildData()
{
    mRootItem = new cTreeWrapperNode( 0 );
    mRootItem->AppendData( "Name" );
    mRootItem->AppendData( "Value" );

    for( unsigned int i = 0; i < mEntity->GetComponentCount(); ++i )
    {
        ::nECS::cComponent* comp = mEntity->GetComponentAtIndex( i );
        cTreeWrapperNode* compNode = new cTreeWrapperNodeComponent( mRootItem, comp );

        auto compAsGen = dynamic_cast<::nECS::cComponentGeneric*>( comp );
        if( compAsGen )
        {
            for( int j = 0; j < compAsGen->VarCount(); ++j )
            {
                ::nBase::cVariant* var = compAsGen->GetVarAtIndex( j );
                cTreeWrapperNode* varNode = new cTreeWrapperNodeVariable( compNode, compAsGen, j );
            }
        }
    }
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

        auto component =::nECS::cComponentRegistry::Instance()->CreateComponentFromName( value.toString().toStdString() );
        mEntity->AddComponent( component );

        auto genericComp = dynamic_cast< ::nECS::cComponentGeneric* >( component );
        if( genericComp )
        {
            beginInsertRows( index, 0, genericComp->VarCount() );
            for( int i = 0; i < genericComp->VarCount(); ++i )
                new cTreeWrapperNodeVariable( item, genericComp, i );
            endInsertRows();
        }
    }

    bool result = item->SetData( index.column(), value );

    if( result )
        emit dataChanged( index, index );

    return result;
}


bool
cEntityModel::setHeaderData( int section, Qt::Orientation orientation, const QVariant & value, int role )
{
    if( role != Qt::EditRole || orientation != Qt::Horizontal )
        return false;

    bool result = mRootItem->SetData( section, value );

    if( result )
        emit headerDataChanged( orientation, section, section );

    return result;
}


bool
cEntityModel::insertColumns( int position, int columns, const QModelIndex & parent )
{
    bool success;

    beginInsertColumns( parent, position, position + columns - 1 );
    success = mRootItem->AppendColumns( position, columns );
    endInsertColumns();

    return success;
}


bool
cEntityModel::removeColumns( int iIndex, int iCount, const QModelIndex & parent )
{
    bool success;

    beginRemoveColumns( parent, iIndex, iIndex + iCount - 1 );
    success = mRootItem->RemoveColumns( iIndex, iCount );
    endRemoveColumns();

    if( mRootItem->DataCount() == 0 )
        removeRows( 0, rowCount() );

    return success;
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


bool
cEntityModel::removeRows( int iIndex, int iCount, const QModelIndex & iParent )
{
    cTreeWrapperNode *parentItem = ExtractTreeWrapper( iParent );
    bool success = true;

    beginRemoveRows( iParent, iIndex, iIndex + iCount - 1 );
    success = parentItem->RemoveChildrenAtIndex( iIndex, iCount );
    endRemoveRows();

    return success;
}


bool
cEntityModel::AddEmptyComponent()
{
    QModelIndex baseNode = QModelIndex();
    beginInsertRows( baseNode, rowCount( baseNode ), rowCount( baseNode ) );

    cTreeWrapperNode* compNode = new cTreeWrapperNodeComponent( mRootItem, 0 );

    endInsertRows();

    return false;
}


bool
cEntityModel::RemoveComponent( QModelIndex & iIndex )
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

} //nQt
} //nModels
