#include "Editor.Widgets.Editors.AnimationEditor.h"

#include "Core.Animation.Animation.h"

#include "Editor.Models.AnimationsModel.h"
#include "Editor.Models.BasicPencilToolModel.h"
#include "Editor.Models.EraserToolModel.h"
#include "Editor.Models.TreeWrapper.h"
#include "Editor.Widgets.Animation.ImageItem.h"
#include "Editor.Widgets.Animation.Canvas.h"


#include <QSpinBox>


cAnimationEditor::~cAnimationEditor()
{
    delete  mAnimationTimer;
    delete  mMapper;

    for( auto tool : mDrawingToolModels )
        delete  tool;

    mDrawingToolModels.clear();
}


cAnimationEditor::cAnimationEditor( QWidget * Parent ) :
    tSuperClass( Parent ),
    mAnimationTimer( 0 ),
    mAnimationIsPlaying( false )
{
    ui.setupUi( this );

    // Mapper
    mMapper = new QDataWidgetMapper( this );
    mMapper->setOrientation( Qt::Vertical );

    //Canvas
    connect( ui.canvas, &cCanvas::currentFrameGotPainted,   ui.animationTimeline,   &cAnimationTimeline::CurrentFrameGotPainted );

    // Drawing tool
    mDrawingToolModels.push_back( new ::nQt::nModels::cBasicPencilToolModel() );
    mDrawingToolModels.push_back( new ::nQt::nModels::cEraserToolModel() );
    ui.canvas->DrawingToolModel( mDrawingToolModels[ 0 ] );
    ui.drawingToolEditor->ShowTool( mDrawingToolModels[ 0 ] );

    // Timeline
    connect( ui.animationTimeline,  &cAnimationTimeline::currentFrameChanged,   this,                   &cAnimationEditor::CurrentFrameChanged );
    connect( ui.animationTimeline,  &cAnimationTimeline::numberOfFrameChanged,  this,                   &cAnimationEditor::NumberOfFramesChanged );
    connect( ui.animationTimeline,  &cAnimationTimeline::askPlayAnimation,      this,                   &cAnimationEditor::PlayAnimation );
    connect( this,                  &cAnimationEditor::saveAnimation,           ui.animationTimeline,   &cAnimationTimeline::SaveAnimationToFiles );
    connect( this,                  &cAnimationEditor::currentFrameSizeChanged, ui.animationTimeline,   &cAnimationTimeline::CurrentFrameSizeChanged );

    // UI Elements
    connect( ui.buttonPlay,         &QPushButton::clicked,      this, &cAnimationEditor::PlayAnimation );
    connect( ui.buttonStop,         &QPushButton::clicked,      this, &cAnimationEditor::StopAnimation );
    connect( ui.buttonPrevious,     &QPushButton::clicked,      this, &cAnimationEditor::GoPreviousFrame );
    connect( ui.buttonNext,         &QPushButton::clicked,      this, &cAnimationEditor::GoNextFrame );
    connect( ui.spinSizeWidth,      SIGNAL(editingFinished()),  this, SLOT(SpinCurrentFrameChanged()) );
    connect( ui.spinSizeHeight,     SIGNAL(editingFinished()),  this, SLOT(SpinCurrentFrameChanged()) );

    // DataMapper has a loseFocus submit policy, meaning it'll submit data only when widget loses focus, which is weird for checkboxes
    // and annoying when playing arount with framerate
    // So here force submit as soon as widgets are modified
    connect( ui.flippedCheckBox,    &QCheckBox::stateChanged, this, &cAnimationEditor::CheckBoxStateChanged );
    connect( ui.pausedCheckBox,     &QCheckBox::stateChanged, this, &cAnimationEditor::CheckBoxStateChanged );
    connect( ui.playOnceCheckBox,   &QCheckBox::stateChanged, this, &cAnimationEditor::CheckBoxStateChanged );
    connect( ui.framerateDoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT( SpinBoxValueChanged(double)) );

    // Tools connection
    connect( ui.toolPencil, &QToolButton::clicked, this, &cAnimationEditor::LoadPencilTool );
    connect( ui.toolEraser, &QToolButton::clicked, this, &cAnimationEditor::LoadEraserTool );
}


void
cAnimationEditor::ShowAnimation( ::nQt::nModels::cAnimationsModel* iAnimationsModel, const QModelIndex& iRoot )
{
    mAnimationsModel = iAnimationsModel;
    mRootAnimation = iRoot;

    delete  mAnimationTimer;
    mAnimationTimer = 0;

    if( mAnimationsModel )
    {
        mCurrentAnimation = mAnimationsModel->AnimationAtIndex( iRoot );
        mAnimationTimer = new QTimer();
        mAnimationTimer->start( 1000 / mCurrentAnimation->FrameRate() );

        mMapper->setModel( mAnimationsModel );
        mMapper->setRootIndex( iRoot );
        mMapper->addMapping( ui.animationNameLineEdit, 0 );
        mMapper->addMapping( ui.framerateDoubleSpinBox, 1 );
        mMapper->addMapping( ui.flippedCheckBox, 2 );
        mMapper->addMapping( ui.pausedCheckBox, 3 );
        mMapper->addMapping( ui.playOnceCheckBox, 4 );
        mMapper->addMapping( ui.numberOfFramesSpinBox, 5 );

        mMapper->toFirst();

        ui.canvas->ClearPixmap();

        ui.animationTimeline->SetupAnimation( mCurrentAnimation );
    }
    else
    {
        ui.animationTimeline->SetupAnimation( 0 );
        ui.canvas->ClearPixmap();
    }

    connect( mAnimationsModel, &QAbstractItemModel::dataChanged, this, &cAnimationEditor::AnimationChanged );
}



