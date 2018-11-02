#include "Editor.Models.EntityListModel.h"

#include "Core.Registries.EntityRegistry.h"
#include "Core.ECS.Core.Entity.h"


namespace  nQt {
namespace  nModels {

cEntityListModel::cEntityListModel( QObject* iParent ) :
    tSuperClass( iParent ),
    mParserInstance( ::nCore::nRegistries::cEntityRegistry::Instance() )
{
}

// --------------------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------ Interface Overrides
// --------------------------------------------------------------------------------------------------------------


int
cEntityListModel::rowCount( const QModelIndex& iParent ) const
{
    return  mParserInstance->ItemCount();
}


QVariant
cEntityListModel::data( const QModelIndex& iIndex, int iRole ) const
{
    if( !iIndex.isValid() )
        return  QVariant();

    if( iRole == Qt::DisplayRole )
    {
        return  mParserInstance->GetItemNamesSorted()[ iIndex.row() ].c_str();
    }

    return  QVariant();
}


QVariant
cEntityListModel::headerData( int iSection, Qt::Orientation iOrientation, int iRole ) const
{
    if( iRole != Qt::DisplayRole )
        return  QVariant();

    if( iOrientation == Qt::Horizontal )
        return  tr( "Entities" );

    return  QVariant();
}


QModelIndex
cEntityListModel::AddNewPrototype()
{
    ::nCore::nECS::nCore::cEntity* newEntity = new ::nCore::nECS::nCore::cEntity();

    QModelIndex baseNode = QModelIndex();

    beginInsertRows( baseNode, rowCount( baseNode ), rowCount( baseNode ) );
    mParserInstance->RegisterItem( newEntity->ID(), newEntity );
    endInsertRows();
    return  GetPrototypeIndex( newEntity );
}


void
cEntityListModel::RemovePrototype( const QModelIndex& iIndex )
{
    // Removing the file
    std::string entityName = data( iIndex, Qt::DisplayRole ).toString().toStdString();

    auto filename = mParserInstance->GetItemFileByItemName( entityName );

    if( remove( filename.string().c_str() ) != 0 )
        perror( "Delete failed\n" );
    else
        printf( "Delete success\n" );

    beginRemoveRows( iIndex.parent(), iIndex.row(), iIndex.row() );

    mParserInstance->UnregisterItemByName( entityName );

    endRemoveRows();
}


QModelIndex
cEntityListModel::GetPrototypeIndex( ::nCore::nECS::nCore::cEntity * iPrototype )
{
    std::vector< std::string > sortedNames = mParserInstance->GetItemNamesSorted();

    for( int i = 0 ; i < sortedNames.size() ; ++ i )
    {
        if( sortedNames[ i ] == iPrototype->ID() )
            return  index( i, 0 );
    }

    return QModelIndex();
}

} //nQt
} //nModels
