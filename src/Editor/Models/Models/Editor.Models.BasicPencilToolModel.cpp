#include "Editor.Models.BasicPencilToolModel.h"

#include "Editor.Delegates.BasicPencilTool.h"
#include "Editor.Models.DataWrapperPencilTool.h"
#include "Editor.Widgets.DialogBasicPencilTool.h"


namespace  nQt {
namespace  nModels {



cBasicPencilToolModel::~cBasicPencilToolModel()
{
    delete  mPencilTool;
}


cBasicPencilToolModel::cBasicPencilToolModel( QObject * iParent ) :
    tSuperClass( iParent )
{
    mPencilTool = new ::nQt::nDrawingTools::cPencilTool();
    BuildData();
}


// --------------------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------- AbstractModel overrides
// --------------------------------------------------------------------------------------------------------------


Qt::ItemFlags
cBasicPencilToolModel::flags( const QModelIndex & iIndex ) const
{
    if( iIndex.column() == 1 )
        return  tSuperClass::flags( iIndex ) | Qt::ItemIsEditable;

    return  tSuperClass::flags( iIndex );
}


bool
cBasicPencilToolModel::setData( const QModelIndex & index, const QVariant & value, int role )
{
    bool result = tSuperClass::setData( index, value, role );

    if( index.row() == kToolSize )
        emit  hudInvalidated();

    return  result;
}


QStyledItemDelegate*
cBasicPencilToolModel::CreateModelDelegate()
{
    auto delegate = new  cBasicPencilToolDelegate();
    delegate->BasicPencilToolModel( this );

    return  delegate;
}


// --------------------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------- DrawingToolModeBase overrides
// --------------------------------------------------------------------------------------------------------------



QPixmap*
cBasicPencilToolModel::CreateHUDPixmap( float iScale )
{
    return  mPencilTool->CreateHUDPixmap( iScale );
}


QPainter*
cBasicPencilToolModel::CreateNewPainter( QPaintDevice* iPaintDevice )
{
    return  mPencilTool->CreateNewPainter( iPaintDevice );
}


void
cBasicPencilToolModel::OpenToolDialogAtPosition( const QPointF& iPosition, QWidget* iParent )
{
    // Tool Dialogs have the setAttribute( Qt::WA_DeleteOnClose ) thing, which means we don't have to manually do the delete
    auto dialog = new cDialogBasicPencilTool( this, iParent );
    dialog->OpenAtPosition( iPosition - QPointF( dialog->Size().width() / 2, dialog->Size().height() / 2 ) );
}


// --------------------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------------ Set/Get
// --------------------------------------------------------------------------------------------------------------


QColor
cBasicPencilToolModel::Color() const
{
    QVariant dataColor = data( index( kColor, 1 ), Qt::DisplayRole );
    return  dataColor.value< QColor >();
}


void
cBasicPencilToolModel::Color( const QColor & iColor )
{
    setData( index( kColor, 1 ), iColor );
}


int
cBasicPencilToolModel::Size() const
{
    return  data( index( kToolSize, 1 ), Qt::DisplayRole ).toInt();
}


void
cBasicPencilToolModel::Size( int iSize )
{
    setData( index( kToolSize, 1 ), iSize );
}


bool
cBasicPencilToolModel::AntiAliasing() const
{
    return  data( index( kAntiAliasing, 1 ), Qt::DisplayRole ).toBool();
}


void
cBasicPencilToolModel::AntiAliasing( bool iAA )
{
    setData( index( kAntiAliasing, 1 ), iAA );
}


void
cBasicPencilToolModel::BuildData()
{
    mRootItem = new ::nQt::nModels::cTreeWrapperNode( 0 );
    mRootItem->AppendData( "Property" );
    mRootItem->AppendData( "Value" );

    new ::nQt::nModels::cDataWrapperPencilToolSize( mRootItem, mPencilTool );
    new ::nQt::nModels::cDataWrapperPencilToolAntiAliasing( mRootItem, mPencilTool );
    new ::nQt::nModels::cDataWrapperPencilToolColor( mRootItem, mPencilTool );
}


} //nQt
} //nModels

