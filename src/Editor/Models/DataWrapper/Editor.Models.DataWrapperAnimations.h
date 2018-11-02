#pragma once

#include "Editor.Models.TreeWrapper.h"

#include <QtCore>
#include <vector>

namespace nCore::nECS::nComponent   { class cAnimations; }
namespace nCore::nAnimation         { class cAnimation; }

namespace nQt {
namespace nModels {


class cDataWrapperAnimationsBase :
    public cTreeWrapperNode
{
public:
    typedef cTreeWrapperNode tSuperClass;

public:
    virtual ~cDataWrapperAnimationsBase();
    cDataWrapperAnimationsBase( cTreeWrapperNode* iParent, ::nCore::nECS::nComponent::cAnimations* iAnimations );

public:
    // Type
    virtual std::string Type() const override;

public:
    ::nCore::nECS::nComponent::cAnimations* Animations();

protected:
    ::nCore::nECS::nComponent::cAnimations* mAnimations;
};


// -----------------------------------------------------
// -----------------------------------------------------
// -----------------------------------------------------


class cDataWrapperAnimationNode :
    public cTreeWrapperNode
{
public:
    typedef cTreeWrapperNode tSuperClass;

public:
    virtual ~cDataWrapperAnimationNode();
    cDataWrapperAnimationNode( cTreeWrapperNode* iParent, ::nCore::nAnimation::cAnimation* iAnimation );

public:
    // Type
    virtual std::string Type() const override;

public:
    // Data
    virtual  QVariant   DataAtColumn( int iColumn ) override;
    virtual  bool       SetData( int iIndex, const QVariant& iData ) override;

public:
    ::nCore::nAnimation::cAnimation* Animation();

protected:
    ::nCore::nAnimation::cAnimation* mAnimation;
};


// -----------------------------------------------------
// -----------------------------------------------------
// -----------------------------------------------------


class cDataWrapperAnimationName :
    public cDataWrapperAnimationNode
{
public:
    typedef cDataWrapperAnimationNode tSuperClass;

public:
    virtual ~cDataWrapperAnimationName();
    cDataWrapperAnimationName( cTreeWrapperNode* iParent, ::nCore::nAnimation::cAnimation* iAnimation );

public:
    // Type
    virtual std::string Type() const override;

public:
    // Data
    virtual  QVariant   DataAtColumn( int iColumn ) override;
    virtual  bool       SetData( int iIndex, const QVariant& iData ) override;
};


// -----------------------------------------------------
// -----------------------------------------------------
// -----------------------------------------------------


class cDataWrapperAnimationFramerate :
    public cDataWrapperAnimationNode
{
public:
    typedef cDataWrapperAnimationNode tSuperClass;

public:
    virtual ~cDataWrapperAnimationFramerate();
    cDataWrapperAnimationFramerate( cTreeWrapperNode* iParent, ::nCore::nAnimation::cAnimation* iAnimation );

public:
    // Type
    virtual std::string Type() const override;

public:
    // Data
    virtual  QVariant   DataAtColumn( int iColumn ) override;
    virtual  bool       SetData( int iIndex, const QVariant& iData ) override;
};


// -----------------------------------------------------
// -----------------------------------------------------
// -----------------------------------------------------


class cDataWrapperAnimationPaused :
    public cDataWrapperAnimationNode
{
public:
    typedef cDataWrapperAnimationNode tSuperClass;

public:
    virtual ~cDataWrapperAnimationPaused();
    cDataWrapperAnimationPaused( cTreeWrapperNode* iParent, ::nCore::nAnimation::cAnimation* iAnimation );

public:
    // Type
    virtual std::string Type() const override;

public:
    // Data
    virtual  QVariant   DataAtColumn( int iColumn ) override;
    virtual  bool       SetData( int iIndex, const QVariant& iData ) override;
};


// -----------------------------------------------------
// -----------------------------------------------------
// -----------------------------------------------------


class cDataWrapperAnimationFlipped :
    public cDataWrapperAnimationNode
{
public:
    typedef cDataWrapperAnimationNode tSuperClass;

public:
    virtual ~cDataWrapperAnimationFlipped ();
    cDataWrapperAnimationFlipped ( cTreeWrapperNode* iParent, ::nCore::nAnimation::cAnimation* iAnimation );

public:
    // Type
    virtual std::string Type() const override;

public:
    // Data
    virtual  QVariant   DataAtColumn( int iColumn ) override;
    virtual  bool       SetData( int iIndex, const QVariant& iData ) override;
};


// -----------------------------------------------------
// -----------------------------------------------------
// -----------------------------------------------------


class cDataWrapperAnimationLooping :
    public cDataWrapperAnimationNode
{
public:
    typedef cDataWrapperAnimationNode tSuperClass;

public:
    virtual ~cDataWrapperAnimationLooping ();
    cDataWrapperAnimationLooping ( cTreeWrapperNode* iParent, ::nCore::nAnimation::cAnimation* iAnimation );

public:
    // Type
    virtual std::string Type() const override;

public:
    // Data
    virtual  QVariant   DataAtColumn( int iColumn ) override;
    virtual  bool       SetData( int iIndex, const QVariant& iData ) override;
};


// -----------------------------------------------------
// -----------------------------------------------------
// -----------------------------------------------------


class cDataWrapperAnimationNumberOfFrames :
    public cDataWrapperAnimationNode
{
public:
    typedef cDataWrapperAnimationNode tSuperClass;

public:
    virtual ~cDataWrapperAnimationNumberOfFrames();
    cDataWrapperAnimationNumberOfFrames( cTreeWrapperNode* iParent, ::nCore::nAnimation::cAnimation* iAnimation );

public:
    // Type
    virtual std::string Type() const override;

public:
    // Data
    virtual  QVariant   DataAtColumn( int iColumn ) override;
    virtual  bool       SetData( int iIndex, const QVariant& iData ) override;
};






} // nModels
} // nQT