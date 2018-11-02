#pragma once

#include "Editor.Models.ModelBase.h"

#include <QAbstractItemModel>

namespace nCore::nECS::nComponent { class cAnimations; }
namespace nCore::nAnimation { class  cAnimation; }

namespace  nQt {
namespace  nModels {

class cTreeWrapperNode;

class  cAnimationsModel :
    public cModelBase
{
    Q_OBJECT

public:
    typedef cModelBase tSuperClass;

public:
    virtual ~cAnimationsModel();
    cAnimationsModel( ::nCore::nECS::nComponent::cAnimations* iAnimations, QObject* iParent = 0 );
    cAnimationsModel( cAnimationsModel& iRef );

public:
    // cModelBase overrides
        // Read
    virtual  Qt::ItemFlags  flags( const QModelIndex& iIndex ) const override;
    virtual  bool           removeRows( int iIndex, int iCount, const QModelIndex &parent = QModelIndex() ) override;

    void                    BuildData() override;

public:
    // ContextualMenu
    QStringList     ContextualMenuAllowedActionForIndex( QModelIndex iIndex ) override;
    void            ExecuteActionOnIndex( const QString& iAction, const QModelIndex& iIndex ) override;

public:
    // ItemDelegate
    virtual  QStyledItemDelegate *   CreateModelDelegate() override;

public:
    // Model manipulation
    void                                AddAnimation( const QModelIndex& iPosition );
    void                                RemoveAnimation( const QModelIndex& iPosition );
    ::nCore::nAnimation::cAnimation*    AnimationAtIndex( const QModelIndex& iIndex );

    // Easy get interface
    float   FrameRate() const;
    bool    Flipped() const;

private:
    ::nCore::nECS::nComponent::cAnimations* mAnimations;
};

} //nQt
} //nModels
