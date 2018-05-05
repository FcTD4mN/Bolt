#pragma once

#include "ui_SnapGridSettings.h"

#include <QDialog>

class cSnapGridSettings :
    public QDialog
{
    Q_OBJECT

public:
    typedef QDialog tSuperClass;

public:
    ~cSnapGridSettings();
    cSnapGridSettings( QWidget *parent = Q_NULLPTR );

public:
    double CellWidth() const;
    double CellHeight() const;
    void   SetCellWidth( double iWidth );
    void   SetCellHeight( double iHeight );

private:
    Ui::DialogSnapGridSettings ui;
};
