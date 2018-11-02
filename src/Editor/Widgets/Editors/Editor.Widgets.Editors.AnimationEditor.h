#pragma once

#include "ui_AnimationEditor.h"

#include <QDataWidgetMapper>
#include <QModelIndex>
#include <QTimer>
#include <QWidget>

namespace  nQt::nModels      { class cAnimationsModel; }
namespace  nQt::nModels      { class cDrawingToolModelBase; }
namespace  nCore::nAnimation { class cAnimation; }

class cAnimationEditor :
    public QWidget
{
    Q_OBJECT

public:
    typedef QWidget tSuperClass;

public:
    ~cAnimationEditor();
    cAnimationEditor( QWidget *parent = Q_NULLPTR );

public  slots:
    void  ShowAnimation( ::nQt::nModels::cAnimationsModel* iAnimationsModel, const QModelIndex& iRoot );

    // Timeline communication
    void  CurrentFrameChanged();
    void  NumberOfFramesChanged();
    void  SpinCurrentFrameChanged();

    // Animation controllers
    void  TimerTick();
    void  PlayAnimation();
    void  StopAnimation();
    void  GoPreviousFrame();
    void  GoNextFrame();

    // These slots are there to allow an instant submit of datachange when using these widgets
    void  CheckBoxStateChanged( bool iState );
    void  SpinBoxValueChanged( double iNewValue );

    void  AnimationChanged( const QModelIndex& iTopLeft, const QModelIndex& iBottomRight, const QVector< int >& iRoles );

    // Tools
    void  LoadPencilTool();
    void  LoadEraserTool();

signals:
    void  saveAnimation();
    void  currentFrameSizeChanged( const QSize& iSize );

private:
    // __PRIVATE__
    void  _UpdateFlipInCanvas();

private:
    Ui::AnimationEditor ui;

    ::nQt::nModels::cAnimationsModel*       mAnimationsModel;
    QModelIndex                             mRootAnimation;
    ::nCore::nAnimation::cAnimation*        mCurrentAnimation;
    QTimer*                                 mAnimationTimer;
    bool                                    mAnimationIsPlaying;

    QDataWidgetMapper*                      mMapper;

    QVector< ::nQt::nModels::cDrawingToolModelBase* > mDrawingToolModels;      // Origin // TODO: replace with model in models
};

