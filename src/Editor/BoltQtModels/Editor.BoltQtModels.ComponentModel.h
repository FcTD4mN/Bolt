#pragma once

#include <QAbstractItemModel>

namespace  nECS { class cComponent; }

namespace  nQt {
namespace  nModels {

class cTreeWrapperNode;

class  cComponentModel :
    public QAbstractItemModel
{
    Q_OBJECT

public:
    typedef QAbstractItemModel tSuperClass;

public:
    ~cComponentModel();
    cComponentModel( ::nECS::cComponent* iComponent, QObject* iParent = 0 );

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
    bool setData( const QModelIndex &index, const QVariant &value, int role = Qt::EditRole ) override;
    bool setHeaderData( int section, Qt::Orientation orientation, const QVariant &value, int role = Qt::EditRole ) override;

    bool insertColumns( int iIndex, int iCount, const QModelIndex &parent = QModelIndex() ) override;
    bool removeColumns( int iIndex, int iCount, const QModelIndex &parent = QModelIndex() ) override;
    bool insertRows( int iIndex, int iCount, const QModelIndex &parent = QModelIndex() ) override;
    bool removeRows( int iIndex, int iCount, const QModelIndex &parent = QModelIndex() ) override;

    bool AddNewVariable();
    bool RemoveVariable( const QModelIndex& iIndex );


public:
    cTreeWrapperNode*  ExtractTreeWrapper( const QModelIndex& iIndex ) const;
    void BuildData();

private:
    ::nECS::cComponent* mComponent;

    cTreeWrapperNode* mRootItem;
};

} //nQt
} //nModels
