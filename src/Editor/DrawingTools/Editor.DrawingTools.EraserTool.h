#pragma once


#include <QBrush>
#include <QPainter>
#include <QPixmap>
#include <QPen>


namespace  nQt::nDrawingTools {


class cEraserTool
{
public:
    ~cEraserTool();
    cEraserTool();

public:
    // Interface methods
    QPixmap*        CreateHUDPixmap( float iScale );
    QPainter*       CreateNewPainter( QPaintDevice* iPaintDevice );

public:
    // Set/Get
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
    int             mToolSize;
    bool            mAntiAliasingOn;
};


} // namespace  nQt::nDrawingTools



