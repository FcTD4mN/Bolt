#include "Editor.Models.TreeWrapperSystem.h"

#include "Core.Base.Variant.h"
#include "Core.ECS.Core.System.h"


namespace nQt {
namespace nModels {


cTreeWrapperNodeSystem::~cTreeWrapperNodeSystem()
{
}


cTreeWrapperNodeSystem::cTreeWrapperNodeSystem( cTreeWrapperNode* iParent, ::nCore::nECS::nCore::cSystem* iSystem ) :
    tSuperClass( iParent ),
    mSystem( iSystem )
{
}


std::string
cTreeWrapperNodeSystem::Type() const
{
    return  "System";
}


// ------ DATA


int
cTreeWrapperNodeSystem::DataCount() const
{
    return  2;
}


QVariant
cTreeWrapperNodeSystem::DataAtColumn( int iColumn )
{
    if( iColumn == 1 )
    {
        if( mData[ 0 ] == "System Name" )
            return  mSystem->Name().c_str();
        if( mData[ 0 ] == "Connected to Events" )
            return  mSystem->IsEventConnected();
    }
    else
    {
        return  tSuperClass::DataAtColumn( iColumn );
    }

    return  QVariant();
}


bool
cTreeWrapperNodeSystem::SetData( int iIndex, const QVariant & iData )
{
    if( mData[ 0 ] == "Connected to Events" )
    {
        if( iData.toBool() == true )
            mSystem->ConnectToEvents();
        else
            mSystem->DisconnectFromEvents();
    }

    return  true;
}


// ------ ACCESS


::nCore::nECS::nCore::cSystem*
cTreeWrapperNodeSystem::System()
{
    return  mSystem;
}


} //nModels
} //nQt

