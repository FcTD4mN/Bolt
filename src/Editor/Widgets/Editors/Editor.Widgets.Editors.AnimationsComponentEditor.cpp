#include "Editor.Widgets.Editors.AnimationsComponentEditor.h"


#include "Core.ECS.Component.Animations.h"
#include "Core.ECS.Core.Entity.h"

#include "Editor.Widgets.Editors.AnimationEditor.h"
#include "Editor.Models.AnimationsModel.h"


cAnimationsComponentEditor::~cAnimationsComponentEditor()
{
    delete  mMainHLayout;
    delete  mSplitter;
    delete  mLeftWidget;
    delete  mAllAnimationsList;
    delete  mLeftVLayout;
    delete  mButtonHLayout;
    delete  mAddButton;
    delete  mRemoveButton;
    delete  mRightWidget;
    delete  mRightVLayout;
    delete  mAnimationEditor;
}


cAnimationsComponentEditor::cAnimationsComponentEditor( QWidget * Parent ) :
    tSuperClass( Parent ),
    mAnimationsModel( 0 )
{
    // Creating widgets
    mMainHLayout = new QHBoxLayout( this );
    setLayout( mMainHLayout );

        // LEFT
    mSplitter = new QSplitter( this );
    mSplitter->setOrientation( Qt::Horizontal );
    mMainHLayout->addWidget( mSplitter );

    mLeftWidget = new QWidget( this );
    mLeftVLayout = new QVBoxLayout( this );
    mButtonHLayout = new QHBoxLayout( this );
    mLeftWidget->setFixedWidth( 170 );

    mAllAnimationsList = new QListView( this );
    mLeftVLayout->addWidget( mAllAnimationsList );
    mLeftWidget->setLayout( mLeftVLayout );

    mAddButton = new QPushButton( this );
    mAddButton->setText( "+" );
    mRemoveButton = new QPushButton( this );
    mRemoveButton->setText( "x" );
    mButtonHLayout->addWidget( mAddButton );
    mButtonHLayout->addWidget( mRemoveButton );

    mLeftVLayout->addLayout( mButtonHLayout );

    mSplitter->addWidget( mLeftWidget );

    // RIGHT
    mRightWidget = new QWidget( this );
    mRightVLayout = new QVBoxLayout( this );
    mAnimationEditor = new cAnimationEditor( this );
    mRightVLayout->addWidget( mAnimationEditor );
    mRightWidget->setLayout( mRightVLayout );

    mSplitter->addWidget( mRightWidget );


    // Geometry management
    auto  geom = mAllAnimationsList->geometry();
    geom.setWidth( 100 );
    mAllAnimationsList->setGeometry( geom );

    // CONNEXIONS
    connect( mAddButton, &QPushButton::clicked, this, &cAnimationsComponentEditor::AddAnimation );
    connect( mRemoveButton, &QPushButton::clicked, this, &cAnimationsComponentEditor::RemoveAnimation );
    connect( this, &cAnimationsComponentEditor::saveAnimation, mAnimationEditor, &cAnimationEditor::saveAnimation );
}


void
cAnimationsComponentEditor::AddAnimation()
{
    if( mAnimationsModel )
        mAnimationsModel->AddAnimation( mAllAnimationsList->currentIndex() );
}


void
cAnimationsComponentEditor::RemoveAnimation()
{
    if( mAnimationsModel )
        mAnimationsModel->RemoveAnimation( mAllAnimationsList->currentIndex() );
}


void
cAnimationsComponentEditor::AnimationSelected( const QModelIndex & iCurrent, const QModelIndex & iPrevious )
{
    mAnimationEditor->ShowAnimation( mAnimationsModel, iCurrent );
}


void
cAnimationsComponentEditor::ShowAnimationsComponentFromEntity( ::nCore::nECS::nCore::cEntity* iEntity )
{
    auto animations = iEntity->GetComponentByNameAs< ::nCore::nECS::nComponent::cAnimations* >( "animations" );
    if( animations )
    {
        disconnect( mAllAnimationsList->selectionModel(), &QItemSelectionModel::currentChanged, this, &cAnimationsComponentEditor::AnimationSelected );

        delete  mAnimationsModel;
        mAnimationsModel = new  ::nQt::nModels::cAnimationsModel( animations );
        mAllAnimationsList->setModel( mAnimationsModel );

        connect( mAllAnimationsList->selectionModel(), &QItemSelectionModel::currentChanged, this, &cAnimationsComponentEditor::AnimationSelected );
    }
    else
    {
        disconnect( mAllAnimationsList->selectionModel(), &QItemSelectionModel::currentChanged, this, &cAnimationsComponentEditor::AnimationSelected );

        delete  mAnimationsModel;
        mAnimationsModel = 0;
        mAllAnimationsList->setModel( mAnimationsModel );
        mAnimationEditor->ShowAnimation( 0, QModelIndex() );

        connect( mAllAnimationsList->selectionModel(), &QItemSelectionModel::currentChanged, this, &cAnimationsComponentEditor::AnimationSelected );
    }
}

