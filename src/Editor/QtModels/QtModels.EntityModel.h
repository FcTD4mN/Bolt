#include "QtCore/QAbstractTableModel"

class cEntity;

class  cEntityModel :
    public QAbstractTableModel
{
    Q_OBJECT

public:
    typedef QAbstractTableModel tSuperClass;

public:
    cEntityModel( cEntity* iEntity, QObject* iParent = 0 );

public:
    // Interface overrides
    virtual  int rowCount( const QModelIndex& iParent = QModelIndex() ) const override;
    virtual  int columnCount( const QModelIndex& iParent = QModelIndex() ) const override;
    virtual  QVariant data( const QModelIndex& iIndex, int iRole ) const override;
    virtual  QVariant headerData( int iSection, Qt::Orientation iOrientation, int iRole = Qt::DisplayRole ) const override;

private:
    cEntity* mEntity;
};
