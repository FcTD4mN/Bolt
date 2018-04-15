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
    return  2;
}


QVariant
cEntityModel::data( const QModelIndex& iIndex, int iRole ) const
{
    if( !iIndex.isValid() )
        return  QVariant();

    if( iRole != Qt::DisplayRole )
        return  QVariant();

    cTreeWrapperNode* item = ExtractTreeWrapper( iIndex );
    return  item->DataAtColumn( iIndex.column() );
}


QVariant
cEntityModel::headerData( int iSection, Qt::Orientation iOrientation, int iRole ) const
{
    if( iRole != Qt::DisplayRole )
        return  QVariant();

    if( iOrientation == Qt::Horizontal )
        return  mRootItem->DataAtColumn( iSection );

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
        return  0;

    return  QAbstractItemModel::flags( iIndex );
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
        compNode->AppendData( comp->Name().c_str() );
        compNode->AppendData( "" );

        auto compAsGen = dynamic_cast<::nECS::cComponentGeneric*>( comp );
        if( compAsGen )
        {
            for( int j = 0; j < compAsGen->VarCount(); ++j )
            {
                ::nBase::cVariant* var = compAsGen->GetVarAtIndex( j );
                cTreeWrapperNode* varNode = new cTreeWrapperNodeVariable( compNode, var );
                varNode->AppendData( compAsGen->GetVarNameAtIndex( j ).c_str() );
                varNode->AppendData( var->ToString().c_str() );
            }
        }
    }
}

} //nQt
} //nModels
