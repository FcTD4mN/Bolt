#include "Editor.BoltQtModels.EntityListModel.h"

#include "Editor.Application.EditorApplication.h"

#include "Core.ECS.Utilities.EntityParser.h"
#include "Core.ECS.Core.Entity.h"


namespace  nQt {
namespace  nModels {

cEntityListModel::cEntityListModel( QObject* iParent ) :
    tSuperClass( iParent ),
    mParserInstance( ::nECS::cEntityParser::Instance() )
{
}

// --------------------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------ Interface Overrides
// --------------------------------------------------------------------------------------------------------------


int
cEntityListModel::rowCount( const QModelIndex& iParent ) const
{
    return  mParserInstance->EntityCount();
}


QVariant
cEntityListModel::data( const QModelIndex& iIndex, int iRole ) const
{
    if( !iIndex.isValid() )
        return  QVariant();

    if( iRole == Qt::DisplayRole )
    {
        return  mParserInstance->GetEntityNamesSorted()[ iIndex.row() ].c_str();
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
    ::nECS::cEntity* newEntity = new ::nECS::cEntity();

    QModelIndex baseNode = QModelIndex();

    beginInsertRows( baseNode, rowCount( baseNode ), rowCount( baseNode ) );
    mParserInstance->RegisterEntity( newEntity );
    endInsertRows();
    return  GetPrototypeIndex( newEntity );
}


void
cEntityListModel::RemovePrototype( QModelIndex & iIndex )
{
    // Removing the file
    std::string entityName = data( iIndex, Qt::DisplayRole ).toString().toStdString();

    auto filename = mParserInstance->GetEntityFileNameByEntityName( entityName );
    std::string originalAsString = std::string( filename.begin(), filename.end() );

    if( remove( originalAsString.c_str() ) != 0 )
        perror( "Delete failed\n" );
    else
        printf( "Delete success\n" );

    beginRemoveRows( iIndex.parent(), iIndex.row(), iIndex.row() );

    mParserInstance->UnregisterEntityByName( entityName );

    endRemoveRows();
}


QModelIndex
cEntityListModel::GetPrototypeIndex( ::nECS::cEntity * iPrototype )
{
    std::vector< std::string > sortedNames = mParserInstance->GetEntityNamesSorted();

    for( int i = 0 ; i < sortedNames.size() ; ++ i )
    {
        if( sortedNames[ i ] == iPrototype->ID() )
            return  index( i, 0 );
    }

    return QModelIndex();
}

} //nQt
} //nModels
