#include "Editor.Widgets.ColorPicker.h"


#include <QPaintEvent>
#include <QPainter>

#define SELCOLORSIZE 20


cColorPicker::~cColorPicker()
{
    delete  mPixmap;
    delete  mImage;
    delete  mSelectedColorCircle;
}


cColorPicker::cColorPicker( QWidget *parent ) :
    tSuperClass( parent )
{
    mPixmap = new QPixmap( width(), height() );
    mImage = new QImage( width(), height(), QImage::Format_ARGB32_Premultiplied );

    mSelectedColorCircle = new QPixmap( SELCOLORSIZE, SELCOLORSIZE );
    mSelectedColorCirclePos = QPoint( 0, 0 );
    mLight = 0.5F;

    _DrawWheel();
    _DrawSelectedColorCircle();
}


//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------- Events overrides
//--------------------------------------------------------------------------------------


void
cColorPicker::paintEvent( QPaintEvent * event )
{
    QPainter painter( this );
    painter.drawPixmap( 0, 0, *mPixmap );
    painter.drawPixmap( mSelectedColorCirclePos, *mSelectedColorCircle );
}


void
cColorPicker::mousePressEvent( QMouseEvent * event )
{
    mSelectedColorCirclePos = event->pos() - QPoint( SELCOLORSIZE/2, SELCOLORSIZE/2 );
    mSelectedColor = mImage->pixel( event->pos() );
    _DrawSelectedColorCircle();
    update();
}


void
cColorPicker::mouseMoveEvent( QMouseEvent * event )
{
    mSelectedColorCirclePos = event->pos() - QPoint( SELCOLORSIZE/2, SELCOLORSIZE/2 );
    mSelectedColor = mImage->pixel( event->pos() );
    _DrawSelectedColorCircle();
    update();
}


void
cColorPicker::mouseReleaseEvent( QMouseEvent * event )
{
    mSelectedColor = mImage->pixel( event->pos() );
    emit  colorPicked( mSelectedColor );
}


void
cColorPicker::resizeEvent( QResizeEvent * event )
{
    delete  mPixmap;
    delete  mImage;
    mPixmap = new QPixmap( width(), height() );
    mImage = new QImage( width(), height(), QImage::Format_ARGB32_Premultiplied );
    _DrawWheel();
}


//--------------------------------------------------------------------------------------
//------------------------------------------------------------------------------ Set/Get
//--------------------------------------------------------------------------------------


void
cColorPicker::Light( float light )
{
    mLight = light;

    _DrawWheel();
    qreal h, s, l;
    mSelectedColor.getHslF( &h, &s, &l );

    mSelectedColor.setHslF( h, s, mLight );
    _DrawSelectedColorCircle();
    update();

    emit  colorPicked( mSelectedColor );
}


float
cColorPicker::Light() const
{
    return  mLight;
}


void
cColorPicker::Color( const QColor & color )
{
    mSelectedColor = color;

    qreal h, s, l;
    mSelectedColor.getHslF( &h, &s, &l );
    mLight = l;

    _DrawWheel();
    _DrawSelectedColorCircle();
    update();
}


//--------------------------------------------------------------------------------------
//-------------------------------------------------------------------------- __PRIVATE__
//--------------------------------------------------------------------------------------


void
cColorPicker::_DrawWheel()
{
    mPixmap->fill( Qt::transparent );

    QPainter painter( mPixmap );

    QConicalGradient outterWheel( width() / 2, height() / 2, 0 );
    outterWheel.setColorAt( 0, QColor::fromHslF( 0 / 360.0, 1.0, mLight, 1.0 ) );
    outterWheel.setColorAt( 60.F / 360.F, QColor::fromHslF( 60.F / 360.0, 1.0, mLight, 1.0 ) );
    outterWheel.setColorAt( 120.F / 360.F, QColor::fromHslF( 120.F / 360.0, 1.0, mLight, 1.0 ) );
    outterWheel.setColorAt( 180.F / 360.F, QColor::fromHslF( 180.F / 360.0, 1.0, mLight, 1.0 ) );
    outterWheel.setColorAt( 240.F / 360.F, QColor::fromHslF( 240.F / 360.0, 1.0, mLight, 1.0 ) );
    outterWheel.setColorAt( 300.F / 360.F, QColor::fromHslF( 300.F / 360.0, 1.0, mLight, 1.0 ) );
    outterWheel.setColorAt( 1, QColor::fromHslF( 360.F / 360.0, 1.0, mLight, 1.0 ) );
    painter.setBrush( outterWheel );

    painter.drawEllipse( 0, 0, width(), height() );

    *mImage = mPixmap->toImage();
}


void
cColorPicker::_DrawSelectedColorCircle()
{
    mSelectedColorCircle->fill( Qt::transparent );

    QPainter painter( mSelectedColorCircle );
    painter.setPen( Qt::black );
    painter.setBrush( mSelectedColor );

    painter.drawEllipse( 0, 0, SELCOLORSIZE - 1, SELCOLORSIZE - 1 ); // -1 otherwise ellipse goes out of picture
}


