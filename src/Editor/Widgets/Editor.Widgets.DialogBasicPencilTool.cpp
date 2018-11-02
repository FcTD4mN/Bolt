#include "Editor.Widgets.DialogBasicPencilTool.h"


#include <QEvent>
#include <QSpinBox>



// TODO, do a non linear slider gadget
static
float
Smooth( float value, float max )
{
    return  max * std::powf( value / max, 4.0 );
}

static
float
SmoothInverse( float value, float max )
{
    return  max * std::powf( value / max, 1.0 / 4.0 );
}


cDialogBasicPencilTool::~cDialogBasicPencilTool()
{
}


cDialogBasicPencilTool::cDialogBasicPencilTool( ::nQt::nModels::cBasicPencilToolModel* iModel, QWidget* iParent ) :
    tSuperClass( iParent ),
    mToolModel( iModel ),
    mCloseOnRelease( true )
{
    ui.setupUi( this );
    setWindowFlags( Qt::Popup );
    setAttribute( Qt::WA_DeleteOnClose );

    ui.sliderSize->setValue( int( SmoothInverse( mToolModel->Size(), 5000 ) ) );
    ui.colorPicker->installEventFilter( this );

    qreal h, s, l;
    mToolModel->Color().getHslF( &h, &s, &l );
    ui.sliderLight->setValue( l * 100 );
    ui.spinLight->setValue( l * 100 );

    mMapper = new QDataWidgetMapper( this );
    mMapper->setOrientation( Qt::Vertical );
    mMapper->setModel( mToolModel );
    mMapper->addMapping( ui.spinSize, 0 );
    mMapper->setCurrentIndex( 1 );


    connect( ui.sliderSize, &QSlider::valueChanged, this, &cDialogBasicPencilTool::SliderSizeChanged );

    connect( ui.sliderLight,    &QSlider::valueChanged, this, &cDialogBasicPencilTool::LuminosityChanged );
    connect( ui.sliderLight,    &QSlider::valueChanged, ui.spinLight, &QSpinBox::setValue );
    connect( ui.spinLight,      SIGNAL(valueChanged(int)), ui.sliderLight, SLOT( setValue(int)) );
    connect( ui.spinLight,      SIGNAL(valueChanged(int)), this, SLOT( LuminosityChanged(int)) );

    connect( ui.colorPicker, &cColorPicker::colorPicked, this, &cDialogBasicPencilTool::ColorPicked );
}


bool
cDialogBasicPencilTool::eventFilter( QObject * iObject, QEvent * iEvent )
{
    if( iObject == ui.colorPicker )
    {
        if( iEvent->type() == QEvent::MouseButtonRelease )
        {
            if( mTimer.isActive() )
            {
                mCloseOnRelease = false;
                return  true;
            }

        }
    }

    return  tSuperClass::eventFilter( iObject, iEvent );
}


//--------------------------------------------------------------------------------------
//------------------------------------------------------------------------------ Set/Get
//--------------------------------------------------------------------------------------


QSize
cDialogBasicPencilTool::Size() const
{
    return QSize( 200, 200 );
}


//--------------------------------------------------------------------------------------
//---------------------------------------------------------------------- Dialog controls
//--------------------------------------------------------------------------------------


void
cDialogBasicPencilTool::OpenAtPosition( QPointF iPos )
{
    setGeometry( iPos.x(), iPos.y(), 200, 200 );
    ui.colorPicker->Color( mToolModel->Color() );
    qreal h, s, l;
    mToolModel->Color().getHslF( &h, &s, &l );
    ui.sliderLight->setValue( l * 100 );
    show();
    mTimer.start( 200 );
    mTimer.setSingleShot( true );
}


//--------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------- Slots
//--------------------------------------------------------------------------------------


void
cDialogBasicPencilTool::SliderSizeChanged( int iValue )
{
    int value = int( Smooth( iValue, 5000 ) );
    if( value == 0 )
        value = 1;
    mToolModel->Size( value );
}


void
cDialogBasicPencilTool::LuminosityChanged( int iValue )
{
    ui.colorPicker->Light( float(iValue) / 100 );
}


void
cDialogBasicPencilTool::ColorPicked( const QColor & color )
{
    mToolModel->Color( color );

    if( mCloseOnRelease )
        close();
}


