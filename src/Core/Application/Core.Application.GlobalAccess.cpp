#include "Core.Application.GlobalAccess.h"

namespace  nGlobal
{


cGlobalProperties::~cGlobalProperties()
{
}


cGlobalProperties::cGlobalProperties()
{
}


// static
cGlobalProperties*
cGlobalProperties::Instance()
{
    static  cGlobalProperties* sgGlobalProperties = 0;
    if( !sgGlobalProperties )
        sgGlobalProperties = new cGlobalProperties();

    return  sgGlobalProperties;
}


void
cGlobalProperties::SetProjectSize( const sf::Vector2f & iSize )
{
    mProjectSize = iSize;
}


void
cGlobalProperties::SetProjectFolder( const std::string & iProjectFolder )
{
    mProjectFolder = iProjectFolder;
}


const sf::Vector2f &
cGlobalProperties::GetProjectSize()
{
    return  mProjectSize;
}


const std::string &
cGlobalProperties::GetProjectFolder()
{
    return  mProjectFolder;
}


}


