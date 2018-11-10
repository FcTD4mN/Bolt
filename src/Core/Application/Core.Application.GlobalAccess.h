#pragma once

/*

    The purpose of this whole file is to avoid dependencies from low level api to cApplication, in order to get basic informations such as windows' properties
    ( size essentially ), or resource dir etc...

*/



#include <SFML/Graphics.hpp>

#define  PROJECTVIEWSIZE    ::nCore::nApplication::cGlobalAccess::Instance()->ProjectSize()
#define  PROJECTDIR         ::nCore::nApplication::cGlobalAccess::Instance()->ProjectFolder()
#define  MAINWIN            ::nCore::nApplication::cGlobalAccess::Instance()->TheMainWindow()


namespace nCore {
namespace nApplication {


class cGlobalAccess
{
private:
    ~cGlobalAccess();
    cGlobalAccess();

public:
    static  cGlobalAccess*  Instance();

public:
    void  ProjectSize( const  sf::Vector2f&  iSize );
    void  ProjectFolder( const  std::string&  iProjectFolder );
    void  TheMainWindow( sf::RenderWindow*  iTheMainWindow );
public:
    const  sf::Vector2f&    ProjectSize();
    const  std::string&     ProjectFolder();
    sf::RenderWindow*       TheMainWindow();

protected:
    sf::Vector2f        mProjectSize;
    std::string         mProjectFolder;
    sf::RenderWindow*   mTheMainWindow;
};


} // namespace nApplication
} // namespace nCore

