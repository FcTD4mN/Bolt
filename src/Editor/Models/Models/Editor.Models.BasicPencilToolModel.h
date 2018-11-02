#pragma once

#include "Editor.Models.DrawingToolModelBase.h"

#include "Editor.DrawingTools.PencilTool.h"

#include <QColor>
#include <QBrush>
#include <QPainter>
#include <QPen>

namespace  nQt {
namespace  nModels {

class cBasicPencilToolModel :
    public cDrawingToolModelBase
{
    Q_OBJECT

public:
    typedef cDrawingToolModelBase tSuperClass;

public:
    enum eDataName
    {
        kToolSize = 0,
        kAntiAliasing,
        kColor
    };


public:
    virtual ~cBasicPencilToolModel();
    cBasicPencilToolModel( QObject* iParent = Q_NULLPTR );

public:
    // AbstractModel overrides
    virtual  Qt::ItemFlags  flags( const QModelIndex& iIndex ) const override;
    virtual  bool           setData( const QModelIndex &index, const QVariant &value, int role = Qt::EditRole ) override;

public:
    // cModelBase overrides
    virtual  QStyledItemDelegate *   CreateModelDelegate() override;

public:
    // DrawingToolModeBase overrides
    virtual  QPixmap*   CreateHUDPixmap( float iScale ) override;
    virtual  QPainter*  CreateNewPainter( QPaintDevice* iPaintDevice ) override;
    virtual  void       OpenToolDialogAtPosition( const QPointF& iPosition, QWidget* iParent = Q_NULLPTR ) override;

public:
    // Set/Get
    QColor          Color() const;
    void            Color( const QColor& iColor );

    int             Size() const;
    void            Size( int iSize );

    bool            AntiAliasing() const;
    void            AntiAliasing( bool iAA );

public:
    virtual  void  BuildData() override;

private:
    // Tool
    ::nQt::nDrawingTools::cPencilTool*  mPencilTool;
};

} //nQt
} //nModels
