#pragma once

#include "ui_ProjectEditor.h"

#include <QWidget>

namespace nProject { class cProject; }

class cProjectEditor :
    public QWidget
{
    Q_OBJECT

public:
    typedef QWidget tSuperClass;

public:
    ~cProjectEditor();
    cProjectEditor( QWidget *parent = Q_NULLPTR );

public  slots:
    void  ProjectLoaded( ::nProject::cProject* iProject );

private:
    Ui::ProjectEditor ui;
};


