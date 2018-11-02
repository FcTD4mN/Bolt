#pragma once


#include <QBrush>
#include <QPainter>
#include <QPixmap>
#include <QPen>


namespace  nQt::nDrawingTools {


class cPencilTool
{
public:
    ~cPencilTool();
    cPencilTool();

public:
    // Interface methods
    QPixmap*        CreateHUDPixmap( float iScale );
    QPainter*       CreateNewPainter( QPaintDevice* iPaintDevice );

public:
    // Set/Get
    QColor          Color() const;
    void            Color( const QColor& iColor );

    int             Size() const;
    void            Size( int iSize );

    bool            AntiAliasing() const;
    void            AntiAliasing( bool iAA );

    QPen*           Pen();
    QBrush*         Brush();


private:
    // Tools
    QPen*           mPen;
    QBrush*         mBrush;
    QColor          mColor;
    int             mToolSize;
    bool            mAntiAliasingOn;
};


} // namespace  nQt::nDrawingTools



