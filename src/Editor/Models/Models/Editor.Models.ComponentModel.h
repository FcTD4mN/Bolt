#pragma once

#include "Editor.Models.ModelBase.h"

#include <QAbstractItemModel>

namespace nCore  { namespace nECS { namespace nCore { class cComponent; } } }

namespace  nQt {
namespace  nModels {

class cTreeWrapperNode;

class  cComponentModel :
    public cModelBase
{
    Q_OBJECT

public:
    typedef cModelBase tSuperClass;

public:
    virtual ~cComponentModel();
    cComponentModel( ::nCore::nECS::nCore::cComponent* iComponent, QObject* iParent = 0 );
    cComponentModel( cComponentModel& iRef );

public:
    // cModelBase overrides
        // Read
    virtual  Qt::ItemFlags flags( const QModelIndex& iIndex ) const override;

        // Write
    bool insertColumns( int iIndex, int iCount, const QModelIndex &parent = QModelIndex() ) override;
    bool removeColumns( int iIndex, int iCount, const QModelIndex &parent = QModelIndex() ) override;
    bool insertRows( int iIndex, int iCount, const QModelIndex &parent = QModelIndex() ) override;
    bool removeRows( int iIndex, int iCount, const QModelIndex &parent = QModelIndex() ) override;

    void BuildData() override;

public:
    // ContextualMenu
    QStringList     ContextualMenuAllowedActionForIndex( QModelIndex iIndex ) override;
    void            ExecuteActionOnIndex( const QString& iAction, const QModelIndex& iIndex ) override;

public:
    // ItemDelegate
    virtual  QStyledItemDelegate *   CreateModelDelegate() override;

public:
    // Variable controls
    bool AddNewVariable();
    bool RemoveVariable( const QModelIndex& iIndex );

private:
    ::nCore::nECS::nCore::cComponent*   mComponent;
    cTreeWrapperNode*                   mVariableParentNode;
};

} //nQt
} //nModels
