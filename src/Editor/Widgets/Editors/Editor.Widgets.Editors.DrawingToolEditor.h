#pragma once


#include <QHBoxLayout>
#include <QStyledItemDelegate>
#include <QTreeView>
#include <QWidget>

namespace  nQt::nModels { class cDrawingToolModelBase; }

class cDrawingToolEditor :
    public QWidget
{
    Q_OBJECT

public:
    typedef QWidget tSuperClass;

public:
    ~cDrawingToolEditor();
    cDrawingToolEditor( QWidget *parent = Q_NULLPTR );

public  slots:
    void  ShowTool( ::nQt::nModels::cDrawingToolModelBase* iDrawingToolModelBase );

private:
    ::nQt::nModels::cDrawingToolModelBase*  mDrawingToolModelBase;
    QTreeView*                              mTreeView;
    QHBoxLayout*                            mMainLayout;
    QStyledItemDelegate*                    mModelDelegate;
};

