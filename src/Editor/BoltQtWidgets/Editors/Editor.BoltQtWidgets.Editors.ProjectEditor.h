#pragma once

#include "ui_ProjectEditor.h"

#include <QWidget>


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
    Ui::ProjectEditor ui;
};


