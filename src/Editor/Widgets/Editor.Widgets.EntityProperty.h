
// REPLACED BY PROPERTYEDITOR

//#pragma once
//
//#include "ui_EntityPropertyWidget.h"
//
//#include <QModelIndex>
//#include <QStyledItemDelegate>
//
//namespace nApplication { class cEditorApplication; }
//namespace nCore  { namespace nECS { namespace nCore { class cEntity; } } }
//namespace  nQt { namespace  nModels { class cEntityModel; } }
//
//class  cEntityPropertyDelegate2;
//
//class cEntityProperty :
//    public QWidget
//{
//    Q_OBJECT
//
//public:
//    typedef QWidget tSuperClass;
//
//public:
//    ~cEntityProperty();
//    cEntityProperty( QWidget *parent = Q_NULLPTR );
//
//public:
//    QString GetEntityName();
//
//public:
//    // Events
//    virtual  void contextMenuEvent( QContextMenuEvent* iEvent ) override;
//
//signals:
//    void  EntityNameChanged( QString iOldName, QString iNewName );
//
//public slots :
//    void selectedEntitiesChanged( ::nCore::nECS::nCore::cEntity* iEntity, ::nQt::nModels::cEntityModel* iModel );
//    void addEmptyComponent();
//    void removeComponent();
//    void EntityIDChanged();
//
//private:
//    Ui::EntityProperty ui;
//    cEntityPropertyDelegate2* mComboDelegate;
//
//    ::nQt::nModels::cEntityModel* mModel;
//    ::nCore::nECS::nCore::cEntity* mEntity;
//    std::string  mEntityName;
//};
//
//
//// ==================================================================
//// ==================================================================
//// ==================================================================
//
//
//class  cEntityPropertyDelegate2 :
//    public  QStyledItemDelegate
//{
//public:
//    typedef QStyledItemDelegate tSuperClass;
//
//public:
//    cEntityPropertyDelegate2( QWidget* iParent = 0 );
//
//public:
//    // Overrides
//    QWidget* createEditor( QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index ) const override;
//    void    setEditorData( QWidget *editor, const QModelIndex &index ) const override;
//    void    setModelData( QWidget *editor, QAbstractItemModel *model, const QModelIndex &index ) const override;
//
//public:
//    void SetEntity( ::nCore::nECS::nCore::cEntity* iEntity );
//
//private:
//    ::nCore::nECS::nCore::cEntity* mEntity;
//};
//
//
//
//
