#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_BoltEditor.h"

class BoltEditor : public QMainWindow
{
	Q_OBJECT

public:
	BoltEditor(QWidget *parent = Q_NULLPTR);

private:
	Ui::BoltEditorClass ui;
};
