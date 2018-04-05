#include "QtModels.EntityListModel.h"

#include "ECS/Utilities/EntityParser.h"

cEntityListModel::cEntityListModel( QObject* iParent ) :
    tSuperClass( iParent ),
    mParserInstance( cEntityParser::Instance() )
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
        return  mParserInstance->GetEntityNameAtIndex( iIndex.row() ).c_str();
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

