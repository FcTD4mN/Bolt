#include "Editor.Models.LayerModel.h"

#include "Core.Render.Layer.h"

#include "Editor.Models.TreeWrapperLayer.h"

namespace  nQt {
namespace  nModels {


cLayerModel::~cLayerModel()
{
}


cLayerModel::cLayerModel( ::nCore::nRender::cLayer* iLayer, QObject* iParent ) :
    tSuperClass( iParent ),
    mLayer( iLayer )
{
    BuildData();
}


cLayerModel::cLayerModel( cLayerModel & iRef ) :
    mLayer( iRef.mLayer )
{
    BuildData();
}


// --------------------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------ Interface Overrides
// --------------------------------------------------------------------------------------------------------------


Qt::ItemFlags
cLayerModel::flags( const QModelIndex & iIndex ) const
{
    if( !iIndex.isValid() )
        return 0;

    if( iIndex.column() == 0 )
        return  QAbstractItemModel::flags( iIndex );

    return  Qt::ItemIsEditable | QAbstractItemModel::flags( iIndex );
}


void
cLayerModel::BuildData()
{
    if( mRootItem )
        return;

    mRootItem = new cTreeWrapperNode( 0 );
    mRootItem->AppendData( "Name" );
    mRootItem->AppendData( "Value" );

    if( !mLayer )
        return;

    cTreeWrapperNodeLayer* name   = new cTreeWrapperNodeLayer( mRootItem, mLayer );
    name->AppendData( "Layer Name" );
    cTreeWrapperNodeLayer* zDepthNode   = new cTreeWrapperNodeLayer( mRootItem, mLayer );
    zDepthNode->AppendData( "ZDepth" );
    cTreeWrapperNodeLayer* fixedNode    = new cTreeWrapperNodeLayer( mRootItem, mLayer );
    fixedNode->AppendData( "Fixed" );
}

} //nQt
} //nModels
