#pragma once

#include "Editor.Models.ModelBase.h"

namespace nCore::nProject       { class cProject; }
namespace nCore::nECS::nCore    { class cEntity; }
namespace nCore::nECS::nCore    { class cComponent; }

namespace  nQt {
namespace  nModels {


class cTreeWrapperNode;


class  cProjectHierarchyModel :
    public cModelBase
{
    Q_OBJECT

public:
    typedef cModelBase tSuperClass;

public:
    virtual ~cProjectHierarchyModel();
    cProjectHierarchyModel( ::nCore::nProject::cProject* iProject, QObject* iParent = 0 );

public:
    // Interface overrides
    // Read
    virtual  Qt::ItemFlags flags( const QModelIndex& iIndex ) const override;
    virtual  QVariant data( const QModelIndex& iIndex, int iRole ) const override;

    // Write
    bool setData( const QModelIndex &index, const QVariant &value, int role = Qt::EditRole ) override;
    bool insertRows( int iIndex, int iCount, const QModelIndex &parent = QModelIndex() ) override;

        // Drag n Drop
    QStringList             mimeTypes() const override;
    virtual  QMimeData*     mimeData( const QModelIndexList & indexes ) const override;
    virtual bool            canDropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent) const override;
    virtual bool            dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent) override;
    virtual Qt::DropActions supportedDropActions() const override;

public:
    // ContextualMenu
    virtual QStringList ContextualMenuAllowedActionForIndex( QModelIndex iIndex ) override;
    virtual void        ExecuteActionOnIndex( const QString& iAction, const QModelIndex& iIndex ) override;

public:
    virtual void BuildData() override;

public:
    // Model Interactions ( Interface to use when willing to change project )
    bool            RemoveEntity( ::nCore::nECS::nCore::cEntity* iEntity );
    bool            RemoveComponent( QModelIndex& iIndex );
    void            AddEntityToCurrentScreenInLayer( ::nCore::nECS::nCore::cEntity* iEntity, int iIndex );
    void            CloneEntity( ::nCore::nECS::nCore::cEntity* iEntity );

    ::nCore::nProject::cProject* Project();

public:
    // QModelIndex translations
    QModelIndex  GetEntityModelIndex( const ::nCore::nECS::nCore::cEntity* iEntity );
    QModelIndex  GetProjectModelIndex();
    QModelIndex  GetScreenModelIndexAtIndex( int iIndex );
    QModelIndex  GetLayerModelIndexAtIndex( QModelIndex iScreenModelIndex, int iIndex );
    QModelIndex  GetEntityModelIndexAtIndex( QModelIndex iLayerModelIndex, int iIndex );

public:
    // Saving
    void  SaveProject();
    void  SaveComponent( const ::nCore::nECS::nCore::cComponent* iComponent );
    void  SaveComponentAs( const ::nCore::nECS::nCore::cComponent* iComponent );
    void  SavePrototype( const ::nCore::nECS::nCore::cEntity* iEntity );
    void  SavePrototypeAs( const ::nCore::nECS::nCore::cEntity* iEntity );

private:
    void  _AskFileAndSetProject();

public:
    // Enumerators
    void  AssetsEntitiesEnumerator( std::function<void( ::nCore::nECS::nCore::cEntity* )> iFunction );
    void  AssetsComponentsEnumerator( std::function<void( ::nCore::nECS::nCore::cComponent* )> iFunction );

    // This is a tool function to search a node from another node iNodeToSearch, using the first data's value as discriminant
    cTreeWrapperNode* _FindNodeWithinNode( const QVariant& iNodeFirstColumnData, cTreeWrapperNode* iNodeToSearch );

signals:
    void  prototypeEditionAsked( QModelIndex );
    void  componentEditionAsked( QModelIndex );
    void  screenEditionAsked( QModelIndex );

private:
    ::nCore::nProject::cProject* mProject;
};


} //nQt
} //nModels
