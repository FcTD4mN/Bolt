#include <QtCore/QAbstractTableModel>

namespace  nECS { class cEntity; }

namespace  nQt {
namespace  nModels {

class  cEntityModel :
    public QAbstractTableModel
{
    Q_OBJECT

public:
    typedef QAbstractTableModel tSuperClass;

public:
    cEntityModel( ::nECS::cEntity* iEntity, QObject* iParent = 0 );

public:
    // Interface overrides
    virtual  int rowCount( const QModelIndex& iParent = QModelIndex() ) const override;
    virtual  int columnCount( const QModelIndex& iParent = QModelIndex() ) const override;
    virtual  QVariant data( const QModelIndex& iIndex, int iRole ) const override;
    virtual  QVariant headerData( int iSection, Qt::Orientation iOrientation, int iRole = Qt::DisplayRole ) const override;
    virtual  QModelIndex index( int row, int column, const QModelIndex &parent = QModelIndex() ) const override;
    virtual  QModelIndex parent( const QModelIndex &index ) const override;

private:
    ::nECS::cEntity* mEntity;
};

} //nQt
} //nModels
