#pragma once

#include "Editor.Models.ModelBase.h"

#include <QBrush>
#include <QColor>
#include <QDialog>
#include <QPainter>
#include <QPen>

namespace  nQt {
namespace  nModels {

class cDrawingToolModelBase :
    public ::nQt::nModels::cModelBase
{
    Q_OBJECT

public:
    typedef ::nQt::nModels::cModelBase tSuperClass;

public:
    virtual ~cDrawingToolModelBase() = 0;
    cDrawingToolModelBase( QObject* iParent = Q_NULLPTR );

public:
    // The HUD is an optional visual aspect of the tool, like a cursor or whatever
    virtual  QPixmap*   CreateHUDPixmap( float iScale );

    // Can be nullptr if the tool doesn't do drawing, like select tool
    virtual  QPainter*  CreateNewPainter( QPaintDevice* iPaintDevice );

    // Dialog shown when doing the alt right click action. This can be null if the tool has no dialog to show
    virtual  void       OpenToolDialogAtPosition( const QPointF& iPosition, QWidget* iParent = Q_NULLPTR );

signals:
    void  hudInvalidated();
};

} //nQt
} //nModels
