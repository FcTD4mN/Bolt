#include "Editor.BoltQtModels.EntityModel.h"

#include "Core.ECS.Core.Entity.h"
#include "Core.ECS.Core.Component.h"

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

    beginInsertRows( parent, iIndex, iIndex + iCount - 1 );
    if( parentItem->Type() == "Entity" )
    {
        for( int i = 0; i < iCount; ++i )
        {
            cTreeWrapperNodeComponent* comp = new cTreeWrapperNodeComponent( parentItem, 0 );
            parentItem->AddChild( comp );
        }
    }
    else if( parentItem->Type() == "Component" )
    {
        auto nodeAsComp = dynamic_cast<cTreeWrapperNodeComponent *>( parentItem );
        for( int i = 0; i < iCount; ++i )
        {
            cTreeWrapperNodeVariable* var = new cTreeWrapperNodeVariable( parentItem, nodeAsComp->Component(), -1 );
            parentItem->AddChild( var );
        }
    }
    endInsertRows();

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

} //nQt
} //nModels
