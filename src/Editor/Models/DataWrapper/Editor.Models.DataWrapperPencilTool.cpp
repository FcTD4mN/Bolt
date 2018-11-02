#include "Editor.Models.DataWrapperPencilTool.h"


namespace nQt {
namespace nModels {


cDataWrapperPencilToolBase::~cDataWrapperPencilToolBase()
{
}


cDataWrapperPencilToolBase::cDataWrapperPencilToolBase( cTreeWrapperNode* iParent, ::nQt::nDrawingTools::cPencilTool* iPencilTool ) :
    tSuperClass( iParent ),
    mPencilTool( iPencilTool )
{
}


std::string
cDataWrapperPencilToolBase::Type() const
{
    return  "NodePencilBase";
}


// -----------------------------------------------------
// -----------------------------------------------------
// -----------------------------------------------------


cDataWrapperPencilToolSize::~cDataWrapperPencilToolSize()
{
}


cDataWrapperPencilToolSize::cDataWrapperPencilToolSize( cTreeWrapperNode* iParent, ::nQt::nDrawingTools::cPencilTool* iPencilTool ) :
    tSuperClass( iParent, iPencilTool )
{
}


int
cDataWrapperPencilToolSize::DataCount() const
{
    return  2;
}


QVariant
cDataWrapperPencilToolSize::DataAtColumn( int iColumn )
{
    if( iColumn == 0 )
        return  "Size";

    return  mPencilTool->Size();
}


bool
cDataWrapperPencilToolSize::SetData( int iIndex, const QVariant & iData )
{
    if( iIndex != 1 )
        return  false;

    mPencilTool->Size( iData.toInt() );

    return  true;
}


std::string
cDataWrapperPencilToolSize::Type() const
{
    return  "NodePencilSize";
}


// -----------------------------------------------------
// -----------------------------------------------------
// -----------------------------------------------------


cDataWrapperPencilToolColor::~cDataWrapperPencilToolColor()
{
}


cDataWrapperPencilToolColor::cDataWrapperPencilToolColor( cTreeWrapperNode* iParent, ::nQt::nDrawingTools::cPencilTool* iPencilTool ) :
    tSuperClass( iParent, iPencilTool )
{
}


int
cDataWrapperPencilToolColor::DataCount() const
{
    return  2;
}


QVariant
cDataWrapperPencilToolColor::DataAtColumn( int iColumn )
{
    if( iColumn == 0 )
        return  "Color";

    return  mPencilTool->Color();
}


bool
cDataWrapperPencilToolColor::SetData( int iIndex, const QVariant & iData )
{
    if( iIndex != 1 )
        return  false;

    mPencilTool->Color( iData.value< QColor >() );

    return  true;
}


std::string
cDataWrapperPencilToolColor::Type() const
{
    return  "NodePencilColor";
}


// -----------------------------------------------------
// -----------------------------------------------------
// -----------------------------------------------------


cDataWrapperPencilToolAntiAliasing::~cDataWrapperPencilToolAntiAliasing()
{
}


cDataWrapperPencilToolAntiAliasing::cDataWrapperPencilToolAntiAliasing( cTreeWrapperNode* iParent, ::nQt::nDrawingTools::cPencilTool* iPencilTool ) :
    tSuperClass( iParent, iPencilTool )
{
}


int
cDataWrapperPencilToolAntiAliasing::DataCount() const
{
    return  2;
}


QVariant
cDataWrapperPencilToolAntiAliasing::DataAtColumn( int iColumn )
{
    if( iColumn == 0 )
        return  "AntiAliasing";

    return  mPencilTool->AntiAliasing();
}


bool
cDataWrapperPencilToolAntiAliasing::SetData( int iIndex, const QVariant & iData )
{
    if( iIndex != 1 )
        return  false;

    mPencilTool->AntiAliasing( iData.toBool() );

    return  true;
}


std::string
cDataWrapperPencilToolAntiAliasing::Type() const
{
    return  "NodePencilAntiAliasing";
}



} //nModels
} //nQt

