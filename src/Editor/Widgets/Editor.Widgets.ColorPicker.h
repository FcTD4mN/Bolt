#pragma once

#include <QWidget>
#include <QPixmap>
#include <QTimer>


class cColorPicker :
    public QWidget
{
    Q_OBJECT

public:
    typedef  QWidget  tSuperClass;

public:
    virtual  ~cColorPicker();
    cColorPicker( QWidget* iParent = nullptr );

public:
    // Events overrides
    void  paintEvent( QPaintEvent* event ) override;

    void  mousePressEvent( QMouseEvent* event ) override;
    void  mouseMoveEvent( QMouseEvent* event ) override;
    void  mouseReleaseEvent( QMouseEvent* event ) override;

    void  resizeEvent( QResizeEvent* event ) override;

public:
    // Set/Get
    void  Light( float iLight );
    float Light() const;

    void  Color( const QColor& iColor );

private:
    // __PRIVATE__
    void _DrawWheel();
    void _DrawSelectedColorCircle();

signals:
    void  colorPicked( const QColor& color );

private:
    QPixmap*    mPixmap;
    QImage*     mImage;

    QPixmap*    mSelectedColorCircle;
    QPoint      mSelectedColorCirclePos;
    float       mLight;

    QColor      mSelectedColor;
};