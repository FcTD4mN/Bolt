#include "Editor.DrawingTools.EraserTool.h"


namespace  nQt::nDrawingTools {


cEraserTool::~cEraserTool()
{
}


cEraserTool::cEraserTool()
{
    mToolSize = 5;
    mAntiAliasingOn = true;

    mBrush = new QBrush();
    mBrush->setStyle( Qt::SolidPattern );
    mBrush->setColor( Qt::black );

    mPen = new QPen();
    mPen->setWidth( mToolSize );
    mPen->setBrush( *mBrush );
    mPen->setCapStyle( Qt::RoundCap );
    mPen->setJoinStyle( Qt::RoundJoin );
}


// --------------------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------- Interface methods
// --------------------------------------------------------------------------------------------------------------


QPixmap*
cEraserTool::CreateHUDPixmap( float iScale )
{
    int finalSize = mToolSize * iScale;
    QPixmap* brushHUD = new QPixmap( finalSize, finalSize );
    brushHUD->fill( Qt::transparent );

    QPainter painter( brushHUD );
    painter.setBrush( Qt::transparent );
    painter.setPen( Qt::lightGray );

    if( mToolSize == 1 )
        painter.drawPoint( 0, 0 );
    else
        painter.drawEllipse( 0, 0, finalSize - 1, finalSize - 1 );

    return brushHUD;
}


QPainter*
cEraserTool::CreateNewPainter( QPaintDevice * iPaintDevice )
{
    if( !iPaintDevice )
        return  0;

    QPainter* painter = new QPainter( iPaintDevice );

    if( mAntiAliasingOn )
        painter->setRenderHint( QPainter::Antialiasing );

    painter->setPen( *mPen );
    painter->setCompositionMode( QPainter::CompositionMode_DestinationOut );

    return  painter;
}


// --------------------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------------ Set/Get
// --------------------------------------------------------------------------------------------------------------


int
cEraserTool::Size() const
{
    return  mToolSize;
}


void
cEraserTool::Size( int iSize )
{
    mToolSize = iSize;
    mPen->setWidth( mToolSize );
}


bool
cEraserTool::AntiAliasing() const
{
    return  mAntiAliasingOn;
}


void
cEraserTool::AntiAliasing( bool iAA )
{
    mAntiAliasingOn = iAA;
}


QPen*
cEraserTool::Pen()
{
    return  mPen;
}


QBrush*
cEraserTool::Brush()
{
    return  mBrush;
}


} // namespace  nQt::nDrawingTools

