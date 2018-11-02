#pragma once

#include <QAbstractListModel>

namespace  nCore { namespace  nRegistries { class cComponentRegistry; } }
namespace nCore  { namespace nECS { namespace nCore { class cComponent; } } }

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

    QModelIndex  AddNewComponent();
    void         RemoveComponent( const QModelIndex& iIndex );
    QModelIndex  GetComponentIndex( ::nCore::nECS::nCore::cComponent* iPrototype );

private:
    ::nCore::nRegistries::cComponentRegistry* mComponentRegistryInstance;
};

} //nQt
} //nModels
