#include "Editor.Models.DataWrapperEraserTool.h"


namespace nQt {
namespace nModels {


cDataWrapperEraserToolBase::~cDataWrapperEraserToolBase()
{
}


cDataWrapperEraserToolBase::cDataWrapperEraserToolBase( cTreeWrapperNode* iParent, ::nQt::nDrawingTools::cEraserTool* iEraserTool ) :
    tSuperClass( iParent ),
    mEraserTool( iEraserTool )
{
}


std::string
cDataWrapperEraserToolBase::Type() const
{
    return  "NodeEraserBase";
}


// -----------------------------------------------------
// -----------------------------------------------------
// -----------------------------------------------------


cDataWrapperEraserToolSize::~cDataWrapperEraserToolSize()
{
}


cDataWrapperEraserToolSize::cDataWrapperEraserToolSize( cTreeWrapperNode* iParent, ::nQt::nDrawingTools::cEraserTool* iEraserTool ) :
    tSuperClass( iParent, iEraserTool )
{
}


int
cDataWrapperEraserToolSize::DataCount() const
{
    return  2;
}


QVariant
cDataWrapperEraserToolSize::DataAtColumn( int iColumn )
{
    if( iColumn == 0 )
        return  "Size";

    return  mEraserTool->Size();
}


bool
cDataWrapperEraserToolSize::SetData( int iIndex, const QVariant & iData )
{
    if( iIndex != 1 )
        return  false;

    mEraserTool->Size( iData.toInt() );

    return  true;
}


std::string
cDataWrapperEraserToolSize::Type() const
{
    return  "NodeEraserSize";
}


// -----------------------------------------------------
// -----------------------------------------------------
// -----------------------------------------------------


cDataWrapperEraserToolAntiAliasing::~cDataWrapperEraserToolAntiAliasing()
{
}


cDataWrapperEraserToolAntiAliasing::cDataWrapperEraserToolAntiAliasing( cTreeWrapperNode* iParent, ::nQt::nDrawingTools::cEraserTool* iEraserTool ) :
    tSuperClass( iParent, iEraserTool )
{
}


int
cDataWrapperEraserToolAntiAliasing::DataCount() const
{
    return  2;
}


QVariant
cDataWrapperEraserToolAntiAliasing::DataAtColumn( int iColumn )
{
    if( iColumn == 0 )
        return  "AntiAliasing";

    return  mEraserTool->AntiAliasing();
}


bool
cDataWrapperEraserToolAntiAliasing::SetData( int iIndex, const QVariant & iData )
{
    if( iIndex != 1 )
        return  false;

    mEraserTool->AntiAliasing( iData.toBool() );

    return  true;
}


std::string
cDataWrapperEraserToolAntiAliasing::Type() const
{
    return  "NodeEraserAntiAliasing";
}



} //nModels
} //nQt

