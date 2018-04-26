#include "Editor.BoltQtModels.ComponentListModel.h"

#include "Editor.Application.EditorApplication.h"

#include "Core.ECS.Utilities.ComponentRegistry.h"
#include "Core.ECS.Core.Component.h"


namespace  nQt {
namespace  nModels {


cComponentListModel::cComponentListModel( QObject* iParent ) :
    tSuperClass( iParent ),
    mComponentRegistryInstance( ::nECS::cComponentRegistry::Instance() )
{
}

// --------------------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------ Interface Overrides
// --------------------------------------------------------------------------------------------------------------


int
cComponentListModel::rowCount( const QModelIndex& iParent ) const
{
    return  mComponentRegistryInstance->ComponentCount();
}


QVariant
cComponentListModel::data( const QModelIndex& iIndex, int iRole ) const
{
    if( !iIndex.isValid() )
        return  QVariant();

    if( iRole == Qt::DisplayRole )
    {
        return  mComponentRegistryInstance->GetComponentNamesSorted()[ iIndex.row() ].c_str();
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


void
cComponentListModel::AddNewComponent()
{
    ::nECS::cComponentGeneric* newComp = new ::nECS::cComponentGeneric( "NewComponent" );

    QModelIndex baseNode = QModelIndex();

    beginInsertRows( baseNode, rowCount( baseNode ), rowCount( baseNode ) );
    mComponentRegistryInstance->RegisterComponent( newComp );
    endInsertRows();
}


void
cComponentListModel::RemoveComponent( QModelIndex & iIndex )
{
    // Removing the file
    std::string compName = data( iIndex, Qt::DisplayRole ).toString().toStdString();

    auto filename = mComponentRegistryInstance->GetComponentFileNameByComponentName( compName );
    std::string originalAsString = std::string( filename.begin(), filename.end() );

    if( remove( originalAsString.c_str() ) != 0 )
        perror( "Delete failed\n" );
    else
        printf( "Delete success\n" );

    mComponentRegistryInstance->UnregisterComponentByName( compName );
    dataChanged( index( 0, 0 ), index( mComponentRegistryInstance->ComponentCount(), 0 ) );
}


} //nQt
} //nModels
