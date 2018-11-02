#include "Core.Application.GlobalAccess.h"


namespace  nCore {
namespace  nApplication {


cGlobalAccess::~cGlobalAccess()
{
}


cGlobalAccess::cGlobalAccess() :
	mTheMainWindow( 0 )
{
}


// static
cGlobalAccess*
cGlobalAccess::Instance()
{
    static  cGlobalAccess* sgGlobalProperties = 0;
    if( !sgGlobalProperties )
        sgGlobalProperties = new cGlobalAccess();

    return  sgGlobalProperties;
}


void
cGlobalAccess::ProjectSize( const  sf::Vector2f&  iSize )
{
    mProjectSize = iSize;
}


void
cGlobalAccess::ProjectFolder( const  std::string&  iProjectFolder )
{
    mProjectFolder = iProjectFolder;
}


void
cGlobalAccess::TheMainWindow( sf::RenderWindow*  iTheMainWindow )
{
	mTheMainWindow = iTheMainWindow;
}


const  sf::Vector2f&
cGlobalAccess::ProjectSize()
{
    return  mProjectSize;
}


const  std::string&
cGlobalAccess::ProjectFolder()
{
    return  mProjectFolder;
}


sf::RenderWindow*
cGlobalAccess::TheMainWindow()
{
	return  mTheMainWindow;
}


} // nApplication
} // nCore

