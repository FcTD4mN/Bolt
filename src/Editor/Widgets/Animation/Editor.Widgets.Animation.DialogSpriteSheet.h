#pragma once

#include "ui_DialogSpriteSheet.h"

#include <QDialog>

class cDialogSpriteSheet :
    public  QDialog
{
    Q_OBJECT

public:
    typedef  QDialog  tSuperClass;

public:
    virtual  ~cDialogSpriteSheet();
    cDialogSpriteSheet( QWidget* iParent = nullptr );

public:
    int  GetNumberOfRows() const;
    int  GetNumberOfColumns() const;

private:
    Ui::DialogSpriteSheet ui;
};


