#include "Editor.Models.DrawingToolModelBase.h"


namespace  nQt {
namespace  nModels {


cDrawingToolModelBase::~cDrawingToolModelBase()
{
}


cDrawingToolModelBase::cDrawingToolModelBase( QObject * iParent ) :
    tSuperClass( iParent )
{
}


QPixmap*
cDrawingToolModelBase::CreateHUDPixmap( float iScale )
{
    return  nullptr;
}


QPainter*
cDrawingToolModelBase::CreateNewPainter( QPaintDevice * iPaintDevice )
{
    return  nullptr;
}


void
cDrawingToolModelBase::OpenToolDialogAtPosition( const QPointF& iPosition, QWidget* iParent )
{
    // Nothing
}


} //nQt
} //nModels

