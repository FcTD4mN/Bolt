#include "Editor.Widgets.ColorSwatch.h"


cColorSwatch::~cColorSwatch()
{
}


cColorSwatch::cColorSwatch( QWidget* iParent ) :
    QLabel( iParent )
{
    setFixedHeight( 16 );
}


//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------- Events overrides
//--------------------------------------------------------------------------------------


void
cColorSwatch::mouseReleaseEvent( QMouseEvent * iEvent )
{
    emit  swatchClicked();
    QLabel::mouseReleaseEvent( iEvent );
}


//--------------------------------------------------------------------------------------
//------------------------------------------------------------------------------ Set/Get
//--------------------------------------------------------------------------------------


void
cColorSwatch::Color( const QColor & iColor )
{
    mColor = iColor;
    QPixmap px( size() );
    px.fill( iColor );
    setPixmap( px );
}


const QColor&
cColorSwatch::Color() const
{
    return  mColor;
}

