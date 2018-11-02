#include "Editor.Models.ComponentListModel.h"

#include "Core.Registries.ComponentRegistry.h"
#include "Core.ECS.Core.Component.h"


namespace  nQt {
namespace  nModels {


cComponentListModel::cComponentListModel( QObject* iParent ) :
    tSuperClass( iParent ),
    mComponentRegistryInstance( ::nCore::nRegistries::cComponentRegistry::Instance() )
{
}


// --------------------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------ Interface Overrides
// --------------------------------------------------------------------------------------------------------------


int
cComponentListModel::rowCount( const QModelIndex& iParent ) const
{
    return  mComponentRegistryInstance->ItemCount();
}


QVariant
cComponentListModel::data( const QModelIndex& iIndex, int iRole ) const
{
    if( !iIndex.isValid() )
        return  QVariant();

    if( iRole == Qt::DisplayRole )
    {
        return  mComponentRegistryInstance->GetItemNamesSorted()[ iIndex.row() ].c_str();
    }

    return  QVariant();
}


QVariant
cComponentListModel::headerData( int iSection, Qt::Orientation iOrientation, int iRole ) const
{
    if( iRole != Qt::DisplayRole )
        return  QVariant();

    if( iOrientation == Qt::Horizontal )
        return  tr( "Components" );

    return  QVariant();
}


QModelIndex
cComponentListModel::AddNewComponent()
{
    ::nCore::nECS::nCore::cComponentGeneric* newComp = new ::nCore::nECS::nCore::cComponentGeneric( "NewComponent" );

    QModelIndex baseNode = QModelIndex();

    beginInsertRows( baseNode, rowCount( baseNode ), rowCount( baseNode ) );
    mComponentRegistryInstance->RegisterItem( newComp->Name(), newComp );
    endInsertRows();

    return  GetComponentIndex( newComp );
}


void
cComponentListModel::RemoveComponent( const QModelIndex& iIndex )
{
    // Removing the file
    std::string compName = data( iIndex, Qt::DisplayRole ).toString().toStdString();

    nStdFileSystem::path filename = mComponentRegistryInstance->GetItemFileByItemName( compName );

    if( remove( filename.string().c_str() ) != 0 )
        perror( "Delete failed\n" );
    else
        printf( "Delete success\n" );

    beginRemoveRows( iIndex.parent(), iIndex.row(), iIndex.row() );

    mComponentRegistryInstance->UnregisterItemByName( compName );

    endRemoveRows();
}


QModelIndex
cComponentListModel::GetComponentIndex( ::nCore::nECS::nCore::cComponent * iPrototype )
{
    std::vector< std::string > sortedNames = mComponentRegistryInstance->GetItemNamesSorted();

    for( int i = 0; i < sortedNames.size(); ++i )
    {
        if( sortedNames[ i ] == iPrototype->Name() )
            return  index( i, 0 );
    }

    return QModelIndex();
}


} //nQt
} //nModels
