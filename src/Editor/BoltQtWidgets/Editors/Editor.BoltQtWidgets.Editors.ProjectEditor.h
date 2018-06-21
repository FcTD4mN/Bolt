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

private:
	void  AskFileAndSetProject();

public  slots:
    void  ProjectLoaded( ::nProject::cProject* iProject );
    void  SaveProject();
    void  SaveProjectAs();

    void  ProjectResolutionChanged();
    void  ProjectFrameLimitChanged();
    void  ProjectNameChanged();

private:
    Ui::ProjectEditor ui;
	::nProject::cProject* mProject;
};


