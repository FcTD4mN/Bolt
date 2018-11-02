#pragma once

#include "Editor.Models.ModelBase.h"


#include <QAbstractItemModel>


namespace nCore { namespace nECS { namespace nCore { class cEntity; } } }

namespace  nQt {
namespace  nModels {

class cTreeWrapperNode;

class  cEntityModel :
    public cModelBase
{
    Q_OBJECT

public:
    typedef cModelBase tSuperClass;

public:
    virtual ~cEntityModel();
    cEntityModel( ::nCore::nECS::nCore::cEntity* iEntity, QObject* iParent = 0 );
    cEntityModel( cEntityModel& iRef );

public:
    // cModelBase overrides
        // Read
    virtual  Qt::ItemFlags flags( const QModelIndex& iIndex ) const override;

        // Write
    bool setData( const QModelIndex &index, const QVariant &value, int role = Qt::EditRole ) override;
    bool insertRows( int iIndex, int iCount, const QModelIndex &parent = QModelIndex() ) override;


public:
    // Component controls
    bool AddEmptyComponent( const QModelIndex& iIndex );
    bool RemoveComponent( const QModelIndex& iIndex );
    bool AddEmptyTag( const QModelIndex& iIndex );
    bool RemoveTag( const QModelIndex& iIndex );
    void UpdateModelByComponentName( const QString& iName );

public:
    // ContextualMenu
    QStringList     ContextualMenuAllowedActionForIndex( QModelIndex iIndex ) override;
    void            ExecuteActionOnIndex( const QString& iAction, const QModelIndex& iIndex ) override;

public:
    // ItemDelegate
    virtual  QStyledItemDelegate*  CreateModelDelegate() override;

public:
    virtual  void  BuildData() override;

signals:
    void  EntityNameChanged( QString iOldName, QString iNewName );

private:
    ::nCore::nECS::nCore::cEntity* mEntity;
};

} //nQt
} //nModels
