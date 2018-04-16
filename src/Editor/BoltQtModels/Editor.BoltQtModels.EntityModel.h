#pragma once

#include <QtCore/QAbstractItemModel>

namespace  nECS { class cEntity; }

namespace  nQt {
namespace  nModels {

class cTreeWrapperNode;

class  cEntityModel :
    public QAbstractItemModel
{
    Q_OBJECT

public:
    typedef QAbstractItemModel tSuperClass;

public:
    ~cEntityModel();
    cEntityModel( ::nECS::cEntity* iEntity, QObject* iParent = 0 );

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
    bool setData( const QModelIndex &index, const QVariant &value, int role = Qt::EditRole ) override;    bool insertColumns( int position, int columns );
    bool setHeaderData( int section, Qt::Orientation orientation, const QVariant &value, int role = Qt::EditRole ) override;

    bool insertColumns( int iIndex, int iCount, const QModelIndex &parent = QModelIndex() ) override;
    bool removeColumns( int iIndex, int iCount, const QModelIndex &parent = QModelIndex() ) override;
    bool insertRows( int iIndex, int iCount, const QModelIndex &parent = QModelIndex() ) override;
    bool removeRows( int iIndex, int iCount, const QModelIndex &parent = QModelIndex() ) override;


public:
    cTreeWrapperNode*  ExtractTreeWrapper( const QModelIndex& iIndex ) const;
    void BuildData();

private:
    ::nECS::cEntity* mEntity;

    cTreeWrapperNode* mRootItem;
};

} //nQt
} //nModels
