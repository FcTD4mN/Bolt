#include "Editor.BoltQtModels.ComponentModel.h"

#include "Core.ECS.Core.Component.h"

#include "Core.ECS.Utilities.ComponentRegistry.h"

#include "Editor.BoltQtModels.TreeWrapper.h"
#include "Editor.BoltQtModels.TreeWrapperComponent.h"


namespace  nQt {
namespace  nModels {


cComponentModel::~cComponentModel()
{
    delete  mRootItem;
}


cComponentModel::cComponentModel( ::nECS::cComponent* iComponent, QObject* iParent ) :
    tSuperClass( iParent ),
    mComponent( iComponent )
{
    BuildData();
}


// --------------------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------ Interface Overrides
// --------------------------------------------------------------------------------------------------------------


int
cComponentModel::rowCount( const QModelIndex& iParent ) const
{
    cTreeWrapperNode* parentItem = ExtractTreeWrapper( iParent );
    return  parentItem->ChildrenCount();
}


int
cComponentModel::columnCount( const QModelIndex& iParent ) const
{
    return  mRootItem->DataCount();
}


QVariant
cComponentModel::data( const QModelIndex& iIndex, int iRole ) const
{
    if( !iIndex.isValid() )
        return  QVariant();

    if( iRole != Qt::DisplayRole && iRole != Qt::EditRole )
        return  QVariant();

    cTreeWrapperNode* item = ExtractTreeWrapper( iIndex );
    return  item->DataAtColumn( iIndex.column() );
}


QVariant
cComponentModel::headerData( int iSection, Qt::Orientation iOrientation, int iRole ) const
{
    if( iOrientation == Qt::Horizontal && iRole == Qt::DisplayRole )
        return mRootItem->DataAtColumn( iSection );

    return  QVariant();
}


QModelIndex
cComponentModel::index( int row, int column, const QModelIndex & iParent ) const
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
cComponentModel::parent( const QModelIndex& iIndex ) const
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
cComponentModel::flags( const QModelIndex & iIndex ) const
{
    if( !iIndex.isValid() )
        return 0;

    auto item = ExtractTreeWrapper( iIndex );

    // Can't edit component's name nor value's
    if( item->Type() == "Component" )
        return  QAbstractItemModel::flags( iIndex );

    return Qt::ItemIsEditable | QAbstractItemModel::flags( iIndex );
}


cTreeWrapperNode*
cComponentModel::ExtractTreeWrapper( const QModelIndex& iIndex ) const
{
    if( !iIndex.isValid() )
        return  mRootItem;

    cTreeWrapperNode* item = static_cast< cTreeWrapperNode* >( iIndex.internalPointer() );
    if( item )
        return  item;

    return  mRootItem;
}


void
cComponentModel::BuildData()
{
    mRootItem = new cTreeWrapperNodeComponentEditor( 0, mComponent );
    mRootItem->SetData( 0, "Name" );
    mRootItem->SetData( 1, "Type" );

    auto compAsGen = dynamic_cast<::nECS::cComponentGeneric*>( mComponent );
    if( compAsGen )
    {
        for( int j = 0; j < compAsGen->VarCount(); ++j )
        {
            ::nBase::cVariant* var = compAsGen->GetVarAtIndex( j );
            cTreeWrapperNode* varNode = new cTreeWrapperNodeComponentEditorVariable( mRootItem, compAsGen, compAsGen->GetVarNameAtIndex( j ) );
        }
    }
}


bool
cComponentModel::setData( const QModelIndex & index, const QVariant & value, int role )
{
    if( role != Qt::EditRole )
        return false;

    cTreeWrapperNode *item = ExtractTreeWrapper( index );
    auto itemAsVariable = dynamic_cast< cTreeWrapperNodeComponentEditorVariable* >( item );

    if( itemAsVariable )
    {
        if( item->SetData( index.column(), value ) )
        {
            emit dataChanged( index, index );
            return  true;
        }
    }

    return  false;
}


bool
cComponentModel::setHeaderData( int section, Qt::Orientation orientation, const QVariant & value, int role )
{
    if( role != Qt::EditRole || orientation != Qt::Horizontal )
        return false;

    bool result = mRootItem->SetData( section, value );

    if( result )
        emit headerDataChanged( orientation, section, section );

    return result;
}


bool
cComponentModel::insertColumns( int position, int columns, const QModelIndex & parent )
{
    return  false; // Can't add columns
}


bool
cComponentModel::removeColumns( int iIndex, int iCount, const QModelIndex & parent )
{
    return  false; // Can't remove columns
}


bool
cComponentModel::insertRows( int iIndex, int iCount, const QModelIndex & parent )
{
    return  false; // Can't use this basic function
}


bool
cComponentModel::removeRows( int iIndex, int iCount, const QModelIndex & iParent )
{
    return  false; // Can't use this basic function
}


bool
cComponentModel::AddNewVariable()
{
    auto compAsGen = dynamic_cast<::nECS::cComponentGeneric*>( mComponent );
    if( !compAsGen )
        return  false;

    QModelIndex baseNode = QModelIndex();
    beginInsertRows( baseNode, rowCount( baseNode ), rowCount( baseNode ) );

    mRootItem->AddChild();

    endInsertRows();

    return false;
}


bool
cComponentModel::RemoveVariable( const QModelIndex& iIndex )
{
    cTreeWrapperNode* item = ExtractTreeWrapper( iIndex );
    cTreeWrapperNode* parent = item->Parent();
    bool result = false;

    if( parent && parent->Type() == "Component" )
    {
        beginRemoveRows( iIndex.parent(), iIndex.row(), iIndex.row() );

        result = parent->RemoveChildrenAtIndex( iIndex.row(), 1 );

        endRemoveRows();
    }

    return  result;
}

} //nQt
} //nModels
