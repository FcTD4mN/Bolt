#pragma once

#include "ui_ProjectHierarchyViewer.h"

#include <QWidget>

class  cEntityPropertyDelegate;

class cProjectHierarchyViewer :
    public QWidget
{
    Q_OBJECT

public:
    typedef QWidget tSuperClass;

public:
    ~cProjectHierarchyViewer();
    cProjectHierarchyViewer( QWidget *parent = Q_NULLPTR );

private:
    Ui::ProjectHierarchyViewer ui;
};



