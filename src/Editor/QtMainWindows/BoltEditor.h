#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_BoltEditor.h"

class cBoltEditor :
    public QMainWindow
{
    Q_OBJECT

public:
    cBoltEditor(QWidget *parent = Q_NULLPTR);

private:
    Ui::BoltEditorClass ui;
};
