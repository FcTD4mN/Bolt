#pragma once

#include "ui_ProjectHierarchyViewer.h"

#include <QWidget>
#include <QStyledItemDelegate>

#include <memory>

namespace nCore { namespace nECS { namespace nCore { class cSystem;  } } }
namespace nCore { namespace nECS { namespace nCore { class cEntity;  } } }
namespace nProject  { class cProject; }
namespace nQt::nModels { class cProjectHierarchyModel; }
namespace nQt::nModels { class cModelBase; }

class cProjectHierarchyDelegate;
class cTreeWrapperNode;


class cProjectHierarchyViewer :
    public QWidget
{
    Q_OBJECT

public:
    typedef QWidget tSuperClass;

public:
    ~cProjectHierarchyViewer();
    cProjectHierarchyViewer( QWidget *parent = Q_NULLPTR );


public:
    // Events
    virtual  void contextMenuEvent( QContextMenuEvent* iEvent ) override;


public  slots:
    void  ProjectLoaded( ::nQt::nModels::cProjectHierarchyModel* iProject );
    void  SaveProject();

    void  PrototypeEditionAsked( QModelIndex );
    void  ComponentEditionAsked( QModelIndex );
    void  ScreenEditionAsked( QModelIndex );

    void EntitySelectionChanged( const std::vector< ::nCore::nECS::nCore::cEntity* >& iEntities );

signals:
    void prototypeEditionAsked( QModelIndex );
    void componentEditionAsked( QModelIndex );
    void screenEditionAsked( QModelIndex );
    void itemClicked( QModelIndex );

    void showEntityProperties( const std::shared_ptr< ::nQt::nModels::cModelBase >& iModel );

private:
    Ui::ProjectHierarchyViewer              ui;

    cProjectHierarchyDelegate*              mComboDelegate;
    ::nQt::nModels::cProjectHierarchyModel* mModel;
    QItemSelectionModel*                    mSelectionModel;
};


// ==================================================================
// ==================================================================
// ==================================================================


class  cProjectHierarchyDelegate :
    public  QStyledItemDelegate
{
public:
    typedef QStyledItemDelegate tSuperClass;

public:
    cProjectHierarchyDelegate( QWidget* iParent = 0 );

public:
    // Overrides
    QWidget * createEditor( QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index ) const override;
    void    setEditorData( QWidget *editor, const QModelIndex &index ) const override;
    void    setModelData( QWidget *editor, QAbstractItemModel *model, const QModelIndex &index ) const override;

public:
    void SetModel( ::nQt::nModels::cProjectHierarchyModel* iModel );

private:
    ::nCore::nECS::nCore::cSystem*                        mSystem;
    ::nQt::nModels::cProjectHierarchyModel* mProjectModel;
};


