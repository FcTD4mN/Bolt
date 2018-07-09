#pragma once

#include <QtCore/QAbstractListModel>

namespace  nProject { class cProject; }

namespace  nQt {
namespace  nModels {


class cTreeWrapperNode;


class  cProjectHierarchyModel :
    public QAbstractItemModel
{
    Q_OBJECT

public:
    typedef QAbstractItemModel tSuperClass;

public:
    ~cProjectHierarchyModel();
    cProjectHierarchyModel( ::nProject::cProject* iProject, QObject* iParent = 0 );

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

	bool moveRows(const QModelIndex &sourceParent, int sourceRow, int count, const QModelIndex &destinationParent, int destinationChild) override;

    bool RemoveComponent( QModelIndex& iIndex );


		// Drag n Drop
	virtual  QMimeData*		mimeData( const QModelIndexList & indexes ) const override;
	virtual bool			canDropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent) const override;
	virtual bool			dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent) override;
	virtual Qt::DropActions supportedDropActions() const override;

public:
	QStringList		ContextualMenuAllowedActionForIndex( QModelIndex iIndex );
	void			ExecuteActionOnIndex( const QString& iAction, const QModelIndex& iIndex );

public:
    cTreeWrapperNode * ExtractTreeWrapper( const QModelIndex& iIndex ) const;
    void BuildData();

private:
    ::nProject::cProject* mProject;

    cTreeWrapperNode* mRootItem;
};


} //nQt
} //nModels
