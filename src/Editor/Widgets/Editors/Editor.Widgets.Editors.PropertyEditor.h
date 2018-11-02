#pragma once

#include "ui_PropertyEditor.h"

#include "Editor.Models.ModelBase.h"

#include <QModelIndex>

#include <memory>

//namespace  nQt { namespace  nModels { class cModelBase; } }

class cPropertyEditor :
    public QWidget
{
    Q_OBJECT

public:
    typedef QWidget tSuperClass;

public:
    ~cPropertyEditor();
    cPropertyEditor( QWidget *parent = Q_NULLPTR );

public:
    virtual  void contextMenuEvent( QContextMenuEvent* iEvent ) override;
    virtual  void closeEvent( QCloseEvent* iEvent ) override;

public slots:
    void  ShowProperties( const std::shared_ptr< ::nQt::nModels::cModelBase >& iModel );

    void ForceRefresh();

private:
    Ui::PropertyEditor ui;
    std::shared_ptr< ::nQt::nModels::cModelBase > mModel; ;
};