void
cAnimationEditor::CurrentFrameChanged()
{
    if( ui.animationTimeline->AnimationImages().size() == 0 )
    {
        ui.canvas->ClearPixmap();
    }
    else
    {
        _UpdateFlipInCanvas();
        auto currentItemPixmap = ui.animationTimeline->CurrentPixmap();
        ui.spinSizeWidth->setValue( currentItemPixmap.width() );
        ui.spinSizeHeight->setValue( currentItemPixmap.height() );
    }
}


void
cAnimationEditor::NumberOfFramesChanged()
{
    QModelIndex numberOfFrameIndex = mAnimationsModel->index( 5, 0, mRootAnimation );
    mAnimationsModel->dataChanged( numberOfFrameIndex , numberOfFrameIndex );
}


void
cAnimationEditor::SpinCurrentFrameChanged()
{

    emit currentFrameSizeChanged( QSize( ui.spinSizeWidth->value(), ui.spinSizeHeight->value() ) );
}


void
cAnimationEditor::TimerTick()
{
    ui.animationTimeline->GoToNextFrame();
}


void
cAnimationEditor::PlayAnimation()
{
    if( !mAnimationTimer )
        return;

    if( !mAnimationIsPlaying )
    {
        mAnimationIsPlaying = true;
        connect( mAnimationTimer, &QTimer::timeout, this, &cAnimationEditor::TimerTick );
        ui.buttonPlay->setText( "||" );
        mAnimationTimer->start();
    }
    else
    {
        mAnimationIsPlaying = false;
        disconnect( mAnimationTimer, &QTimer::timeout, this, &cAnimationEditor::TimerTick );
        ui.buttonPlay->setText( ">" );
        mAnimationTimer->stop();
    }
}


void
cAnimationEditor::StopAnimation()
{
    if( !mAnimationTimer )
        return;

    mAnimationIsPlaying = false;
    disconnect( mAnimationTimer, &QTimer::timeout, this, &cAnimationEditor::TimerTick );
    ui.buttonPlay->setText( ">" );
    mAnimationTimer->stop();
    ui.animationTimeline->GoToFrame( 0 );
}


void
cAnimationEditor::GoPreviousFrame()
{
    if( !mAnimationIsPlaying )
        ui.animationTimeline->GoToPreviousFrame();
}


void
cAnimationEditor::GoNextFrame()
{
    if( !mAnimationIsPlaying )
        ui.animationTimeline->GoToNextFrame();
}


void
cAnimationEditor::CheckBoxStateChanged( bool iState )
{
    mMapper->submit();
}


void
cAnimationEditor::SpinBoxValueChanged( double iNewValue )
{
    mMapper->submit();
}


void
cAnimationEditor::AnimationChanged( const QModelIndex & iTopLeft, const QModelIndex & iBottomRight, const QVector<int>& iRoles )
{
    auto item = mAnimationsModel->ExtractTreeWrapper( iTopLeft );
    if( item->Type() == "AnimationFrameRate" )
    {
        mAnimationTimer->stop();
        mAnimationTimer->start( 1000 / mAnimationsModel->FrameRate() );
    }
    else if( item->Type() == "AnimationFlipped" )
    {
        _UpdateFlipInCanvas();
    }
}


void
cAnimationEditor::LoadPencilTool()
{
    ui.canvas->DrawingToolModel( mDrawingToolModels[ 0 ] );
    ui.drawingToolEditor->ShowTool( mDrawingToolModels[ 0 ] );
    ui.toolEraser->setChecked( false );
    ui.toolPencil->setChecked( true );
}


void
cAnimationEditor::LoadEraserTool()
{
    ui.canvas->DrawingToolModel( mDrawingToolModels[ 1 ] );
    ui.drawingToolEditor->ShowTool( mDrawingToolModels[ 1 ] );
    ui.toolPencil->setChecked( false );
    ui.toolEraser->setChecked( true );
}


// --------------------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------- __PRIVATE__
// --------------------------------------------------------------------------------------------------------------


void
cAnimationEditor::_UpdateFlipInCanvas()
{
    QPixmap pix = ui.animationTimeline->CurrentPixmap();
    if( mCurrentAnimation->Flipped() )
    {
        QTransform flipper;
        flipper.scale( -1, 1 );
        pix = pix.transformed( flipper );
    }

    ui.canvas->Pixmap( pix );
}

