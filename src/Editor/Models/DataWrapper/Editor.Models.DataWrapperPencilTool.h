#pragma once

#include "Editor.Models.TreeWrapper.h"

#include "Editor.DrawingTools.PencilTool.h"

#include <QtCore>
#include <vector>

namespace nQt {
namespace nModels {


class cDataWrapperPencilToolBase :
    public cTreeWrapperNode
{
public:
    typedef cTreeWrapperNode tSuperClass;

public:
    virtual ~cDataWrapperPencilToolBase();
    cDataWrapperPencilToolBase( cTreeWrapperNode* iParent, ::nQt::nDrawingTools::cPencilTool* iPencilTool );

public:
    // Type
    virtual std::string Type() const override;

protected:
    ::nQt::nDrawingTools::cPencilTool* mPencilTool;
};


// -----------------------------------------------------
// -----------------------------------------------------
// -----------------------------------------------------


class cDataWrapperPencilToolSize :
    public cDataWrapperPencilToolBase
{
public:
    typedef cDataWrapperPencilToolBase tSuperClass;

public:
    virtual ~cDataWrapperPencilToolSize();
    cDataWrapperPencilToolSize( cTreeWrapperNode* iParent, ::nQt::nDrawingTools::cPencilTool* iPencilTool );

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


class cDataWrapperPencilToolColor :
    public cDataWrapperPencilToolBase
{
public:
    typedef cDataWrapperPencilToolBase tSuperClass;

public:
    virtual ~cDataWrapperPencilToolColor();
    cDataWrapperPencilToolColor( cTreeWrapperNode* iParent, ::nQt::nDrawingTools::cPencilTool* iPencilTool );

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


class cDataWrapperPencilToolAntiAliasing :
    public cDataWrapperPencilToolBase
{
public:
    typedef cDataWrapperPencilToolBase tSuperClass;

public:
    virtual ~cDataWrapperPencilToolAntiAliasing();
    cDataWrapperPencilToolAntiAliasing( cTreeWrapperNode* iParent, ::nQt::nDrawingTools::cPencilTool* iPencilTool );

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