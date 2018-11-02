#pragma once

#include <QAbstractItemModel>

#include <QStyledItemDelegate>

namespace  nQt {
namespace  nModels {

class cTreeWrapperNode;

class  cModelBase :
    public QAbstractItemModel
{
    Q_OBJECT

public:
    typedef QAbstractItemModel tSuperClass;

public:
    virtual ~cModelBase();
    cModelBase( QObject* iParent = 0 );

public:
    // Interface overrides
    // Read
    virtual  int rowCount( const QModelIndex& iParent = QModelIndex() ) const override;
    virtual  int columnCount( const QModelIndex& iParent = QModelIndex() ) const override;

    virtual  QVariant data( const QModelIndex& iIndex, int iRole ) const override;
    virtual  QVariant headerData( int iSection, Qt::Orientation iOrientation, int iRole = Qt::DisplayRole ) const override;
    virtual  QModelIndex index( int row, int column, const QModelIndex &parent = QModelIndex() ) const override;
    virtual  QModelIndex parent( const QModelIndex &index ) const override;
    virtual  Qt::ItemFlags flags( const QModelIndex& iIndex ) const override;

    // Write
    virtual  bool setData( const QModelIndex &index, const QVariant &value, int role = Qt::EditRole ) override;
    virtual  bool setHeaderData( int section, Qt::Orientation orientation, const QVariant &value, int role = Qt::EditRole ) override;

    virtual  bool insertColumns( int iIndex, int iCount, const QModelIndex &parent = QModelIndex() ) override;
    virtual  bool removeColumns( int iIndex, int iCount, const QModelIndex &parent = QModelIndex() ) override;
    virtual  bool insertRows( int iIndex, int iCount, const QModelIndex &parent = QModelIndex() ) override;
    virtual  bool removeRows( int iIndex, int iCount, const QModelIndex &parent = QModelIndex() ) override;

    virtual  bool moveRows(const QModelIndex &sourceParent, int sourceRow, int count, const QModelIndex &destinationParent, int destinationChild) override;

        // Drag n Drop
    virtual  QStringList    mimeTypes() const override;
    virtual  QMimeData*     mimeData( const QModelIndexList & indexes ) const override;

public:
    // ContextualMenu
    virtual  QStringList    ContextualMenuAllowedActionForIndex( QModelIndex iIndex );
    virtual  void           ExecuteActionOnIndex( const QString& iAction, const QModelIndex& iIndex );

public:
    // ItemDelegate
    virtual  QStyledItemDelegate *   CreateModelDelegate();

public:
    cTreeWrapperNode *  ExtractTreeWrapper( const QModelIndex& iIndex ) const;
    QModelIndex         GetModelIndexFromWrapper( const cTreeWrapperNode* iNode ) const;
    virtual  void       BuildData();

private:
    bool _GetModelIndexFromWrapper( QModelIndex* oIndex, const QModelIndex& iParentIndex, const cTreeWrapperNode* inode ) const;

protected:
    cTreeWrapperNode* mRootItem;
};


} //nQt
} //nModels
