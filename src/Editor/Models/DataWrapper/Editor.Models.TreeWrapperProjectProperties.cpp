#include "Editor.Models.TreeWrapperProjectProperties.h"

#include "Core.Base.Variant.h"

#include "Core.Project.Project.h"

#include "Core.Render.Layer.h"

namespace nQt {
namespace nModels {


cTreeWrapperNodeProjectProperties::~cTreeWrapperNodeProjectProperties()
{
}


cTreeWrapperNodeProjectProperties::cTreeWrapperNodeProjectProperties( cTreeWrapperNode* iParent, ::nCore::nProject::cProject* iProject ) :
    tSuperClass( iParent ),
    mProject( iProject )
{
}


std::string
cTreeWrapperNodeProjectProperties::Type() const
{
    return  "ProjectProperties";
}


// ------ DATA


int
cTreeWrapperNodeProjectProperties::DataCount() const
{
    return  2;
}


QVariant
cTreeWrapperNodeProjectProperties::DataAtColumn( int iColumn )
{
    if( iColumn == 1 )
    {
        if( mData[ 0 ] == "Project Name" )
            return  mProject->Name().c_str();
        else if( mData[ 0 ] == "Resolution Width" )
            return  mProject->ResolutionWidth();
        else if( mData[ 0 ] == "Resolution Height" )
            return  mProject->ResolutionHeight();
        else if( mData[ 0 ] == "Limit Framerate" )
            return  mProject->LimitFramerate();
    }
    else
    {
        return  tSuperClass::DataAtColumn( iColumn );
    }

    return  QVariant();
}


bool
cTreeWrapperNodeProjectProperties::SetData( int iIndex, const QVariant & iData )
{
    if( mData[ 0 ] == "Project Name" )
        mProject->Name( iData.toString().toStdString() );
    else if( mData[ 0 ] == "Resolution Width" )
        mProject->SetResolution( iData.toFloat(), mProject->ResolutionHeight() );
    else if( mData[ 0 ] == "Resolution Height" )
        mProject->SetResolution( mProject->ResolutionWidth(), iData.toFloat() );
    else if( mData[ 0 ] == "Limit Framerate" )
        mProject->SetLimitFramerate( iData.toFloat() );

    return  true;
}


// ------ ACCESS


::nCore::nProject::cProject*
cTreeWrapperNodeProjectProperties::Project()
{
    return  mProject;
}


} //nModels
} //nQt

