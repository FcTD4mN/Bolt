#include "Editor.BoltQtModels.EntityModel.h"

#include "Core.ECS.Core.Entity.h"
#include "Core.ECS.Core.Component.h"

namespace  nQt {
namespace  nModels {

cEntityModel::cEntityModel( ::nECS::cEntity* iEntity, QObject* iParent ) :
    tSuperClass( iParent ),
    mEntity( iEntity )
{

}

// --------------------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------ Interface Overrides
// --------------------------------------------------------------------------------------------------------------


int
cEntityModel::rowCount( const QModelIndex& iParent ) const
{
    // How many things of an entity can we edit ?
    // 1 - Name
    // 2 - Components
    return  2;
}


int
cEntityModel::columnCount( const QModelIndex& iParent ) const
{
    if( iParent.row() == 0 ) // If we ask how many "slots" does Name take ? -> 1
        return  1;

    if( iParent.row() == 1 ) // If we ask how many "slots" does Components take ? -> Current component count
        return  mEntity->GetComponentCount();

    return  0;
}


QVariant
cEntityModel::data( const QModelIndex& iIndex, int iRole ) const
{
    if( !iIndex.isValid() )
        return  QVariant();

    if( iRole == Qt::DisplayRole )
    {
        if( iIndex.row() == 0 )
            return  mEntity->ID().c_str();
        else if( iIndex.row() == 1 )
            return  mEntity->GetComponentAtIndex( iIndex.column() )->Name().c_str();
    }

    return  QVariant();
}


QVariant
cEntityModel::headerData( int iSection, Qt::Orientation iOrientation, int iRole ) const
{
    if( iRole != Qt::DisplayRole )
        return  QVariant();

    if( iOrientation == Qt::Horizontal )
        return  tr( "Entity" );

    return  QVariant();
}

} //nQt
} //nModels
