#pragma once

#include <QAbstractListModel>

namespace  nECS { class cComponentRegistry; }

namespace  nQt {
namespace  nModels {

class  cComponentListModel :
    public QAbstractListModel
{
    Q_OBJECT

public:
    typedef QAbstractListModel tSuperClass;

public:
    cComponentListModel( QObject* iParent = 0 );

public:
    // Interface overrides
    virtual  int rowCount( const QModelIndex& iParent = QModelIndex() ) const override;
    virtual  QVariant data( const QModelIndex& iIndex, int iRole ) const override;
    virtual  QVariant headerData( int iSection, Qt::Orientation iOrientation, int iRole = Qt::DisplayRole ) const override;

    void AddNewComponent();
    void RemoveComponent( QModelIndex& iIndex );

private:
    ::nECS::cComponentRegistry* mComponentRegistryInstance;
};

} //nQt
} //nModels
