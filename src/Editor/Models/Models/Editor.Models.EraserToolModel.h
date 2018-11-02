#pragma once

#include "Editor.Models.DrawingToolModelBase.h"

#include "Editor.DrawingTools.EraserTool.h"

#include <QBrush>
#include <QPainter>
#include <QPen>


namespace  nQt {
namespace  nModels {

class cEraserToolModel :
    public cDrawingToolModelBase
{
    Q_OBJECT

public:
    typedef cDrawingToolModelBase tSuperClass;

public:
    enum eDataName
    {
        kToolSize = 0,
        kAntiAliasing
    };


public:
    virtual ~cEraserToolModel();
    cEraserToolModel( QObject* iParent = Q_NULLPTR );

public:
    // AbstractModel overrides
    virtual  Qt::ItemFlags  flags( const QModelIndex& iIndex ) const override;
    virtual  bool           setData( const QModelIndex &index, const QVariant &value, int role = Qt::EditRole ) override;

public:
    // DrawingToolModeBase overrides
    virtual  QPixmap*   CreateHUDPixmap( float iScale ) override;
    virtual  QPainter*  CreateNewPainter( QPaintDevice* iPaintDevice ) override;

public:
    // Set/Get
    int             Size() const;
    void            Size( int iSize );

    bool            AntiAliasing() const;
    void            AntiAliasing( bool iAA );

public:
    virtual  void   BuildData() override;

private:
    // Tool
    ::nQt::nDrawingTools::cEraserTool*  mEraserTool;
};

} //nQt
} //nModels
