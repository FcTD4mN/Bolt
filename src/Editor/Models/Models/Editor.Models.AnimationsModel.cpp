#include "Editor.Models.AnimationsModel.h"


#include "Core.ECS.Component.Animations.h"

#include "Editor.Delegates.ComponentProperties.h"
#include "Editor.Models.DataWrapperAnimations.h"



namespace  nQt {
namespace  nModels {


cAnimationsModel::~cAnimationsModel()
{
}


cAnimationsModel::cAnimationsModel( ::nCore::nECS::nComponent::cAnimations* iAnimations, QObject* iParent ) :
    tSuperClass( iParent ),
    mAnimations( iAnimations )
{
    BuildData();
}


cAnimationsModel::cAnimationsModel( cAnimationsModel & iRef ) :
    mAnimations( iRef.mAnimations )
{
    BuildData();
}


// --------------------------------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------- cModelBase Overrides
// --------------------------------------------------------------------------------------------------------------


Qt::ItemFlags
cAnimationsModel::flags( const QModelIndex & iIndex ) const
{
    if( !iIndex.isValid() )
        return 0;

    return QAbstractItemModel::flags( iIndex );
}


bool
cAnimationsModel::removeRows( int iIndex, int iCount, const QModelIndex & iParent )
{
    cTreeWrapperNode *parentItem = ExtractTreeWrapper( iParent );
    bool success = true;

    beginRemoveRows( iParent, iIndex, iIndex + iCount - 1 );
    success = parentItem->RemoveChildrenAtIndexWithDelete( iIndex, iCount );
    endRemoveRows();

    return success;
}


void
cAnimationsModel::BuildData()
{
    if( mRootItem || !mAnimations )
        return;

    mRootItem = new cTreeWrapperNode( 0 );
    mRootItem->AppendData( "Animations" );

    for( int i = 0; i < mAnimations->AnimationCount(); ++i )
    {
        auto animation = mAnimations->AnimationAtIndex( i );
        auto animNode = new cDataWrapperAnimationNode( mRootItem, animation );

            new cDataWrapperAnimationName( animNode, animation );
            new cDataWrapperAnimationFramerate( animNode, animation );
            new cDataWrapperAnimationFlipped( animNode, animation );
            new cDataWrapperAnimationPaused( animNode, animation );
            new cDataWrapperAnimationLooping( animNode, animation );
            new cDataWrapperAnimationNumberOfFrames( animNode, animation );
    }
}


// --------------------------------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------- ContextualMenu
// --------------------------------------------------------------------------------------------------------------


QStringList
cAnimationsModel::ContextualMenuAllowedActionForIndex( QModelIndex iIndex )
{
    QStringList outputList;

    return  outputList;
}


void
cAnimationsModel::ExecuteActionOnIndex( const QString & iAction, const QModelIndex & iIndex )
{
}


// --------------------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------- ItemDelegate
// --------------------------------------------------------------------------------------------------------------


QStyledItemDelegate *
cAnimationsModel::CreateModelDelegate()
{
    return  0;
}


// --------------------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------- Model manipulation
// --------------------------------------------------------------------------------------------------------------


void
cAnimationsModel::AddAnimation( const QModelIndex& iPosition )
{
    int insertionIndex = iPosition.row() + 1; // So we insert after current selection, not before

    auto animation = mAnimations->AddEmptyAnimationAtIndex( "NewAnimation_" + std::to_string( mAnimations->AnimationCount() ), insertionIndex );

    beginInsertRows( QModelIndex(), insertionIndex, insertionIndex );

        auto animNode = new cDataWrapperAnimationNode( 0, animation );
        mRootItem->InsertChild( animNode, insertionIndex );

            new cDataWrapperAnimationName( animNode, animation );
            new cDataWrapperAnimationFramerate( animNode, animation );
            new cDataWrapperAnimationFlipped( animNode, animation );
            new cDataWrapperAnimationPaused( animNode, animation );
            new cDataWrapperAnimationLooping( animNode, animation );
            new cDataWrapperAnimationNumberOfFrames( animNode, animation );

    endInsertRows();
}


void
cAnimationsModel::RemoveAnimation( const QModelIndex & iPosition )
{
    removeRow( iPosition.row(), QModelIndex() );
    mAnimations->RemoveAnimationAtIndex( iPosition.row() );
}


::nCore::nAnimation::cAnimation*
cAnimationsModel::AnimationAtIndex( const QModelIndex & iIndex )
{
    auto item = ExtractTreeWrapper( iIndex );
    auto itemAsAnimationNode = dynamic_cast<cDataWrapperAnimationNode*>( item );
    if( itemAsAnimationNode )
        return  itemAsAnimationNode->Animation();

    return  nullptr;
}


// --------------------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------- Easy get interface
// --------------------------------------------------------------------------------------------------------------


float
cAnimationsModel::FrameRate() const
{
    QVariant frameRate = index( 1, 0, index( 0, 0 ) ).data();
    return  frameRate.toFloat();
}


bool
cAnimationsModel::Flipped() const
{
    QVariant flipped = index( 2, 0, index( 0, 0 ) ).data();
    return  flipped.toBool();
}

} //nQt
} //nModels
