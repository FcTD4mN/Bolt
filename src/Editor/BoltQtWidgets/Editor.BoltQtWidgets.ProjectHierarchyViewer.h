#pragma once

#include "ui_ProjectHierarchyViewer.h"

#include <QWidget>

namespace nProject { class cProject; }

class cProjectHierarchyViewer :
    public QWidget
{
    Q_OBJECT

public:
    typedef QWidget tSuperClass;

public:
    ~cProjectHierarchyViewer();
    cProjectHierarchyViewer( QWidget *parent = Q_NULLPTR );


public  slots:
    void  ProjectLoaded( ::nProject::cProject* iProject );


private:
    Ui::ProjectHierarchyViewer ui;
};



