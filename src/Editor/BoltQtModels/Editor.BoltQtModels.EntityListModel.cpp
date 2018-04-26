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


void
cEntityListModel::AddNewPrototype()
{
    ::nECS::cEntity* newEntity = new ::nECS::cEntity( ::nApplication::cEditorApplication::App()->World() );

    QModelIndex baseNode = QModelIndex();

    beginInsertRows( baseNode, rowCount( baseNode ), rowCount( baseNode ) );
    mParserInstance->RegisterEntity( newEntity );
    endInsertRows();
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

    mParserInstance->UnregisterEntityByName( entityName );
    dataChanged( index( 0, 0 ), index( mParserInstance->EntityCount(), 0 ) );
}

} //nQt
} //nModels
