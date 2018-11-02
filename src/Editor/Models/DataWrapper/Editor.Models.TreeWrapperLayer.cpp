#include "Editor.Models.TreeWrapperLayer.h"

#include "Core.Base.Variant.h"
#include "Core.Render.Layer.h"

namespace nQt {
namespace nModels {


cTreeWrapperNodeLayer::~cTreeWrapperNodeLayer()
{
}


cTreeWrapperNodeLayer::cTreeWrapperNodeLayer( cTreeWrapperNode* iParent, ::nCore::nRender::cLayer* iLayer ) :
    tSuperClass( iParent ),
    mLayer( iLayer )
{
}


std::string
cTreeWrapperNodeLayer::Type() const
{
    return  "Layer";
}


// ------ DATA


int
cTreeWrapperNodeLayer::DataCount() const
{
    return  2;
}


QVariant
cTreeWrapperNodeLayer::DataAtColumn( int iColumn )
{
    if( iColumn == 1 )
    {
        if( mData[ 0 ] == "Layer Name" )
            return  mLayer->Name().c_str();
        else if( mData[ 0 ] == "ZDepth" )
            return  mLayer->ZLayer();
        else if( mData[ 0 ] == "Fixed" )
            return  mLayer->Fixed();
    }
    else
    {
        return  tSuperClass::DataAtColumn( iColumn );
    }

    return  QVariant();
}


bool
cTreeWrapperNodeLayer::SetData( int iIndex, const QVariant & iData )
{
    if( mData[ 0 ] == "Layer Name" )
        mLayer->Name( iData.toString().toStdString() );
    else if( mData[ 0 ] == "ZDepth" )
        mLayer->ZLayer( iData.toFloat() );
    else if( mData[ 0 ] == "Fixed" )
        mLayer->Fixed( iData.toBool() );

    return  true;
}


// ------ ACCESS


::nCore::nRender::cLayer*
cTreeWrapperNodeLayer::Layer()
{
    return  mLayer;
}


} //nModels
} //nQt

