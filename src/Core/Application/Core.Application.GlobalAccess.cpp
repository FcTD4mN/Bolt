#include "Core.Application.GlobalAccess.h"

namespace  nGlobal
{


cGlobalProperties::~cGlobalProperties()
{
}


cGlobalProperties::cGlobalProperties() :
	mTheMainWindow( 0 )
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


void
cGlobalProperties::SetTheMainWindow( sf::RenderWindow * iTheMainWindow )
{
	mTheMainWindow = iTheMainWindow;
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


sf::RenderWindow*
cGlobalProperties::GetTheMainWindow()
{
	return  mTheMainWindow;
}


}


