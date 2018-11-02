#include "Editor.Models.DataWrapperAnimations.h"

#include "Core.ECS.Component.Animations.h"
#include "Core.Animation.Animation.h"

namespace nQt {
namespace nModels {


cDataWrapperAnimationsBase::~cDataWrapperAnimationsBase()
{
}


cDataWrapperAnimationsBase::cDataWrapperAnimationsBase( cTreeWrapperNode* iParent, ::nCore::nECS::nComponent::cAnimations* iAnimations ) :
    tSuperClass( iParent ),
    mAnimations( iAnimations )
{
}


std::string
cDataWrapperAnimationsBase::Type() const
{
    return  "Animations";
}


::nCore::nECS::nComponent::cAnimations*
cDataWrapperAnimationsBase::Animations()
{
    return  mAnimations;
}


// ===========================================================================
// ===========================================================================
// ===========================================================================


cDataWrapperAnimationNode::~cDataWrapperAnimationNode()
{
}


cDataWrapperAnimationNode::cDataWrapperAnimationNode( cTreeWrapperNode * iParent, ::nCore::nAnimation::cAnimation* iAnimation ) :
    tSuperClass( iParent ),
    mAnimation( iAnimation )
{
}


std::string
cDataWrapperAnimationNode::Type() const
{
    return  "AnimationNode";
}


QVariant
cDataWrapperAnimationNode::DataAtColumn( int iColumn )
{
    return  mAnimation->Name().c_str();
}


bool
cDataWrapperAnimationNode::SetData( int iIndex, const QVariant & iData )
{
    mAnimation->Name( iData.toString().toStdString() );
    return  true;
}


::nCore::nAnimation::cAnimation*
cDataWrapperAnimationNode::Animation()
{
    return  mAnimation;
}


// ===========================================================================
// ===========================================================================
// ===========================================================================




cDataWrapperAnimationName::~cDataWrapperAnimationName()
{
}


cDataWrapperAnimationName::cDataWrapperAnimationName( cTreeWrapperNode * iParent, ::nCore::nAnimation::cAnimation* iAnimation ) :
    tSuperClass( iParent, iAnimation )
{
}


std::string
cDataWrapperAnimationName::Type() const
{
    return  "AnimationName";
}


QVariant
cDataWrapperAnimationName::DataAtColumn( int iColumn )
{
    return  mAnimation->Name().c_str();
}


bool
cDataWrapperAnimationName::SetData( int iIndex, const QVariant & iData )
{
    mAnimation->Name( iData.toString().toStdString() );
    return  true;
}


// ===========================================================================
// ===========================================================================
// ===========================================================================




cDataWrapperAnimationFramerate::~cDataWrapperAnimationFramerate()
{
}


cDataWrapperAnimationFramerate::cDataWrapperAnimationFramerate( cTreeWrapperNode * iParent, ::nCore::nAnimation::cAnimation* iAnimation ) :
    tSuperClass( iParent, iAnimation )
{
}


std::string
cDataWrapperAnimationFramerate::Type() const
{
    return  "AnimationFrameRate";
}


QVariant
cDataWrapperAnimationFramerate::DataAtColumn( int iColumn )
{
    return  mAnimation->FrameRate();
}


bool
cDataWrapperAnimationFramerate::SetData( int iIndex, const QVariant & iData )
{
    mAnimation->FrameRate( iData.toFloat() );
    return  true;
}


// ===========================================================================
// ===========================================================================
// ===========================================================================




cDataWrapperAnimationPaused::~cDataWrapperAnimationPaused()
{
}


cDataWrapperAnimationPaused::cDataWrapperAnimationPaused( cTreeWrapperNode * iParent, ::nCore::nAnimation::cAnimation* iAnimation ) :
    tSuperClass( iParent, iAnimation )
{
}


std::string
cDataWrapperAnimationPaused::Type() const
{
    return  "AnimationPaused";
}


QVariant
cDataWrapperAnimationPaused::DataAtColumn( int iColumn )
{
    return  mAnimation->Paused();
}


bool
cDataWrapperAnimationPaused::SetData( int iIndex, const QVariant & iData )
{
    mAnimation->Paused( iData.toBool() );
    return  true;
}


// ===========================================================================
// ===========================================================================
// ===========================================================================




cDataWrapperAnimationFlipped::~cDataWrapperAnimationFlipped()
{
}


cDataWrapperAnimationFlipped::cDataWrapperAnimationFlipped( cTreeWrapperNode * iParent, ::nCore::nAnimation::cAnimation* iAnimation ) :
    tSuperClass( iParent, iAnimation )
{
}


std::string
cDataWrapperAnimationFlipped::Type() const
{
    return  "AnimationFlipped";
}


QVariant
cDataWrapperAnimationFlipped::DataAtColumn( int iColumn )
{
    return  mAnimation->Flipped();
}


bool
cDataWrapperAnimationFlipped::SetData( int iIndex, const QVariant & iData )
{
    mAnimation->Flipped( iData.toBool() );
    return  true;
}


// ===========================================================================
// ===========================================================================
// ===========================================================================




cDataWrapperAnimationLooping::~cDataWrapperAnimationLooping()
{
}


cDataWrapperAnimationLooping::cDataWrapperAnimationLooping( cTreeWrapperNode * iParent, ::nCore::nAnimation::cAnimation* iAnimation ) :
    tSuperClass( iParent, iAnimation )
{
}


std::string
cDataWrapperAnimationLooping::Type() const
{
    return  "AnimationLooping";
}


QVariant
cDataWrapperAnimationLooping::DataAtColumn( int iColumn )
{
    return  mAnimation->IsAnimationLooping();
}


bool
cDataWrapperAnimationLooping::SetData( int iIndex, const QVariant & iData )
{
    mAnimation->IsAnimationLooping( iData.toBool() );
    return  true;
}


// ===========================================================================
// ===========================================================================
// ===========================================================================




cDataWrapperAnimationNumberOfFrames::~cDataWrapperAnimationNumberOfFrames()
{
}


cDataWrapperAnimationNumberOfFrames::cDataWrapperAnimationNumberOfFrames( cTreeWrapperNode * iParent, ::nCore::nAnimation::cAnimation* iAnimation ) :
    tSuperClass( iParent, iAnimation )
{
}


std::string
cDataWrapperAnimationNumberOfFrames::Type() const
{
    return  "AnimationNumberOfFrame";
}


QVariant
cDataWrapperAnimationNumberOfFrames::DataAtColumn( int iColumn )
{
    return  mAnimation->SpriteCount();
}


bool
cDataWrapperAnimationNumberOfFrames::SetData( int iIndex, const QVariant & iData )
{
    return  true;
}


} //nModels
} //nQt

