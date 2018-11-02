#include "Editor.Models.EraserToolModel.h"

#include "Editor.Models.DataWrapperEraserTool.h"


namespace  nQt {
namespace  nModels {



cEraserToolModel::~cEraserToolModel()
{
    delete  mEraserTool;
}


cEraserToolModel::cEraserToolModel( QObject * iParent ) :
    tSuperClass( iParent )
{
    mEraserTool = new ::nQt::nDrawingTools::cEraserTool();
    BuildData();
}


// --------------------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------- AbstractModel overrides
// --------------------------------------------------------------------------------------------------------------


Qt::ItemFlags
cEraserToolModel::flags( const QModelIndex & iIndex ) const
{
    if( iIndex.column() == 1 )
        return  tSuperClass::flags( iIndex ) | Qt::ItemIsEditable;

    return  tSuperClass::flags( iIndex );
}


bool
cEraserToolModel::setData( const QModelIndex & index, const QVariant & value, int role )
{
    bool result = tSuperClass::setData( index, value, role );

    if( index.row() == kToolSize )
        emit  hudInvalidated();

    return  result;
}


// --------------------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------- DrawingToolModeBase overrides
// --------------------------------------------------------------------------------------------------------------



QPixmap*
cEraserToolModel::CreateHUDPixmap( float iScale )
{
    return  mEraserTool->CreateHUDPixmap( iScale );
}


QPainter*
cEraserToolModel::CreateNewPainter( QPaintDevice* iPaintDevice )
{
    return  mEraserTool ->CreateNewPainter( iPaintDevice );
}


// --------------------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------------ Set/Get
// --------------------------------------------------------------------------------------------------------------


int
cEraserToolModel::Size() const
{
    return  data( index( kToolSize, 1 ), Qt::DisplayRole ).toInt();
}


void
cEraserToolModel::Size( int iSize )
{
    setData( index( kToolSize, 1 ), iSize );
}


bool
cEraserToolModel::AntiAliasing() const
{
    return  data( index( kAntiAliasing, 1 ), Qt::DisplayRole ).toBool();
}


void
cEraserToolModel::AntiAliasing( bool iAA )
{
    setData( index( kAntiAliasing, 1 ), iAA );
}


void
cEraserToolModel::BuildData()
{
    mRootItem = new ::nQt::nModels::cTreeWrapperNode( 0 );
    mRootItem->AppendData( "Property" );
    mRootItem->AppendData( "Value" );

    new ::nQt::nModels::cDataWrapperEraserToolSize( mRootItem, mEraserTool );
    new ::nQt::nModels::cDataWrapperEraserToolAntiAliasing( mRootItem, mEraserTool );
}


} //nQt
} //nModels

