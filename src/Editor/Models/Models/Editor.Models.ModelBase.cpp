#include "Editor.Models.ModelBase.h"

#include "Core.Application.GlobalAccess.h"

#include "Editor.Models.TreeWrapperProject.h"

namespace  nQt {
namespace  nModels {


cModelBase::~cModelBase()
{
    delete  mRootItem;
}


 cModelBase::cModelBase( QObject* iParent ) :
    tSuperClass( iParent ),
     mRootItem( 0 )
{
     // Can't call virtual functions here, as in constructors, class isn't built yet, so virtuality doesn't work, it will only call the one from cModelBase
}


// --------------------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------ Interface Overrides
// --------------------------------------------------------------------------------------------------------------


int
cModelBase::rowCount( const QModelIndex& iParent ) const
{
    cTreeWrapperNode* parentItem = ExtractTreeWrapper( iParent );
    return  parentItem->ChildrenCount();
}


int
cModelBase::columnCount( const QModelIndex& iParent ) const
{
    return  mRootItem->DataCount();
}


QVariant
cModelBase::data( const QModelIndex& iIndex, int iRole ) const
{
    if( !iIndex.isValid() )
        return  QVariant();

    if( iRole != Qt::DisplayRole && iRole != Qt::EditRole )
        return  QVariant();

    cTreeWrapperNode* item = ExtractTreeWrapper( iIndex );
    return  item->DataAtColumn( iIndex.column() );
}


QVariant
cModelBase::headerData( int iSection, Qt::Orientation iOrientation, int iRole ) const
{
    if( iOrientation == Qt::Horizontal && iRole == Qt::DisplayRole )
        return mRootItem->DataAtColumn( iSection );

    return  QVariant();
}


QModelIndex
cModelBase::index( int row, int column, const QModelIndex & iParent ) const
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
cModelBase::parent( const QModelIndex& iIndex ) const
{
    if( !iIndex.isValid() )
        return QModelIndex();

    cTreeWrapperNode* item = ExtractTreeWrapper( iIndex );
    cTreeWrapperNode* parentItem = item->Parent();
    if( parentItem == mRootItem )
        return QModelIndex();

    return  createIndex( parentItem->IndexInParent(), 0, parentItem );
}


Qt::ItemFlags
cModelBase::flags( const QModelIndex & iIndex ) const
{
    if( !iIndex.isValid() )
        return 0;

    return QAbstractItemModel::flags( iIndex );
}


QStyledItemDelegate *
cModelBase::CreateModelDelegate()
{
    return  0;
}


cTreeWrapperNode*
cModelBase::ExtractTreeWrapper( const QModelIndex& iIndex ) const
{
    if( !iIndex.isValid() )
        return  mRootItem;

    cTreeWrapperNode* item = static_cast< cTreeWrapperNode* >( iIndex.internalPointer() );
    if( item )
        return  item;

    return  mRootItem;
}


QModelIndex
cModelBase::GetModelIndexFromWrapper( const cTreeWrapperNode * iNode ) const
{
    QModelIndex element = QModelIndex();
    if( _GetModelIndexFromWrapper( &element, QModelIndex(), iNode ) )
        return  element;

    return  QModelIndex();
}


void
cModelBase::BuildData()
{
    // Nothing here
}


bool
cModelBase::_GetModelIndexFromWrapper( QModelIndex* oMatchingIndex, const QModelIndex& iIndex, const cTreeWrapperNode * iNode ) const
{
    if( ExtractTreeWrapper( iIndex ) == iNode )
    {
        *oMatchingIndex = iIndex;
        return  true;
    }

    for( int i = 0; i < rowCount( iIndex ); ++i )
    {
        if( _GetModelIndexFromWrapper( oMatchingIndex, index( i, 0, iIndex ), iNode ) )
            return  true;
    }

    return  false;
}


bool
cModelBase::setData( const QModelIndex & index, const QVariant & value, int role )
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
cModelBase::setHeaderData( int section, Qt::Orientation orientation, const QVariant & value, int role )
{
    if( role != Qt::EditRole || orientation != Qt::Horizontal )
        return false;

    bool result = mRootItem->SetData( section, value );

    if( result )
        emit headerDataChanged( orientation, section, section );

    return result;
}


bool
cModelBase::insertColumns( int position, int columns, const QModelIndex & parent )
{
    bool success;

    beginInsertColumns( parent, position, position + columns - 1 );
    success = mRootItem->AppendColumns( position, columns );
    endInsertColumns();

    return success;
}


bool
cModelBase::removeColumns( int iIndex, int iCount, const QModelIndex & parent )
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
cModelBase::insertRows( int iIndex, int iCount, const QModelIndex & iModelIndex )
{
    //TODO
    return  false;
}


bool
cModelBase::removeRows( int iIndex, int iCount, const QModelIndex & iParent )
{
    cTreeWrapperNode *parentItem = ExtractTreeWrapper( iParent );
    bool success = true;

    beginRemoveRows( iParent, iIndex, iIndex + iCount - 1 );
    success = parentItem->RemoveChildrenAtIndex( iIndex, iCount );
    endRemoveRows();

    return success;
}


bool
cModelBase::moveRows( const QModelIndex & sourceParent, int sourceRow, int count, const QModelIndex & destinationParent, int destinationChild )
{
    return false;
}


QMimeData*
cModelBase::mimeData( const QModelIndexList & indexes ) const
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

    mimeData->setData( "application/treewrappernode", encodedData);

    return mimeData;
}


QStringList
cModelBase::mimeTypes() const
{
    QStringList output;
    output.push_back( "application/treewrappernode" );
    return  output;
}


QStringList
cModelBase::ContextualMenuAllowedActionForIndex( QModelIndex iIndex )
{
    // Nothing
    return  QStringList();
}


void
cModelBase::ExecuteActionOnIndex( const QString& iAction, const QModelIndex& iIndex )
{
    // Nothing
}


} //nQt
} //nModels
