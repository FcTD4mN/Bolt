#pragma once

#include "Editor.Widgets.ColorPicker.h"
#include "ui_DialogBasicPencilTool.h"

#include "Editor.Models.BasicPencilToolModel.h"

#include  <QDataWidgetMapper>
#include  <QDialog>
#include  <QVBoxLayout>
#include  <QSlider>


class cDialogBasicPencilTool :
    public  QDialog
{
    Q_OBJECT

public:
    typedef  QDialog  tSuperClass;

public:
    virtual  ~cDialogBasicPencilTool();
    cDialogBasicPencilTool( ::nQt::nModels::cBasicPencilToolModel* iModel, QWidget* iParent = nullptr );

public:
    bool  eventFilter( QObject* iObject, QEvent* iEvent ) override;

public:
    // Set/Get
    QSize  Size() const;

public:
    // Dialog controls
    void  OpenAtPosition( QPointF iPos );


public slots:
    // Slots
    void  SliderSizeChanged( int iValue );
    void  LuminosityChanged( int iValue );
    void  ColorPicked( const QColor& color );

private:
    Ui::DialogBasicPencilTool ui;

    ::nQt::nModels::cBasicPencilToolModel*  mToolModel;
    QDataWidgetMapper*                      mMapper;

    QTimer      mTimer;
    bool        mCloseOnRelease;

};


