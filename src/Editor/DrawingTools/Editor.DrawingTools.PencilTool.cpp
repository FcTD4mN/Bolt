#include "Editor.DrawingTools.PencilTool.h"


namespace  nQt::nDrawingTools {


cPencilTool::~cPencilTool()
{
}


cPencilTool::cPencilTool()
{
    mToolSize = 5;
    mAntiAliasingOn = true;

    mBrush = new QBrush();
    mBrush->setStyle( Qt::SolidPattern );
    mBrush->setColor( mColor );

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
cPencilTool::CreateHUDPixmap( float iScale )
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
cPencilTool::CreateNewPainter( QPaintDevice * iPaintDevice )
{
    if( !iPaintDevice )
        return  0;

    QPainter* painter = new QPainter( iPaintDevice );

    if( mAntiAliasingOn )
        painter->setRenderHint( QPainter::Antialiasing );

    painter->setPen( *mPen );

    return  painter;
}


// --------------------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------------ Set/Get
// --------------------------------------------------------------------------------------------------------------


QColor
cPencilTool::Color() const
{
    return  mColor;
}


void
cPencilTool::Color( const QColor & iColor )
{
    mColor = iColor;
    mPen->setColor( mColor );
    mBrush->setColor( mColor );
}


int
cPencilTool::Size() const
{
    return  mToolSize;
}


void
cPencilTool::Size( int iSize )
{
    mToolSize = iSize;
    mPen->setWidth( mToolSize );
}


bool
cPencilTool::AntiAliasing() const
{
    return  mAntiAliasingOn;
}


void
cPencilTool::AntiAliasing( bool iAA )
{
    mAntiAliasingOn = iAA;
}


QPen*
cPencilTool::Pen()
{
    return  mPen;
}


QBrush*
cPencilTool::Brush()
{
    return  mBrush;
}


} // namespace  nQt::nDrawingTools

