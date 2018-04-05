#include "Editor.Qt.EntityListModel.h"


cEntityListModel::cEntityListModel( QObject* iParent = 0 ) :
    tSuperClass( iParent ),
    mParserInstance( cEntityParser::Instance() )
{

}

// --------------------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------ Interface Overrides
// --------------------------------------------------------------------------------------------------------------


int
cEntityListModel::rowCount( const QModelIndex& iParent = QModelIndex() ) const
{
    return  mParserInstance->EntityCount();
}


QVariant
cEntityListModel::data( const QModelIndex& iIndex, int iRole ) const
{
    if( !iIndex.isValid() )
        return  QVariant();

    if( role == Qt::DisplayRole )
    {
        return  mParserInstance->GetEntityNameAtIndex( iIndex.row() );
    }

    return  QVariant();
}


QVariant
cEntityListModel::headerData( int iSection, Qt::Orientation iOrientation, int iRole = Qt::DisplayRole ) const
{
    if( role != Qt::DisplayRole )
        return  QVariant();

    if( iOrientation == Qt::Horizontal )
        return  tr( "Entities" )

    return  QVariant();
}

