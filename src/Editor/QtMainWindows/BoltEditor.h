#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_BoltEditor.h"

class cEditorApplication;
class cEntityListModel;

class cBoltEditor :
    public QMainWindow
{
    Q_OBJECT

public:
    ~cBoltEditor();
    cBoltEditor(QWidget *parent = Q_NULLPTR);

    void Setup();

private:
    Ui::BoltEditorClass ui;
    cEntityListModel* mModel;
    cEditorApplication* mApp;
};
