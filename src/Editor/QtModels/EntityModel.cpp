#include "Editor.Qt.EntityModel.h"


cEntityModel::cEntityModel( cEntity* iEntity, QObject* iParent = 0 ) :
    tSuperClass( iParent ),
    mEntity( iEntity )
{

}

// --------------------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------ Interface Overrides
// --------------------------------------------------------------------------------------------------------------


int
cEntityModel::rowCount( const QModelIndex& iParent = QModelIndex() ) const
{
    // How many things of an entity can we edit ?
    // 1 - Name
    // 2 - Components
    return  2;
}


int
cEntityModel::columnCount( const QModelIndex& iParent = QModelIndex() ) const
{
    if( iParent.row() == 0 ) // If we ask how many "slots" does Name take ? -> 1
        return  1;

    if( iParent.row() == 1 ) // If we ask how many "slots" does Components take ? -> Current component count
        return  mEntity->ComponentCount();

    return  0;
}


QVariant
cEntityModel::data( const QModelIndex& iIndex, int iRole ) const
{
    if( !iIndex.isValid() )
        return  QVariant();

    if( role == Qt::DisplayRole )
    {
        if( iIndex.row() == 0 )
            return  mEntity->Name();
        else if( iIndex.row() == 1 )
            return  mEntity->GetComponentAtIndex( iIndex.column() )->Name();
    }

    return  QVariant();
}


QVariant
cEntityModel::headerData( int iSection, Qt::Orientation iOrientation, int iRole = Qt::DisplayRole ) const
{
    if( role != Qt::DisplayRole )
        return  QVariant();

    if( iOrientation == Qt::Horizontal )
        return  tr( "Entity" )

    return  QVariant();
}

