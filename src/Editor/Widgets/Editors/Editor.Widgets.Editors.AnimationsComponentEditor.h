#pragma once

#include "ui_ProjectEditor.h"

#include <QListView>
#include <QPushButton>
#include <QSplitter>
#include <QWidget>

namespace  nCore::nECS::nComponent  { class cAnimations; }
namespace  nCore::nECS::nCore       { class cEntity; }
namespace  nQt::nModels             { class cAnimationsModel; }

class  cAnimationEditor;

class cAnimationsComponentEditor :
    public QWidget
{
    Q_OBJECT

public:
    typedef QWidget tSuperClass;

public:
    ~cAnimationsComponentEditor();
    cAnimationsComponentEditor( QWidget *parent = Q_NULLPTR );

public  slots:
    void  ShowAnimationsComponentFromEntity( ::nCore::nECS::nCore::cEntity* iEntity );
    void  AddAnimation();
    void  RemoveAnimation();
    void  AnimationSelected( const QModelIndex& iCurrent, const QModelIndex& iPrevious );

signals:
    void  saveAnimation();

private:
    ::nQt::nModels::cAnimationsModel*       mAnimationsModel;  // Origin

    // WIDGETS AND STUFF
    QHBoxLayout*        mMainHLayout;
    QSplitter*          mSplitter;

    // LEFT
    QWidget*            mLeftWidget;
    QListView*          mAllAnimationsList;
    QVBoxLayout*        mLeftVLayout;
    QHBoxLayout*        mButtonHLayout;
    QPushButton*        mAddButton;
    QPushButton*        mRemoveButton;

    // RIGHT
    QWidget*            mRightWidget;
    QVBoxLayout*        mRightVLayout;
    cAnimationEditor*   mAnimationEditor;
};

