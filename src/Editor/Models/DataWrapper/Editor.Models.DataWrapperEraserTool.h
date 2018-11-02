#pragma once

#include "Editor.Models.TreeWrapper.h"

#include "Editor.DrawingTools.EraserTool.h"

#include <QtCore>
#include <vector>

namespace nQt {
namespace nModels {


class cDataWrapperEraserToolBase :
    public cTreeWrapperNode
{
public:
    typedef cTreeWrapperNode tSuperClass;

public:
    virtual ~cDataWrapperEraserToolBase();
    cDataWrapperEraserToolBase( cTreeWrapperNode* iParent, ::nQt::nDrawingTools::cEraserTool* iEraserTool );

public:
    // Type
    virtual std::string Type() const override;

protected:
    ::nQt::nDrawingTools::cEraserTool* mEraserTool;
};


// -----------------------------------------------------
// -----------------------------------------------------
// -----------------------------------------------------


class cDataWrapperEraserToolSize :
    public cDataWrapperEraserToolBase
{
public:
    typedef cDataWrapperEraserToolBase tSuperClass;

public:
    virtual ~cDataWrapperEraserToolSize();
    cDataWrapperEraserToolSize( cTreeWrapperNode* iParent, ::nQt::nDrawingTools::cEraserTool* iEraserTool );

public:
    // Data
    virtual  int        DataCount() const override;
    virtual  QVariant   DataAtColumn( int iColumn ) override;
    virtual  bool       SetData( int iIndex, const QVariant& iData ) override;

public:
    // Type
    virtual std::string Type() const override;
};


// -----------------------------------------------------
// -----------------------------------------------------
// -----------------------------------------------------


class cDataWrapperEraserToolAntiAliasing :
    public cDataWrapperEraserToolBase
{
public:
    typedef cDataWrapperEraserToolBase tSuperClass;

public:
    virtual ~cDataWrapperEraserToolAntiAliasing();
    cDataWrapperEraserToolAntiAliasing( cTreeWrapperNode* iParent, ::nQt::nDrawingTools::cEraserTool* iEraserTool );

public:
    // Data
    virtual  int        DataCount() const override;
    virtual  QVariant   DataAtColumn( int iColumn ) override;
    virtual  bool       SetData( int iIndex, const QVariant& iData ) override;

public:
    // Type
    virtual std::string Type() const override;
};





} // nModels
} // nQT